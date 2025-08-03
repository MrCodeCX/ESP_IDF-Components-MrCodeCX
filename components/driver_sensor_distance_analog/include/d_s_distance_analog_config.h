#pragma once
#include <driver_peripheral_adc_oneshot.h> 
#include <d_s_distance_analog_conversions.h>

// GLOBAL CONFIG THE ANALOG UNIT AND CHANNELS FOR THE SENSORS IN d_s_distance_analog_config.c
extern d_p_adc_oneshot_cfg_t d_s_distance_analog_adc_oneshot_config;

// If you want you can change the global config for the sensors during execution
// But you just can have one at time, then before change to other, kill the previous config

#define D_S_DISTANCE_ANALOG_N_SENSORS 3

// OVERRIDE -> THIS MACRO TO CALL YOUR VOLTAGE TO DISTANCE CONVERSION FUNCTION (volts to cm)
#define D_S_DISTANCE_ANALOG_VOLTAGE_TO_DISTANCE(x) d_s_convert_distance_digital_rz60s(x)
