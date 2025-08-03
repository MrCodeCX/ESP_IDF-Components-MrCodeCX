#pragma once
#include <driver_peripheral_adc_oneshot.h>
#include <d_s_distance_analog_config.h>


// SETUP

/**
 * @brief API User Function to total setup for the d_s_distance_analog_adc_oneshot_config
 * 
 * @note It have to be used just one time at the program
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_setup();


// READ DISTANCES

/**
 * @brief API User Function to read the distances readed from each analog sensor
 * 
 * @param distances     A pointer to the array of distances to override
 * 
 * @return  esp_err_t ESP_OK
 * 
 * @see D_S_DISTANCE_ANALOG_VOLTAGE_TO_DISTANCE macro in config
 */
esp_err_t d_s_distance_analog_read_distances(float* distances);

// KILL

/**
 * @brief API User Function to total kill for the d_s_distance_analog_adc_oneshot_config
 * 
 * @note It have to be used with a d_s_distance_analog_adc_oneshot_config initialized
 * @note This function is usefull to kill a sensors configuration to override an d_s_distance_analog_adc_oneshot_config and new setup configuration
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_kill();
