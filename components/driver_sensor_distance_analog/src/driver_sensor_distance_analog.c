#include <driver_sensor_distance_analog.h>
#include <d_s_distance_analog_internal.h>


// SETUP

esp_err_t d_s_distance_analog_setup()
{
    // SETUP ADC ONESHOT
    ESP_ERROR_CHECK(d_p_adc_oneshot_setup(&d_s_distance_analog_adc_oneshot_config));
    return ESP_OK;
}

// READ DISTANCES

esp_err_t d_s_distance_analog_read_distances(float *distances)
{
    // GET LECTURES WITH THE DRIVER PERIPHERAL ADC ONESHOT
    int* lectures = (int*) malloc(d_s_distance_analog_adc_oneshot_config.n_channels * sizeof(int));
    ESP_ERROR_CHECK(d_p_adc_oneshot_read(&d_s_distance_analog_adc_oneshot_config, lectures));

    // CONVERT LECTURE TO DISTANCES AND WRITE IN THE ARRAY
    d_s_distance_analog_internal_lectures_to_distances(d_s_distance_analog_adc_oneshot_config.n_channels, lectures, distances);

    free(lectures);

    return ESP_OK;
}

// KILL

esp_err_t d_s_distance_analog_kill()
{
    // KILL ADC ONESHOT
    ESP_ERROR_CHECK(d_p_adc_oneshot_kill(&d_s_distance_analog_adc_oneshot_config));

    return ESP_OK;
}
