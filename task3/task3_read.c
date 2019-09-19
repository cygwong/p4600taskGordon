#include <stdlib.h>	/* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>	/* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>	/* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 

float find_mean(float* data, int len)
{
	float mean = 0;
	for(int i = 0; i < len; i++){
		mean += data[i];
	}
	mean = mean/len;
	return mean;
}

float find_std(float* data, int len)
{
	float mean;
	float std;

	mean = find_mean(data,len);

	float dev_sq[len]; //to stor x-xbar sq
	float sum = 0;//sum of deviation


	for (int i = 0; i <len; i += 1)
	{
		dev_sq[i] = pow(data[i] - mean,2);
	}

	for (int i = 0; i <len; i += 1)
	{
		sum = sum + dev_sq[i];
	}

	std= sqrt(sum/(len-1));

	return std;
}

void find_mean_std(float*data, int len, float* out_mean, float*out_std)
{
	*out_mean = find_mean(data,len);
	*out_std = find_std(data,len);
}

void find_mean_std2(float*data, int len, float* out_mean, float*out_std)
{
	float sum = 0;
	float sq_sum = 0;

	for (int i = 0; i < len; ++i)
	{
		sum += data[i];
		sq_sum += data[i]*data[i];
	}

	float ave = sum/len;
	float std_value = (sq_sum - ave * ave * len)/(len - 1);
	std_value = sqrt(std_value);

	*out_mean = ave;
	*out_std = std_value;
}
void main(int argc,char** argv)
{
	
	float mean;
	float std_dev;

	FILE* read_file;
	read_file = fopen(argv[1],"r");

	int size = 0;

	if(read_file !=NULL){

		fscanf(read_file, "%d", &size);
		float data_x[size];
		float data_y[size];

		for (int i = 0; i < size; ++i)
		{
			fscanf(read_file, "%f %f", &data_x[i], &data_y[i]);
		}

		printf("size of data: %d \n", size);
		for(int i = 0; i < size; i++){
			printf(" %f ",data_y[i]);
		}
		find_mean_std(data_y,size,&mean,&std_dev);
		printf("\n Mean: %f",mean);
		printf("\n std: %f",std_dev);

	}
	else{
		printf("\n data not found");
	}
}
