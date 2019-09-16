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

	std= sqrt(sum/len);

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
	float std_value = sq_sum/len - ave * ave;
	std_value = sqrt(std_value);

	*out_mean = ave;
	*out_std = std_value;
}
int main()
{
	float data [] ={0.068038, 0.173967, 0.439303, 0.615258, 0.789436, 0.770980, 0.890924, 1.034431, 0.955555, 0.991579, 0.919359, 0.857244, 0.680064, 0.558250, 0.473129, 0.278329, 0.027142, -0.151631, -0.454363, -0.534177, -0.803847, -0.882892, -0.996433, -0.919950, -1.068664, -1.000596, -0.997921, -0.909708, -0.607322, -0.611919, -0.380097, -0.127268};

	float mean;
	float std_dev;

	/*	Here you can put the code to find the standard deviation of the data array	*/


	/*  ==== START OF YOUR CODE ==== */

	int length =0;
	length = sizeof(data)/sizeof(data[0]);//size of find the byte of data, then we use that to find amount of data in data[]
	
	mean = find_mean(data,length);
	std_dev = find_std(data,length);


	printf("\nMean = %f", mean);
	printf("\nStandard deviation = %f", std_dev);

	float mean1;
	float std1;

	find_mean_std2(data,length,&mean1,&std1);

	printf("\nMean = %f", mean1);
	printf("\nStandard deviation = %f", std1);
	return 0;  // Functions which return a value MUST contain at least one return statement
}
