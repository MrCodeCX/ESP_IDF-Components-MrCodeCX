#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>


// SETUP

/**
 * @brief Internal Function to setup the handle for the adc unit with default config
 * 
 * @note The adc oneshot handle has to be null, in fact, it have to be unitialized, the function verifys it by itself
 * 
 * @param adc_oneshot_handle    A pointer to the adc oneshot handle that has to be created and returned by the function
 * @param adc_unit              The adc unit to config
 * 
 * @return esp_err_t ESP_OK
 */

esp_err_t d_p_adc_oneshot_internal_setup_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle, adc_unit_t adc_unit);

/**
 * @brief Internal Function to setup the adc channels with default config
 * 
 * @note The adc oneshot handle has to be unitialized first, in facts it have to be diferent that null, the function verifys it by itself
 * 
 * @param adc_oneshot_handle    The adc oneshot handle
 * @param n_channels            The number of channels
 * @param adc_channels          A pointer to the adc channels array
 * 
 * @return esp_err_t ESP_OK
 */

esp_err_t d_p_adc_oneshot_internal_setup_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels);


// KILL USE NEEDED FOR HANDLE UNIT, DOSENT EXITS A FUNCTION TO KILL THE CHANNELS CONFIG

/**
 * @brief Internal Function to kill the handle for the adc unit
 * 
 * @note The adc oneshot handle has to exits before, in fact, it have to be initialized, the function verifys it by itself
 * 
 * @param adc_oneshot_handle    The adc oneshot handle that has to be killed by the function
 * 
 * @return esp_err_t ESP_OK
 */

esp_err_t d_p_adc_oneshot_internal_kill_handle(adc_oneshot_unit_handle_t adc_oneshot_handle);

// READ

/**
 * @brief Internal Function to read the value for multiple channels
 * 
 * @note The adc oneshot handle has to be unitialized first, in facts it have to be diferent that null, the function verifys it by itself
 * @note The channels have to be initialized first, but this function dont verify that, it have to be do by a higher level function
 * 
 * @param adc_oneshot_handle    The adc oneshot handle
 * @param n_channels            The number of channels
 * @param adc_channels          A pointer to the adc channels array
 * @param lectures              A pointer to the lectures array
 * 
 * @return esp_err_t ESP_OK
 */

esp_err_t d_p_adc_oneshot_internal_read_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels, int* lectures);