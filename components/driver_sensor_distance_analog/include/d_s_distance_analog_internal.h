#pragma once
#include <driver_peripheral_adc_oneshot.h>
#include <d_s_distance_analog_config.h>


// CONVERSION LECTURE TO VOLTAGE

/**
 * @brief Internal Function to convert lecture to voltage
 * 
 * @param lecture   The analog lecture with bit resolution D_P_ADC_ONESHOT_CHANNELS_BITWIDTH
 * @return          The voltage maped from the lecture with attenuated D_P_ADC_ONESHOT_CHANNELS_ATTEN
 */
float d_s_distance_analog_internal_lecture_to_voltage(int lecture);

/**
 * @brief Internal Function to convert array of lectures to array of voltages
 * 
 * @param lectures  A pointer to the analog lectures array
 * @param voltages  A pointer the voltages array to override
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_internal_lectures_to_voltages(size_t n, int* lectures, float* voltages);


// CONVERSION LECTURES TO DISTANCE

/**
 * @brief Internal Function to convert array of lectures to array of distances
 * 
 * @param lectures      A pointer to the analog lectures array
 * @param distances     A pointer the distances array to override
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_s_distance_analog_internal_lectures_to_distances(size_t n, int* lectures, float* distances);