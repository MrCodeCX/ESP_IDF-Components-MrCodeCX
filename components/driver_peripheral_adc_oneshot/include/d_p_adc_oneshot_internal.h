#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>

#ifdef __cplusplus
extern "C" {
#endif



/**
 * INTERNAL HARDWARE FUNCTIONS
 */


// SETUP

/**
 * @brief Internal Function to setup the handle for the adc unit with the global config
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

/**
 * @brief Internal Function to setup the adc channels with the global config
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


// KILL

/**
 * @brief Internal Function to kill the handle for the adc unit, dosent exits a function to kill the channels.
 * This is because the channels objets are only configurations.
 * And this configuratiosn can be override at even moment, without needing a kill cleaning function before.
 * 
 * @note The adc oneshot handle has to be initialized first, at least it have to be diferent that null, the function verifys it by itself
 * @note The complete initialized verification have to be do by a higher level function with memory
 * 
 * @param adc_oneshot_handle    A pointer to the adc oneshot handle that has to be killed by the function, and will be override with NULL
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_kill_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle);


// READ

/**
 * @brief Internal Function to read the value for multiple channels
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
esp_err_t d_p_adc_oneshot_internal_read_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels, int* lectures);



#ifdef __cplusplus
}
#endif