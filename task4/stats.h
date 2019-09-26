#ifndef STATS_H  
#define STATS_H

float find_mean(float* data, int len);
float find_std(float* data, int len);
void find_mean_std(float*data, int len, float* out_mean, float*out_std);
void find_mean_std2(float*data, int len, float* out_mean, float*out_std);
double d_rand();

#endif 