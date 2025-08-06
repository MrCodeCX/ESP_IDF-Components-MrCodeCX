#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * INTERNAL HARDWARE FUNCTIONS
 */

// ------------------------------ SETUP HANDLE ------------------------------

/**
 * @brief Internal Function to setup the handle for the adc unit with the global user macros config
 * 
 * @note The adc oneshot handle has to be uninitialized, at least it have to be null, the function verifys it by itself
 * @note The complete unitialized verification have to be do by a higher level function with memory
 * 
 * @param adc_oneshot_handle    A pointer to the adc oneshot handle that has to be created and returned by the function
 * @param adc_unit              The adc unit to config
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_setup_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle, adc_unit_t adc_unit);

// ------------------------------ SETUP CHANNELS ------------------------------

/**
 * @brief Internal Function to setup the adc channels with the global user macros config
 * 
 * @note The adc oneshot handle has to be initialized first, at least it have to be diferent that null, the function verifys it by itself
 * @note The complete initialized verification have to be do by a higher level function with memory
 * 
 * @param adc_oneshot_handle    The adc oneshot handle
 * @param n_channels            The number of channels
 * @param adc_channels          A pointer to the adc channels array
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_setup_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels);

// ------------------------------ KILL ------------------------------

/**
 * @brief Internal Function to kill the handle for the adc unit, dosent exits a function to kill the channels.
 * This is because the channels objets are only configurations.
 * And this configurations can be override at even moment, without needing a kill cleaning function before.
 * 
 * @note The adc oneshot handle has to be initialized first, at least it have to be diferent that null, the function verifys it by itself
 * @note The complete initialized verification have to be do by a higher level function with memory
 * 
 * @param adc_oneshot_handle    A pointer to the adc oneshot handle that has to be killed by the function, and will be override with NULL
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_kill_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle);

// ------------------------------ READ CHANNELS (INT LECTURES) ------------------------------

/**
 * @brief Internal Function to read the int lectures for multiple channels
 * 
 * @note The adc oneshot handle has to be initialized first, at least it have to be diferent that null, the function verifys it by itself
 * @note The channels have to be setup (config) first, at least one time, but this function dont verify that
 * @note The complete initialized verification have to be do by a higher level function with memory
 * 
 * @param adc_oneshot_handle    The adc oneshot handle
 * @param n_channels            The number of channels
 * @param adc_channels          A pointer to the adc channels array
 * @param lectures              A pointer to the lectures array
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_read_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels, int *lectures);


/**
 * INTERNAL LOGIC FUNCTIONS
 */

// ------------------------------ CONVERSION LECTURE TO VOLTAGE ------------------------------

/**
 * @brief Internal Function to convert lecture to voltage with the user global macros
 * 
 * @param lecture       The analog lecture with bit resolution D_P_ADC_ONESHOT_CHANNELS_BITWIDTH
 * @return              The voltage maped from the lecture with attenuated D_P_ADC_ONESHOT_CHANNELS_ATTEN
 */
float d_p_adc_oneshot_internal_lecture_to_voltage(int lecture);

// ------------------------------ CONVERSION ARRAY OF LECTURES TO ARRAY OF VOLTAGE ------------------------------

/**
 * @brief Internal Function to convert array of lectures to array of voltages
 * 
 * @param n             The number of channels / lectures / voltages
 * @param lectures      A pointer to the analog lectures array
 * @param voltages      A pointer the voltages array to override
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_lectures_to_voltages(size_t n, int* lectures, float* voltages);


#ifdef __cplusplus
}
#endif