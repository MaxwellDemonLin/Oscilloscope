/*!
 * @file Adafruit_ZeroFFT.h
 *
 * This is an FFT library designed to run on ARM cortex M0 CPUs.
 * It is based on FFT functions provided by ARM.
 *
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Dean Miller for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef ADAFRUIT_ZEROFFT_ADAFRUIT_ZEROFFT_H_
#define ADAFRUIT_ZEROFFT_ADAFRUIT_ZEROFFT_H_

#include "main.h"

#define FFT_BIN(num, fs, size)                                                 \
  ((num) *                                                                       \
   (fs) / (size)) ///< return the center frequency of FFT bin 'num'
                              ///< based on the sample rate and FFT stize
#define FFT_INDEX(freq, fs, size)                                              \
  ((int)((float)(freq) /                                                         \
         ((float)(fs) /                                                          \
          (float)(size)))) ///< return the bin index where the specified frequency
                         ///< 'freq' can be found based on the passed sample
                         ///< rate and FFT size

#ifndef ALIGN4
#define ALIGN4 __attribute__((aligned(4))) ///< align to 4 bytes
#endif

#ifndef q15_t
#define q15_t int16_t ///< a q15 fractional data type
#endif

#ifndef q31_t
#define q31_t int32_t ///< a q31 fractional data type
#endif

#ifndef float32_t
#define float32_t float ///< 32 bit floating point data type
#endif

#define FFT_POINT 256
#define ZERO_FFT_MAX (FFT_POINT * 2) ///< the maximum allowed FFT size

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**************************************************************************/
/*!
    @brief  run an FFT on an int16_t array. Note that this is run in place.
    @param source the data to FFT
    @param length the length of the data. This must be a power of 2 and less
   than or equal to ZERO_FFT_MAX
    @return 0 on success, -1 on failure
    @note The FFT is run in place on the data. A hanning window is applied to
   the input data. The complex portion is discarded, and the real values are
   returned.
*/
/**************************************************************************/
extern int ZeroFFT(q15_t *source);

extern const q15_t window_hanning_256[];  ///< a hanning window of length 256


#ifdef __cplusplus
};
#endif // __cplusplus
#include "arm_common_tables.h"

#endif /* ADAFRUIT_ZEROFFT_ADAFRUIT_ZEROFFT_H_ */
