#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	int size = 80;
	float x[size];// input trig
	float y[size];// output trig
	float step = 3.1415/16;

	FILE* write_file;
	write_file = fopen("data.data","w");
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