#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <visa.h>
#include <string.h>

#include "curve.h"
#include "stats.h"

ViStatus setupVI(ViSession RM,ViSession *handle,ViSession *handle1,char *search, char *search1){
	ViStatus status = VI_SUCCESS;
	ViChar descrip[VI_FIND_BUFLEN];
	ViUInt32  num_inst;
	ViFindList  List;

	status = viFindRsrc(RM,search,&List,&num_inst,descrip);
	if(status == VI_SUCCESS)
	{
		printf("connection 1 VI_SUCCESS\n");
		status = viOpen(RM,descrip,VI_NULL,VI_NULL,handle);
	}
	else printf("connection 1 failed\n");

	status = viFindRsrc(RM,search1,&List,&num_inst,descrip);
	if(status == VI_SUCCESS)
	{
		printf("connection 2 VI_SUCCESS\n");
		status = viOpen(RM,descrip,VI_NULL,VI_NULL,handle1);
	}
	else printf("connection 2 failed\n");

	return status;
}

float findScal(ViSession handle){
	ViStatus status = VI_SUCCESS;
	ViUInt32 resultCount;
	char diviC[5];
	float diviF = 0;
	
	status = viWrite(handle,"CH1:SCA?\n",9,&resultCount);
	sleep(3);
	viRead(handle,diviC,5,&resultCount);
	if (status != VI_SUCCESS)
	{
		printf("failed to find scale");
		exit(EXIT_FAILURE);
	} 
	// convert char to string
	sscanf(diviC,"%f",&diviF);
	printf("scale: %f\n",diviF);
	return diviF;

}

void autoSetScope(ViSession handle){
	ViStatus status = VI_SUCCESS;
	ViUInt32 resultCount;

	viWrite(handle,"AUTOS EXEC\n",11,&resultCount);
	sleep(3);//need sleep to make sure it's done in time
}


float readScope(ViSession handle, float scale){
	ViStatus status = VI_SUCCESS;
	ViUInt32 resultCount;


	int datasize = 2500;
	char resultBuffer[256];
	float dataHold[datasize];
	char dataBuffer[datasize];
	float amp;
	
	status = viWrite(handle,"CURV?\n",6,&resultCount);
	viRead(handle,dataBuffer,datasize,&resultCount);
	for(int i = 0; i <datasize; i++)
	{
		//float conversion
		dataHold[i]=dataBuffer[i] * scale*10.0/256;//multiply by coverstion factor
	}
	amp = find_amp(dataHold,datasize);//find amp
	return amp;
}
void setfreq(ViSession handle,int lamda ){
	ViStatus status = VI_SUCCESS;
	ViUInt32 resultCount;
	int length;
	char set[50];
	sprintf(set,":SOUR:FREQ %d\n",lamda);//set the freq
	length = strlen(set);
	status = viWrite(handle,set,length,&resultCount);
}
void scanfreq(ViSession scope, ViSession func, float scale){
	float amp;
	int f_min,f_max,f_step;
	// enter variables
	printf("enter min freq: ");
	scanf("%d",&f_min);
	printf("enter max freq: ");
	scanf("%d",&f_max);
	printf("enter step freq: ");
	scanf("%d",&f_step);

	printf("min: %d max: %d step: %d\n",f_min,f_max,f_step);
	//check if input is valid
	if(f_min >= f_max || f_step <= 0 || f_min <= 1){
		printf("invalid inputs\n");
		exit(EXIT_FAILURE);
	}
	setfreq(func,f_min);//set generators
	FILE* write_file;
	write_file = fopen("wave.txt","w");
	for (int i = f_min; i <= f_max; i+=f_step)
	{
		printf("freaq: %d\n",i );
		setfreq(func,i);
		amp=readScope(scope,scale);

		fprintf(write_file,"freq:%d:amp:%f\n",i,amp);
	}
	fclose(write_file);
	printf("write over");
}
int main(){
	char inq[] = "*IDN?/n";
	ViStatus status = VI_SUCCESS;
	ViUInt32 resultCount;
	ViFindList resourceList;
	ViUInt32 num_inst;//special in from IVI to standerdize int

	float amp;
	float scale;
	
	ViSession defaultRM, scopeHandle, funcHandle;
	ViChar description[VI_FIND_BUFLEN];

	char findscope[] = "USB[0-9]::0x0699?*";
	char findfunc[] = "USB[0-9]::0x1AB1?*";

	status = viOpenDefaultRM(&defaultRM);
	status = setupVI(defaultRM,&scopeHandle,&funcHandle,findscope,findfunc);
	//set channnels
	if(status == VI_SUCCESS){
		viWrite(scopeHandle,"DAT:SOU CH1\n",12,&resultCount);
		viWrite(funcHandle,":OUTP1:MODE NORM\n",17,&resultCount);
		viWrite(funcHandle,":OUTP1 ON\n",10,&resultCount);
		 scale = findScal(scopeHandle);
		// L = 10 mH, C = 132 nF  hz =67.5khz
		scanfreq(scopeHandle,funcHandle, scale);

	}
	else printf("program failed");

	return 0;
}