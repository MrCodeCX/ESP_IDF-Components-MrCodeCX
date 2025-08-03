#include <d_s_distance_analog_internal.h>

float d_s_distance_analog_internal_lecture_to_voltage(int lecture)
{
    float distance = lecture;
    distance = (distance * D_P_ADC_ONESHOT_CHANNELS_VOLTAGE_MAX) / D_P_ADC_ONESHOT_CHANNELS_LECTURE_MAX;
    return distance;
}

esp_err_t d_s_distance_analog_internal_lectures_to_voltages(size_t n, int *lectures, float *voltages)
{
    for (size_t i = 0; i < n; i++)
    {
        voltages[i] = d_s_distance_analog_internal_lecture_to_voltage(lectures[i]);
    }
    
    return ESP_OK;
}

esp_err_t d_s_distance_analog_internal_lectures_to_distances(size_t n, int *lectures, float *distances)
{
    // CREATE VOLTAGES ARRAY AND FILL FROM LECTURES TO VOLTAGES CONVERSION
    float* voltages = (float*) malloc(d_s_distance_analog_adc_oneshot_config.n_channels * sizeof(float));
    ESP_ERROR_CHECK(d_s_distance_analog_internal_lectures_to_voltages(n, lectures, voltages));

    // CONVERT VOLTAGES TO DISTANCES
    for (size_t i = 0; i < n; i++)
    {
        distances[i] = D_S_DISTANCE_ANALOG_VOLTAGE_TO_DISTANCE(voltages[i]);
    }
    
    // FREE MEMORY
    free(voltages);

    return ESP_OK;
}
