#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>

#ifdef __cplusplus
extern "C" {
#endif



/**
 * INTERNAL MANAGE GLOBAL VARIABLES
 */

// Global Handles

extern adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_1;
extern adc_oneshot_unit_handle_t d_p_adc_oneshot_handle_2;

// Global States

extern bool d_p_adc_oneshot_handle_state_1;
extern bool d_p_adc_oneshot_handle_state_2;
extern bool d_p_adc_oneshot_channels_state_1[D_P_ADC_ONESHOT_CONST_MAX_CHANNELS];
extern bool d_p_adc_oneshot_channels_state_2[D_P_ADC_ONESHOT_CONST_MAX_CHANNELS];


/**
 * INTERNAL MANAGE FUNCTIONS, these never override directly the global handles, only the global states
 */


// SETUP VERIFY STATE

/**
 * @brief Internal Manage Function to verify if a adc unit handle config can be initialized
 * 
 * @param config The d_p_adc_oneshot_cfg_handle_t to be used for the verification 
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_handle_state(d_p_adc_oneshot_cfg_handle_t config_handle);

/**
 * @brief Internal Manage Function to verify if a channels config can be initialized
 * 
 * @note This function is used because you can initialized new channels with a new config after other previous initialization if the channels are diferent
 * But if the channels are repeated, it could generate configurations problems, and that isnt allowed by this driver
 * 
 * @param config The d_p_adc_oneshot_cfg_handle_t to be used for the verification 
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_channels_state(d_p_adc_oneshot_cfg_handle_t config_handle);


// REGISTER AND ERASE GLOBAL STATE

/**
 * @brief Internal Manage Function to register a global state
 * 
 * @param config The d_p_adc_oneshot_cfg_handle_t to be used for register the global state, it have to be call after verification
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_register_global_state(d_p_adc_oneshot_cfg_handle_t config_handle);

/**
 * @brief Internal Manage Function to erase a global state
 * 
 * @note Another low level function have to use the new states to rewrite the adc handles with the adc oneshot api
 * 
 * @param config            The d_p_adc_oneshot_cfg_handle_t to be used for erase his global state
 * @param needed_handle     A pointer to the needed_handle flag, to be override by the function
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_erase_global_state(d_p_adc_oneshot_cfg_handle_t config_handle, bool *needed_handle);



#ifdef __cplusplus
}
#endif