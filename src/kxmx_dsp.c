#include "kxmx_dsp.h"

kxmx_pdwt_f_state kxmx_pdwt_f_init(int sample_rate, int block_size, int spectrum_size, float lowest_frequency, float highest_frequency, float* golden_samples, float golden_f0) {
  kxmx_pdwt_f_state state;

  // Star out by initializing our state parameters
  state.current_index = 0;
  state.sample_rate = sample_rate;
  state.block_size = block_size;
  state.spectrum_size = spectrum_size;
  state.lowest_frequency = lowest_frequency;
  state.highest_frequency = highest_frequency;
  state.golden_f0 = golden_f0;

  state.golden_samples = golden_samples;

  // Allocate the memory needed for the sample buffers
  state.samples_in = malloc(sizeof(float) * block_size);
  state.samples_out = malloc(sizeof(float) * block_size);

  // Allocate the memory needed for the spectrums
  state.spectrum = malloc(sizeof(float) * spectrum_size);
  state.last_spectrum = malloc(sizeof(float) * spectrum_size);

  // Allocate the memory needed for the
  state.frequencies = malloc(sizeof(float) * spectrum_size);

  for (int i = 0; i < spectrum_size; i++) {
    state.frequencies[i] = i * ((highest_frequency - lowest_frequency) / (float) spectrum_size ) + lowest_frequency;
  }

  state.fourier_coef_r = malloc(sizeof(float) * spectrum_size);
  state.fourier_coef_i = malloc(sizeof(float) * spectrum_size);

  for (int i = 0; i < spectrum_size; i++) {
    state.fourier_coef_r[i] = sin(-2 * M_PI * state.frequencies[i] / spectrum_size);
    state.fourier_coef_i[i] = cos(-2 * M_PI * state.frequencies[i] / spectrum_size);
  }


  return state;
}


int main(void) {


  kxmx_pdwt_f_state state = kxmx_pdwt_f_init(44100, 16, 512, 100, 1100, 0, 440.0);

  printf( "Sample Rate : %u\n", state.sample_rate);
  printf( "Size : %lu\n", sizeof(state.fourier_coef_i[0]));

  for (int i = 0; i < state.spectrum_size; i++) {
    printf( "Freq %u: %f - Coef: %f,%fi\n", i, state.frequencies[i], state.fourier_coef_r[i], state.fourier_coef_i[i]);
  }

	return EXIT_SUCCESS;
}
