#include <stdlib.h>	/* The standard libary: a collection of common C functions. Needed in almost any useful program */
#include <stdio.h>	/* The standard input/output library: functions for inputting and outputting data. Needed in almost any useful program*/ 
#include <math.h>	/* Math library: common math functions. Needed for almost any program a physicist would write! remember to use the -lm option with your compiler when including this file */ 
#include <time.h>

#include "curve.h"
#include "stats.h"

int main(){
	int size = 1300;
	double x[size];// input trig
	double y[size];// output trig
	double y_n[size];//noise output
	double y_s[size];//smooth output
	double step =4 * 3.1415/size;
	srand(time(NULL));

	for (int i = 0; i < size; ++i)
	{

		x[i] = i*step;
		y[i] = sin(i*step);
		y_n[i] = y[i] + d_rand();
	}
	

	double amp = 0;
	amp = find_amp(y,size);
	printf("\namp is %f",amp);
	amp = find_amp(y_n,size);
	printf("\n noise amp is %f",amp);

	ave_curve(y_n,y_s,20,size);

	amp = find_amp(y_s,size);
	printf("\n smooth amp is %f",amp);

	FILE* write_file;
	write_file = fopen("wave.txt","w");
	if (write_file != NULL)
	{
		

		for(int i = 0; i < size; ++i)
		{
			fprintf(write_file,"%f %f %f %f\n",x[i],y[i],y_n[i],y_s[i]);
		}

		printf("\n wirte over" );
		fclose(write_file);

	}
	else
	{
		printf("\n Error unable to write file");
	}
}