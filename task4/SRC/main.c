#include <stdlib.h>	/* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>	/* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>	/* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 

#include "../INCLUDE/curve.h"

int main(){
	float x[size];// input trig
	float y[size];// output trig
	float step =4 * 3.1415/size;

	FILE* write_file;
	write_file = fopen("wave.data","w");
	if (write_file != NULL)
	{
		for (int i = 0; i < size; ++i)
		{
			x[i] = i*step;
			y[i] = sin(i*step);
		}

		fprintf(write_file,"%d \n",size);

		for(int i = 0; i < size; ++i)
		{
			fprintf(write_file,"%f %f\n",x[i],y[i]);
		}

		printf("\n wirte over" );
		fclose(write_file);

	}
	else
	{
		printf("\n Error unable to write file");
	}
}