#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "curve.h"

double find_amp(double* yin, int size){
	if(size < 2){
		printf("\n not enough data points. ");
		return 0;
	}
	double high = yin[0];
	double low = yin[0];
	double dh = 0;

	for(int i = 0; i < size; ++i){
		if(high < yin[i]) high = yin[i];
		if(low > yin[i]) low = yin[i];
	}
	dh = high + low;
	return (dh/2.0);
}

void ave_cruve(double* datain, double* dataout, int ave_size, int data_size){
	int i = 0;
	int j = 0;
	double ave = 0;

	while(i < data_size){
		while(j < ave_size && i+j <= data_size){
			ave += datain[i+j]/data_size;
			J +=1;
		}
		dataout[i] = ave;
		i+=1
	}
}