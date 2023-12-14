

#ifndef FLUX_BASE_H
#define FLUX_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

// window
typedef enum{
	Window_Rect=0, 
	Window_Hann,
	Window_Hamm,

	Window_Blackman,
	Window_Kaiser,

	Window_Bartlett,
	Window_Triang,

	Window_Flattop,
	Window_Gauss,

	Window_Blackman_Harris,
	Window_Blackman_Nuttall,
	Window_Bartlett_Hann,

	Window_Bohman,

	Window_Tukey, // tapered cosine

} WindowType;


#ifdef __cplusplus
}
#endif

#endif