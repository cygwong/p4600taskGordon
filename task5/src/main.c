#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <visa.h>

#include "curve.h"
#include "stats.h"

int main(){
	unsigned char resultBuffer[2500];
	char inq[] = "*IDN?/n";
	ViStatus status = VI_SUCCESS;
	ViFindList resourceList;
	ViUInt32 num_inst;//special in from IVI to standerdize int
	ViUInt32 resultCount;

	ViSession defaultRM, scopeHandle;
	ViChar description[VI_FIND_BUFLEN];
	char dataBuffer[2500];

	int y;
	int lsb;
	int masb;

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

				//viWrite(scopeHandle,"DAT:SOU CH1\n",12,&resultCount);
				//sleep(2);
				status = viWrite(scopeHandle,"CURV?\n",6,&resultCount);
				sleep(2);
				viRead(scopeHandle,dataBuffer,2500,&resultCount);

				if(status == VI_SUCCESS){
					printf("Read success, datasize: %d\n",resultCount);
					for(int i = 0; i <128; i++)
					{
						y = dataBuffer[i];
						printf("\nRaw = %x, Read = %d",y,y);
					}
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