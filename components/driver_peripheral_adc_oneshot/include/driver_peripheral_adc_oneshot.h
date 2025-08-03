#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>


#define D_P_ADC_ONESHOT_MAX_CHANNELS 12


// CONFIG STRUCTURE

typedef struct {
    adc_unit_t adc_unit;                                                    // ADC UNIT
    size_t n_channels;                                                      // N CHANNELS
    adc_channel_t adc_channels[D_P_ADC_ONESHOT_MAX_CHANNELS];               // ADC CHANNELS
    adc_oneshot_unit_handle_t* _private_pointer_to_adc_oneshot_handle;      // PRIVATE POINTER TO ADC HANDLE
    bool _private_init_state;                                               // PRIVATE STATE FOR THIS CONFIG
} d_p_adc_oneshot_cfg_t;

typedef d_p_adc_oneshot_cfg_t* d_p_adc_oneshot_cfg_handle_t;


// SETUP

/**
 * @brief API User Function to total setup for a d_p_adc_oneshot_cfg_t
 * 
 * @note The user just can use one d_p_adc_oneshot_cfg_t per a combination of adc_unit and adc_channels
 * @note It have to be used just one time for a dp_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_setup(d_p_adc_oneshot_cfg_handle_t config_handle);


// KILL

/**
 * @brief API User Function to total kill for a d_p_adc_oneshot_cfg_t
 * 
 * @note This function have to be called after update the global states (erase) for the d_p_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_kill(d_p_adc_oneshot_cfg_handle_t config_handle);


// READ

/**
 * @brief API User Function to read the channels declarated in a d_p_adc_oneshot_cfg_t, It verifys a valid state of config by itself
 * 
 * @param config The d_p_adc_oneshot_cfg_t
 * @param lectures A pointer to the lectures array
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_read(d_p_adc_oneshot_cfg_handle_t config_handle, int* lectures);




// INTERNAL MANAGE FUNCTIONS

// SETUP VERIFY STATE

/**
 * @brief Internal Manage Function to verify if a adc unit handle config can be initialized
 * 
 * @param config The d_p_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_handle_state(d_p_adc_oneshot_cfg_handle_t config_handle);

/**
 * @brief Internal Manage Function to verify if a channels config can be initialized
 * 
 * @note This function is used because you can initialized new channels with a new config after other previous initialization if the channels are diferent
 * 
 * @param config The d_p_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_setup_verify_channels_state(d_p_adc_oneshot_cfg_handle_t config_handle);


// REGISTER AND ERASE GLOBAL STATE

/**
 * @brief Internal Manage Function to register a global state
 * 
 * @param config The d_p_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_register_global_state(d_p_adc_oneshot_cfg_handle_t config_handle);

/**
 * @brief Internal Manage Function to erase a global state
 * 
 * @note Another low level function have to use the new states to rewrite the adc handles with the adc oneshot api
 * 
 * @param config The d_p_adc_oneshot_cfg_t
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_internal_manage_erase_global_state(d_p_adc_oneshot_cfg_handle_t config_handle);
