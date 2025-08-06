#include <d_p_adc_oneshot_internal_manage.h>


/**
 * INTERNAL MANAGE GLOBAL VARIABLES
 */

// Global Handles

adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_1 = NULL;
adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_2 = NULL;

// Global States

bool d_p_adc_oneshot_handle_state_1 = false;
bool d_p_adc_oneshot_handle_state_2 = false;
bool d_p_adc_oneshot_channels_state_1[D_P_ADC_ONESHOT_CONST_MAX_CHANNELS] = {false};
bool d_p_adc_oneshot_channels_state_2[D_P_ADC_ONESHOT_CONST_MAX_CHANNELS] = {false};


/**
 * INTERNAL MANAGE FUNCTIONS
 */

// SETUP VERIFY STATE

esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_handle_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // Parameters Verification, Verify if the adc_unit is valid
    if(config_handle->adc_unit != ADC_UNIT_1 && config_handle->adc_unit != ADC_UNIT_2) return ESP_ERR_INVALID_ARG;

    // State Verification, Verify if the unit handle is uninitialized, with the global states (strong)
    if(config_handle->adc_unit == ADC_UNIT_1 && d_p_adc_oneshot_handle_state_1) return ESP_ERR_INVALID_STATE;
    if(config_handle->adc_unit == ADC_UNIT_2 && d_p_adc_oneshot_handle_state_2) return ESP_ERR_INVALID_STATE;
    
    // Return
    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_channels_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // Parameters Verification, Verify if the adc_unit is valid and if the number of channels is valid
    if(config_handle->adc_unit != ADC_UNIT_1 && config_handle->adc_unit != ADC_UNIT_2) return ESP_ERR_INVALID_ARG;
    if(config_handle->n_channels <= 0) return ESP_ERR_INVALID_ARG;

    // State Verification, Verify if global channels are uninitialized, with the global states (strong), for handle 1 if it is
    if(config_handle->adc_unit == ADC_UNIT_1) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            // If one of the global channels for this config is initialized return an invalid state
            if(d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]]) return ESP_ERR_INVALID_STATE;
        }
    }

    // State Verification, Verify if global channels are uninitialized, with the global states (strong), for handle 2 if it is
    else if(config_handle->adc_unit == ADC_UNIT_1) {
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            // If one of the global channels for this config is initialized return an invalid state
            if(d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]]) return ESP_ERR_INVALID_STATE;
        }
    }

    // Return
    return ESP_OK;
}


// REGISTER AND ERASE GLOBAL STATE

esp_err_t d_p_adc_oneshot_internal_manage_register_global_state(d_p_adc_oneshot_cfg_handle_t config_handle)
{
    // Register the global state for hanfle 1 if it is (without verifications)
    if(config_handle->adc_unit == ADC_UNIT_1) {
        d_p_adc_oneshot_handle_state_1 = true;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_1[config_handle->adc_channels[i]] = true;
        }
        
    }

    // Register the global state for hanfle 2 if it is (without verifications)
    else if(config_handle->adc_unit == ADC_UNIT_2) {
        d_p_adc_oneshot_handle_state_2 = true;
        for (size_t i = 0; i < config_handle->n_channels; i++)
        {
            d_p_adc_oneshot_channels_state_2[config_handle->adc_channels[i]] = true;
        }
        
    }

    // Return
    return ESP_OK;
}

esp_err_t d_p_adc_oneshot_internal_manage_erase_global_state(d_p_adc_oneshot_cfg_handle_t config_handle, bool *needed_handle)
{
    // Erase the global state, but another low level function will have to receibe the handle_needed flag to delete the global handle
    
    // Erase the global state for handle 1 if it is
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

        // Override the needed_handle flag
        *needed_handle = handle_needed;
    }

    // Erase the global state for handle 2 if it is
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
        
        // Override the needed_handle flag
        *needed_handle = handle_needed;
    }

    // Return
    return ESP_OK;
}