#pragma once
#include <driver_peripheral_adc_oneshot.h>

// THE DEFAULT FLAG FOR OUT OF RANGE AND DEAD ZONE IS -1

// INTERNAL FUNCTION TO CONVERT THE DISTANCE FOR SHARP GP2Y0A21
float d_s_convert_distance_sharp_gp2y0a21(float voltage);

// INTERNAL FUNCTION TO CONVERT THE DISTANCE FOR A DIGITAL SENSOR RZ60S
float d_s_convert_distance_digital_rz60s(float voltage);