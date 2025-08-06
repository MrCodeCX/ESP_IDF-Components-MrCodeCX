#include <driver_peripheral_adc_oneshot.h>
#include <d_p_adc_oneshot_internal.h>
#include <d_p_adc_oneshot_internal_manage.h>


/**
 * API FUNCTIONS
 */

// SETUP

esp_err_t d_p_adc_oneshot_setup(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // Setup verifications state and parameters

    // ESP_OK if we have to create a new handle, other esp_err_t, if the handle is already created
    esp_err_t err_handle = d_p_adc_oneshot_internal_manage_setup_verify_handle_state(config_handle);
    // Just continue if the channels are a valid state to setup (not inited before)
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_setup_verify_channels_state(config_handle));

    // Setup general

    // Select the handle
    if(config_handle->adc_unit == ADC_UNIT_1) config_handle->_private_pointer_to_adc_oneshot_handle = &d_p_adc_oneshot_handle_1;
    else if(config_handle->adc_unit == ADC_UNIT_2) config_handle->_private_pointer_to_adc_oneshot_handle = &d_p_adc_oneshot_handle_2;

    // Setup adc unit handle if is needed
    if(err_handle == ESP_OK) ESP_ERROR_CHECK(d_p_adc_oneshot_internal_setup_handle(config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->adc_unit));

    // Setup channels
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_setup_channels(*config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->n_channels, config_handle->adc_channels));

    // Register the private state
    config_handle->_private_init_state = true;

    // Register the global state
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_register_global_state(config_handle));

    // Return
    return ESP_OK;
}

// KILL

esp_err_t d_p_adc_oneshot_kill(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // State Verification, Verify if the unit has been previous initialized (strong)
    if(config_handle->_private_init_state == false) return ESP_ERR_INVALID_STATE;

    // Erase the Global State and get the needed handle flag
    bool needed_handle;
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_erase_global_state(config_handle, &needed_handle));

    // If it isnt needed then kill the handle
    if(needed_handle == false) ESP_ERROR_CHECK(d_p_adc_oneshot_internal_kill_handle(config_handle->_private_pointer_to_adc_oneshot_handle));

    // Erase the private state
    config_handle->_private_init_state = false;
    // Erase to pointer to the global handle, then the config will can be reused
    config_handle->_private_pointer_to_adc_oneshot_handle = NULL;

    // Return
    return ESP_OK;
}

// READ

esp_err_t d_p_adc_oneshot_read(d_p_adc_oneshot_cfg_handle_t config_handle, int *lectures)
{
    // State Verification, Verify if the unit has been previous initialized (strong)
    if(config_handle->_private_init_state == false) return ESP_ERR_INVALID_STATE;

    // Read the channels to lectures
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_read_channels(*config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->n_channels, config_handle->adc_channels, lectures));

    // Return
    return ESP_OK;
}

