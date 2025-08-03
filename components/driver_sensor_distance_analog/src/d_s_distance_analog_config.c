#include <d_s_distance_analog_config.h>

// GLOBAL CONFIG THE ANALOG UNIT AND CHANNELS FOR THE SENSORS
d_p_adc_oneshot_cfg_t d_s_distance_analog_adc_oneshot_config = {
    .adc_unit = ADC_UNIT_1,
    .n_channels = D_S_DISTANCE_ANALOG_N_SENSORS,
    // LEFT CENTER RIGHT
    .adc_channels = {ADC_CHANNEL_5, ADC_CHANNEL_7, ADC_CHANNEL_4},
};