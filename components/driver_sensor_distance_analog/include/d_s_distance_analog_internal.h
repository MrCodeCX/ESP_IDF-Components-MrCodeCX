#pragma once
#include <driver_peripheral_adc_oneshot.h>
#include <d_s_distance_analog_config.h>


/**
 * INTERNAL LOGIC FUNCTIONS
 */

// ------------------------------ CONVERSION ARRAY OF VOLTAGES TO ARRAY OF DISTANCES ------------------------------

/**
 * @brief Internal Function to convert array of voltages to array of distances
 * 
 * @param f_conversion  The conversion function to be used by the function
 * @param n             The number of channels / lectures / voltages
 * @param voltages      A pointer to the voltages array
 * @param distances     A pointer the distances array to override
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_internal_voltages_to_distances(d_s_distance_analog_conversion f_conversion, size_t n, float *voltages, float* distances);
