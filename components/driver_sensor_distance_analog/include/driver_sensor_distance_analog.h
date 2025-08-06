#pragma once
#include <driver_peripheral_adc_oneshot.h>
#include <d_s_distance_analog_config.h>
#include <d_s_distance_analog_conversions.h>


/**
 * API FUNCTIONS to be used by the user with his own config handle (d_s_distance_analog_cfg_handle_t) declared in config.h
 */

// ------------------------------ SETUP ------------------------------

/**
 * @brief API User Function to total setup for the config handle
 * 
 * @note You can use a config handle with adc gpios from adc unit 1 and adc unit 2
 * The one restriction is that two config handles can never have a common gpio sensor pin it will be a fatal error
 * @note It have to be used with a config handle uninitialized
 * @note It have to be used just one time for a config handle
 * If you kill your config handle, you will can use setup again
 * 
 * @param d_s_distance_analog_cfg_handle_t  The config handle
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_setup(d_s_distance_analog_cfg_handle_t config_handle);


// ------------------------------ READ DISTANCES ------------------------------

/**
 * @brief API User Function to read the distances readed from each analog sensor of the config handle
 * 
 * @param d_s_distance_analog_cfg_handle_t  The config handle
 * @param distances                         A pointer to the distances array to be override by this function
 * 
 * @return  esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_read_distances(d_s_distance_analog_cfg_handle_t config_handle, float *distances);

// ------------------------------ KILL ------------------------------

/**
 * @brief API User Function to total kill for the config handle
 * 
 * @note It have to be used with a config handle initialized
 * @note It have to be used just one time for a config handle
 * If you kill your config handle, you will can use setup again
 * 
 * @param d_s_distance_analog_cfg_handle_t  The config handle
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_kill(d_s_distance_analog_cfg_handle_t config_handle);
