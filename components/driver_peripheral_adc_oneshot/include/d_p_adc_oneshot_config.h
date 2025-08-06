#pragma once
#include <esp_adc/adc_oneshot.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * GLOBAL CONSTANT MACROS ESP32 Classic (Dont touch it, at least you were using a esp32 variant)
 */

#define D_P_ADC_ONESHOT_CONST_MAX_CHANNELS 10

// ------------------------------ ADC UNIT 1 (ESP32 CLASSIC) ------------------------------

#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_39_ADC_CHANNEL ADC_CHANNEL_3
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_38_ADC_CHANNEL ADC_CHANNEL_2
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_37_ADC_CHANNEL ADC_CHANNEL_1
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_36_ADC_CHANNEL ADC_CHANNEL_0
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_35_ADC_CHANNEL ADC_CHANNEL_7
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_34_ADC_CHANNEL ADC_CHANNEL_6
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_33_ADC_CHANNEL ADC_CHANNEL_5
#define D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_32_ADC_CHANNEL ADC_CHANNEL_4

// ------------------------------ ADC UNIT 2 (ESP32 CLASSIC) ------------------------------

#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_27_ADC_CHANNEL ADC_CHANNEL_7
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_26_ADC_CHANNEL ADC_CHANNEL_9
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_25_ADC_CHANNEL ADC_CHANNEL_8
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_15_ADC_CHANNEL ADC_CHANNEL_3
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_14_ADC_CHANNEL ADC_CHANNEL_6
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_13_ADC_CHANNEL ADC_CHANNEL_4
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_12_ADC_CHANNEL ADC_CHANNEL_5
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_4_ADC_CHANNEL ADC_CHANNEL_0
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_2_ADC_CHANNEL ADC_CHANNEL_2
#define D_P_ADC_ONESHOT_CONST_ADC_2_GPIO_0_ADC_CHANNEL ADC_CHANNEL_1


/**
 * CONFIG STRUCTURES, to be used by the user, as part of the api, are defined here for global use of internal and api functions
 */

// ------------------------------ THE CONFIG HANDLE ------------------------------

typedef struct {
    adc_unit_t adc_unit;                                                    // ADC UNIT
    size_t n_channels;                                                      // N CHANNELS
    adc_oneshot_unit_handle_t* _private_pointer_to_adc_oneshot_handle;      // PRIVATE POINTER TO ADC HANDLE
    bool _private_init_state;                                               // PRIVATE STATE FOR THIS CONFIG
    adc_channel_t adc_channels[];                                           // ADC CHANNELS (Used at end of the structure for compiler optimization)
} d_p_adc_oneshot_cfg_t;

typedef d_p_adc_oneshot_cfg_t* d_p_adc_oneshot_cfg_handle_t;


/**
 * GLOBAL USER MACROS, to be defined by the user, or just keep the defaults for simple use
 */

// ------------------------------ ATTENUATED VOLTAGE (0 - 3.3V) BY DEFAULT ------------------------------

#define D_P_ADC_ONESHOT_CHANNELS_ATTEN ADC_ATTEN_DB_12

// ------------------------------ BIT RESOLUTION (12 BITS) BY DEFAULT ------------------------------

#define D_P_ADC_ONESHOT_CHANNELS_BITWIDTH ADC_BITWIDTH_12

// ------------------------------ MAX VALUES TRADUCTION ------------------------------

#if D_P_ADC_ONESHOT_CHANNELS_ATTEN == ADC_ATTEN_DB_12
    #define D_P_ADC_ONESHOT_CHANNELS_VOLTAGE_MAX 3.3f
#endif
#if D_P_ADC_ONESHOT_CHANNELS_BITWIDTH == ADC_BITWIDTH_12
    #define D_P_ADC_ONESHOT_CHANNELS_LECTURE_MAX 4096.0f
#endif

// ------------------------------ LOW LEVEL CONFIG ------------------------------

// ULTRA LOW POWER DISABLE BY DEFAULT
#define D_P_ADC_ONESHOT_ULP_MODE ADC_ULP_MODE_DISABLE
// THE CLOCK SRC BY DEFAULT
#define D_P_ADC_ONESHOT_CLK_SRC ADC_RTC_CLK_SRC_DEFAULT


#ifdef __cplusplus
}
#endif