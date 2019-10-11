#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <visa.h>

#include "curve.h"
#include "stats.h"

int main(){
	int datasize = 2500;
	char resultBuffer[256];
	char diviC[5];
	float diviF = 0;
	float resultHold[datasize];
	char inq[] = "*IDN?/n";
	ViStatus status = VI_SUCCESS;
	ViFindList resourceList;
	ViUInt32 num_inst;//special in from IVI to standerdize int
	ViUInt32 resultCount;

	ViSession defaultRM, scopeHandle;
	ViChar description[VI_FIND_BUFLEN];
	char dataBuffer[datasize];

	

	status = viOpenDefaultRM(&defaultRM);

	if(status == VI_SUCCESS)
	{
		status = viFindRsrc(defaultRM,"USB[0-9]::?*INSTR",&resourceList,&num_inst,description);
		if(status == VI_SUCCESS)
		{
			status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&scopeHandle);
			if(status == VI_SUCCESS)
			{
				printf("Opened instriment %s\n",description);

				viWrite(scopeHandle,"*IDN?\n",6,&resultCount);
				viRead(scopeHandle,resultBuffer,256,&resultCount);

				printf("\nResult count: %d\n",resultCount);
				printf("\nResult buffer: %s\n",resultBuffer);
				//set scope to CH1
				viWrite(scopeHandle,"DAT:SOU CH1\n",12,&resultCount);
				//find conversion factors
				viWrite(scopeHandle,"CH1:SCA?\n",9,&resultCount);
				viRead(scopeHandle,diviC,5,&resultCount);
				// convert char to string
				sscanf(diviC,"%f",&diviF);
				//stautus can't be on ViRead
				status = viWrite(scopeHandle,"CURV?\n",6,&resultCount);
				viRead(scopeHandle,dataBuffer,datasize,&resultCount);
				//actural data reading into dataBuffer as int
				
				if(status == VI_SUCCESS){
					printf("Read success, datasize: %d, write to wave.txt\n",resultCount);
					//write to file
					FILE* write_file;
					write_file = fopen("wave.txt","w");
					for(int i = 0; i <datasize; i++)
					{
						//float conversion
						resultHold[i]=dataBuffer[i] * diviF*8.0/256;//multiply by coverstion factor
						fprintf(write_file,"%d %d %f\n",i,dataBuffer[i],resultHold[i]);
					}
					fclose(write_file);
					printf("write over");
				}
				else{
					printf("Data read error\n");
				}
				
				
			}
			else{
				printf("Faild to open %s\n",description );
			}
		}
		else{
			printf("Failed to find connection \n");
		}
	}
	return 0;
}