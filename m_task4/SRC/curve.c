#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "curve.h"

float find_amp(float* yin, int size){
	if(size < 2){
		printf("\n not enough data points. ");
		return 0;
	}
	float high = yin[0];
	float low = yin[0];
	float dh = 0;

	for(int i = 0; i < size; ++i){
		if(high < yin[i]) high = yin[i];
		if(low > yin[i]) low = yin[i];
	}
	dh = high - low;
	return (dh/2.0);
}

void ave_curve(float* datain, float* dataout, int ave_size, int data_size){
	int i = 0;
	int j = 0;
	float ave = 0;

	while(i < data_size){
		ave = 0;//reset;
		j = 0;
		while(j < ave_size && i+j <= data_size){
			ave += datain[i+j]/ave_size;
			j +=1;
		}
		dataout[i] = ave;
		i+=1;
	}
}