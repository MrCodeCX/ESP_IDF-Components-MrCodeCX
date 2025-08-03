#include <driver_peripheral_adc_oneshot.h>
#include <d_p_adc_oneshot_internal.h>
#include <esp_log.h>

// Global Handles
static adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_1 = NULL;
static adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_2 = NULL;
// Global States
static bool d_p_adc_oneshot_handle_state_1 = false;
static bool d_p_adc_oneshot_handle_state_2 = false;
static bool d_p_adc_oneshot_channels_state_1[D_P_ADC_ONESHOT_MAX_CHANNELS] = {false};
static bool d_p_adc_oneshot_channels_state_2[D_P_ADC_ONESHOT_MAX_CHANNELS] = {false};


// SETUP

esp_err_t d_p_adc_oneshot_setup(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // SETUP VERIFICATION (IT ALSO VERIFY PARAMETERS)
    esp_err_t err_handle = d_p_adc_oneshot_internal_manage_setup_verify_handle_state(config_handle);
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_setup_verify_channels_state(config_handle));
    // If the handle is inited, you also can init a new config if the channels are diferent, but if channels are inited is a fatal error.

    // SELECT THE HANDLE
    if(config_handle->adc_unit == ADC_UNIT_1) config_handle->_private_pointer_to_adc_oneshot_handle = &d_p_adc_oneshot_handle_1;
    else if(config_handle->adc_unit == ADC_UNIT_2) config_handle->_private_pointer_to_adc_oneshot_handle = &d_p_adc_oneshot_handle_2;

    // SETUP ADC UNIT IF ITS NEEDED
    if(err_handle == ESP_OK) ESP_ERROR_CHECK(d_p_adc_oneshot_internal_setup_handle(config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->adc_unit));

    // SETUP CHANNELS ALWAYS
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_setup_channels(*config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->n_channels, config_handle->adc_channels));

    // Register the private state
    config_handle->_private_init_state = true;

    // Register the global state
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_register_global_state(config_handle));

    return ESP_OK;
}

// KILL

esp_err_t d_p_adc_oneshot_kill(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // RETURN IF THE HANDLE WAS KILLED BEFORE O WAS NEVER INITIALIZED
    if(config_handle->_private_init_state == false) return ESP_ERR_INVALID_STATE;

    // ERASE GLOBAL STATE
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_manage_erase_global_state(config_handle));

    // VERIFY IF NOW IS NEEDED THE HANDLE
    bool needed_handle = true;
    if(config_handle->adc_unit == ADC_UNIT_1 && d_p_adc_oneshot_handle_state_1 == false) needed_handle = false;
    if(config_handle->adc_unit == ADC_UNIT_2 && d_p_adc_oneshot_handle_state_2 == false) needed_handle = false;

    // IF IT ISNT NEEDED THEN KILL THE HANDLE
    if(needed_handle == false) ESP_ERROR_CHECK(d_p_adc_oneshot_internal_kill_handle(*config_handle->_private_pointer_to_adc_oneshot_handle));

    // ERASE THE PRIVATE STATE
    config_handle->_private_init_state = false;
    *config_handle->_private_pointer_to_adc_oneshot_handle = NULL;

    return ESP_OK;
}

// READ

esp_err_t d_p_adc_oneshot_read(d_p_adc_oneshot_cfg_handle_t config_handle, int *lectures)
{
    // VERIFY THE STATE
    if(config_handle->_private_init_state == false) return ESP_ERR_INVALID_STATE;

    // READ THE CHANNELS
    ESP_ERROR_CHECK(d_p_adc_oneshot_internal_read_channels(*config_handle->_private_pointer_to_adc_oneshot_handle, config_handle->n_channels, config_handle->adc_channels, lectures));

    return ESP_OK;
}




// INTERNAL MANAGE FUNCTIONS

// SETUP VERIFY STATE

esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_handle_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // VERIFY PARAMETERS
    if(config_handle->adc_unit != ADC_UNIT_1 && config_handle->adc_unit != ADC_UNIT_2) return ESP_ERR_INVALID_ARG;

    // VERIFY THE GLOBAL HANDLE IS UNITIALIZED
    if(config_handle->adc_unit == ADC_UNIT_1 && d_p_adc_oneshot_handle_state_1) return ESP_ERR_INVALID_STATE;
    if(config_handle->adc_unit == ADC_UNIT_2 && d_p_adc_oneshot_handle_state_2) return ESP_ERR_INVALID_STATE;
    
    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_channels_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // VERIFY PARAMETERS
    if(config_handle->adc_unit != ADC_UNIT_1 && config_handle->adc_unit != ADC_UNIT_2) return ESP_ERR_INVALID_ARG;
    if(config_handle->n_channels <= 0) return ESP_ERR_INVALID_ARG;

    // VERIFY THE GLOBAL CHANNELS ARE UNITIALIZED, FOR HANDLE 1 IF IT IS THE CONFIG
    if(config_handle->adc_unit == ADC_UNIT_1) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            // IF ONE OF THE GLOBAL CHANNEL FOR THIS CONFIG IS INITIALIZED IS A INVALID STATE
            if(d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]]) return ESP_ERR_INVALID_STATE;
        }
    }

    // VERIFY THE GLOBAL CHANNELS ARE UNITIALIZED, FOR HANDLE 2 IF IT IS THE CONFIG
    else if(config_handle->adc_unit == ADC_UNIT_1) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            // IF ONE OF THE GLOBAL CHANNEL FOR THIS CONFIG IS INITIALIZED IS A INVALID STATE
            if(d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]]) return ESP_ERR_INVALID_STATE;
        }
    }

    return ESP_OK;
}


// REGISTER AND ERASE GLOBAL STATE

esp_err_t d_p_adc_oneshot_internal_manage_register_global_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // REGISTER THE GLOBAL STATE
    if(config_handle->adc_unit == ADC_UNIT_1) {
        d_p_adc_oneshot_handle_state_1 = true;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]] = true;
        }
        
    }
    else if(config_handle->adc_unit == ADC_UNIT_2) {
        d_p_adc_oneshot_handle_state_2 = true;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]] = true;
        }
        
    }
    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_manage_erase_global_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // ERASE THE GLOBAL STATE
    // ANOTHER LOW LEVEL FUNCTION WILL HAVE TO DELETE THE HANDLES WITH THE ADC HANDLE API
    if(config_handle->adc_unit == ADC_UNIT_1) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]] = false;
        }

        bool handle_needed = false;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            if(d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]]) {
                handle_needed = true;
                break;
            }
        }
        if(handle_needed == false) d_p_adc_oneshot_handle_state_1 = false;
        
    }
    else if(config_handle->adc_unit == ADC_UNIT_2) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]] = false;
        }

        bool handle_needed = false;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            if(d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]]) {
                handle_needed = true;
                break;
            }
        }
        if(handle_needed == false) d_p_adc_oneshot_handle_state_2 = false;
        
    }
    return ESP_OK;
}

