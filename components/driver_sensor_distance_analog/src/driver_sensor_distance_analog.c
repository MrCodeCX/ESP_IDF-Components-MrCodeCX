#include <driver_sensor_distance_analog.h>
#include <d_s_distance_analog_internal.h>


/**
 * API FUNCTIONS to be used by the user with his own config handle (d_s_distance_analog_cfg_handle_t) declared in config.h
 */

// ------------------------------ SETUP ------------------------------

esp_err_t d_s_distance_analog_setup(d_s_distance_analog_cfg_handle_t config_handle)
{
    // Setup adc oneshot config
    ESP_ERROR_CHECK(d_p_adc_oneshot_setup(&config_handle->adc_oneshot_cfg));

    // Return
    return ESP_OK;
}

// ------------------------------ READ DISTANCES ------------------------------

esp_err_t d_s_distance_analog_read_distances(d_s_distance_analog_cfg_handle_t config_handle, float *distances)
{
    // Create temporary voltages array in the stack (more efficient than heap, and never satures the memory because the max size is short)
    float voltages[D_P_ADC_ONESHOT_CONST_MAX_CHANNELS];

    // Get voltages with the driver peripheral adc oneshot
    ESP_ERROR_CHECK(d_p_adc_oneshot_read(&config_handle->adc_oneshot_cfg, voltages));

    // Convert voltages to distances and override it in the distances array
    ESP_ERROR_CHECK(d_s_distance_analog_internal_voltages_to_distances(config_handle->f_conversion, config_handle->adc_oneshot_cfg.n_channels, voltages, distances));

    // Return
    return ESP_OK;
}

// ------------------------------ KILL ------------------------------

esp_err_t d_s_distance_analog_kill(d_s_distance_analog_cfg_handle_t config_handle)
{
    // Kill adc oneshot config
    ESP_ERROR_CHECK(d_p_adc_oneshot_kill(&config_handle->adc_oneshot_cfg));

    return ESP_OK;
}
