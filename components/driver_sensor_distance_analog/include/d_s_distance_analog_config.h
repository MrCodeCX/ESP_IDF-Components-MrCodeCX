#pragma once
#include <driver_peripheral_adc_oneshot.h> 

#ifdef __cplusplus
extern "C" {
#endif


/**
 * CONFIG STRUCTURES, to be used by the user, as part of the api, are defined her for global use of internal and api functions
 */

// ------------------------------ Function Conversion (Voltage to Distance) structure ------------------------------

typedef float (*d_s_distance_analog_conversion_t) (float);

// ------------------------------ THE CONFIG HANDLE ------------------------------

typedef struct {
    d_p_adc_oneshot_cfg_t adc_oneshot_cfg;                  // ADC ONESHOT CONFIG UNIT, provided by the user, to manage the adc sensors
    d_s_distance_analog_conversion_t f_conversion;          // Function Conversion Voltage to Distance provided by the user
} d_s_distance_analog_cfg_t;

typedef d_s_distance_analog_cfg_t* d_s_distance_analog_cfg_handle_t;


#ifdef __cplusplus
}
#endif