#include <d_p_adc_oneshot_internal.h>


/**
 * INTERNAL HARDWARE FUNCTIONS
 */

// ------------------------------ SETUP HANDLE ------------------------------

esp_err_t d_p_adc_oneshot_internal_setup_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle, adc_unit_t adc_unit)
{
    // State Verification, Verify if the unit handle dosent exits (weak)
    if(adc_oneshot_handle != NULL) return ESP_ERR_INVALID_STATE;

    // Create the unit config
    adc_oneshot_unit_init_cfg_t handle_config = {
        .unit_id = adc_unit,                    // ADC UNIT, PREFERLY USE 1 FOR SAFETY
        .ulp_mode = D_P_ADC_ONESHOT_ULP_MODE,   // GLOBAL CONFIG ULTRA LOW POWER MODE
        .clk_src = D_P_ADC_ONESHOT_CLK_SRC      // GLOBAL CONFIG CLOCK
    };

    // Setup the unit handle
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&handle_config, adc_oneshot_handle));
    
    // Return
    return ESP_OK;
}

// ------------------------------ SETUP CHANNELS------------------------------

esp_err_t d_p_adc_oneshot_internal_setup_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels)
{
    // State Verification, Verify if the unit handle exits (weak)
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_STATE;

    // Create the channels config
    adc_oneshot_chan_cfg_t channels_config = {
        .atten = D_P_ADC_ONESHOT_CHANNELS_ATTEN,        // GLOBAL CONFIG ATTENUATED
        .bitwidth = D_P_ADC_ONESHOT_CHANNELS_BITWIDTH,  // GLOBAL CONFIG BIT RESOLUTION
    };

    // Setup the channels config
    for (size_t i = 0; i < n_channels; i++)
    {
        ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_oneshot_handle, adc_channels[i], &channels_config));
    }

    // Return
    return ESP_OK;
}

// ------------------------------ KILL ------------------------------

esp_err_t d_p_adc_oneshot_internal_kill_handle(adc_oneshot_unit_handle_t *adc_oneshot_handle)
{
    // State Verification, Verify if the unit handle exits (weak)
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_STATE;

    // Kill the unit handle
    ESP_ERROR_CHECK(adc_oneshot_del_unit(*adc_oneshot_handle));

    // Override the handle with NULL
    *adc_oneshot_handle = NULL;

    // Return
    return ESP_OK;
}

// ------------------------------ READ CHANNELS (INT LECTURES) ------------------------------

esp_err_t d_p_adc_oneshot_internal_read_channels(adc_oneshot_unit_handle_t adc_oneshot_handle, size_t n_channels, adc_channel_t *adc_channels, int *lectures)
{
    // State Verification, Verify if the unit handle exits (weak)
    if(adc_oneshot_handle == NULL) return ESP_ERR_INVALID_STATE;

    // Read the channels
    for (size_t i = 0; i < n_channels; i++)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(adc_oneshot_handle, adc_channels[i], (lectures + i)));
    }

    // Return
    return ESP_OK;
}


/**
 * INTERNAL LOGIC FUNCTIONS
 */

// ------------------------------ CONVERSION LECTURE TO VOLTAGE ------------------------------

float d_p_adc_oneshot_internal_lecture_to_voltage(int lecture)
{
    // Convert lecture to voltage with the user global macros
    float voltage = lecture;
    voltage = (voltage * D_P_ADC_ONESHOT_CHANNELS_VOLTAGE_MAX) / D_P_ADC_ONESHOT_CHANNELS_LECTURE_MAX;

    // Return
    return voltage;
}

// ------------------------------ CONVERSION ARRAY OF LECTURES TO ARRAY OF VOLTAGE ------------------------------

esp_err_t d_p_adc_oneshot_internal_lectures_to_voltages(size_t n, int *lectures, float *voltages)
{
    // Convert each lecture to voltage
    for (size_t i = 0; i < n; i++)
    {
        voltages[i] = d_p_adc_oneshot_internal_lecture_to_voltage(lectures[i]);
    }
    
    // Return
    return ESP_OK;
}
