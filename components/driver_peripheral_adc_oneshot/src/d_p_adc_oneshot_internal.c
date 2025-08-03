#include <d_p_adc_oneshot_internal.h>


// SETUP

esp_err_t d_p_adc_oneshot_internal_setup_handle(adc_oneshot_unit_handle_t* adc_oneshot_handle, adc_unit_t adc_unit)
{
    // SETUP ADC UNIT
    adc_oneshot_unit_init_cfg_t handle_config = {
        .unit_id = adc_unit,                    // ADC UNIT, PREFERLY USE 1 FOR SAFETY
        .ulp_mode = D_P_ADC_ONESHOT_ULP_MODE,   // GLOBAL CONFIG ULTRA LOW POWER MODE
        .clk_src = D_P_ADC_ONESHOT_CLK_SRC      // GLOBAL CONFIG CLOCK
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&handle_config, adc_oneshot_handle));
    
    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_setup_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels)
{
    // PARAMETERS VERIFICATION
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_ARG;

    // SETUP CHANNELS
    adc_oneshot_chan_cfg_t channels_config = {
        .atten = D_P_ADC_ONESHOT_CHANNELS_ATTEN,        // GLOBAL CONFIG ATTENUATED
        .bitwidth = D_P_ADC_ONESHOT_CHANNELS_BITWIDTH,  // GLOBAL CONFIG BIT RESOLUTION
    };

    for (size_t i = 0; i < n_channels; i++)
    {
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_oneshot_handle, adc_channels[i], &channels_config));
    }

    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_kill_handle(adc_oneshot_unit_handle_t adc_oneshot_handle)
{
    // VERIFY IF THE HANDLE EXITS
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_STATE;

    // KILL THE UNIT HANDLE
    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc_oneshot_handle));

    return ESP_OK;
}

// READ

esp_err_t d_p_adc_oneshot_internal_read_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels, int *lectures)
{
    // PARAMETERS VERIFICATION
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_ARG;

    // READ CHANNELS
    for (size_t i = 0; i < n_channels; i++)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(adc_oneshot_handle, adc_channels[i], (lectures + i)));
    }

    return ESP_OK;
}
