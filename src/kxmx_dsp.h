#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef KXMX_H_
#define KXMX_H_

typedef struct kxmx_pdwt_f_state {
  int sample_rate;
  int current_index;
  int block_size;
  int spectrum_size;
  float golden_f0;
  float lowest_frequency;
  float highest_frequency;
  float* frequencies;
  float* fourier_coef_r;
  float* fourier_coef_i;
  float* spectrum;
  float* last_spectrum;
  float* golden_samples;
  float* samples_in;
  float* samples_out;


} kxmx_pdwt_f_state;

kxmx_pdwt_f_state kxmx_pdwt_f_init(int sample_rate, int block_size, int spectrum_size, float from_frequency, float to_frequency, float *golden_samples, float golden_f0);

#endif /* KXMX_H_ */
