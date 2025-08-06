#pragma once
#include <driver_peripheral_adc_oneshot.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * GENERAL FUNCTION CONVERSIONS, provided by this driver, the user can use one of this functions or his own conversion function
 * THE DEFAULT FLAG FOR OUT OF RANGE AND DEAD ZONE IS -1
 */

// ------------------------------ SHARP GP2Y0A21 ------------------------------

float d_s_distance_analog_conversion_sharp_gp2y0a21(float voltage);

// ------------------------------ RZ60S (DIGITAL) ------------------------------

float d_s_distance_analog_conversion_rz60s(float voltage);


#ifdef __cplusplus
}
#endif