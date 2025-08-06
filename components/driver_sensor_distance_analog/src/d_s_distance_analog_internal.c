#include <d_s_distance_analog_internal.h>


/**
 * INTERNAL LOGIC FUNCTIONS
 */

// ------------------------------ CONVERSION ARRAY OF LECTURES TO ARRAY OF DISTANCES ------------------------------

esp_err_t d_s_distance_analog_internal_voltages_to_distances(d_s_distance_analog_conversion_t f_conversion, size_t n, float *voltages, float* distances)
{
    // Convert each voltage to distance
    for (size_t i = 0; i < n; i++)
    {
        distances[i] = f_conversion(voltages[i]);
    }

    // Return
    return ESP_OK;
}
