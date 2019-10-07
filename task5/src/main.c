#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <visa.h>
//#include "../include/visa.h"
int main(){
	unsigned char resultBuffer[256];
	char inq[] = "*IDN?/n";
	ViStatus status = VI_SUCCESS;
	ViFindList resourceList;
	ViUInt32 num_inst;
	ViUInt32 resultCount;

	ViSession defaultRM, scopeHandle;
	ViChar description[VI_FIND_BUFLEN];
	char dataBuffer[2500];

	int y;
	int lsb;
	int masb;

	status = viOpenDefaultRM(&defaultRM);
	printf("I am working\n");

	if(status == VI_SUCCESS)
	{
		printf("I am working1\n");
		status = viFindRsrc(defaultRM,"USB[0-9]::?*INSTR",&resourceList,&num_inst,description);
		printf("I am working2\n");
		if(status == VI_SUCCESS)
		{
			printf("I am working3\n");
			status = viOpen(defaultRM,description,VI_NULL,VI_NULL,&scopeHandle);
			printf("I am working4\n");
			if(status == VI_SUCCESS)
			{
				printf("I am working5\n");
				printf("Opened instriment %s\n",description);

				viWrite(scopeHandle,"*IDN?\n",6,&resultCount);
				viRead(scopeHandle,resultBuffer,256,&resultCount);

				printf("\nResult count: %d\n",resultCount);
				printf("\nResult buffer: %s\n",resultBuffer);

				viWrite(scopeHandle,"CURV?\n",6,&resultCount);
				viRead(scopeHandle,dataBuffer,2500,&resultCount);

				for(int i = 0; i <128; i++)
				{
					y = dataBuffer[i];
					printf("\nRaw = %x, Read = %d",y,y);
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