

#ifndef TEST1_H
#define TEST1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

// vector
#include "../pitch/vector/flux_vector.h"
#include "../pitch/vector/flux_vectorOp.h"
#include "../pitch/vector/flux_complex.h"

// util
#include "../pitch/util/flux_util.h"
#include "../pitch/util/flux_wave.h"

// dsp
#include "../pitch/dsp/flux_window.h"
#include "../pitch/dsp/fft_algorithm.h"
#include "../pitch/dsp/conv_algorithm.h"
#include "../pitch/dsp/xcorr_algorithm.h"

#include "../pitch//_pitch_yin.h"
#include "../pitch//_pitch_pef.h"
#include "../pitch//_pitch_ncf.h"
#include "../pitch//_pitch_lhs.h"
#include "../pitch//_pitch_hps.h"
#include "../pitch//_pitch_cep.h"

// .
#include "../pitch/flux_base.h"

#ifdef __cplusplus
}
#endif

#endif