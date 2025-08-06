#pragma once
#include <esp_adc/adc_oneshot.h>
#include <d_p_adc_oneshot_config.h>

#ifdef __cplusplus
extern "C" {
#endif



/**
 * API FUNCTIONS to be used by the user with his own own handle of configuration (d_p_adc_oneshot_cfg_handle_t) declared in config.h
 */


// SETUP

/**
 * @brief API User Function to total setup for a d_p_adc_oneshot_cfg_t
 * 
 * @note The user just can use one d_p_adc_oneshot_cfg_t per a combination of adc_unit and adc_channels
 * Two configs with channels of the same unit in common are invalid arguments.
 * @note It have to be used just one time for a dp_adc_oneshot_cfg_handle_t.
 * If you kill your config handle, you will can use setup again
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_setup(d_p_adc_oneshot_cfg_handle_t config_handle);


// KILL

/**
 * @brief API User Function to total kill for a d_p_adc_oneshot_cfg_t
 * 
 * @note This function have to be called after do the setup for the d_p_adc_oneshot_cfg_t
 * @note It have to be used just one time for a dp_adc_oneshot_cfg_handle_t
 * If you kill your config handle, you will can use setup again
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_kill(d_p_adc_oneshot_cfg_handle_t config_handle);


// READ

/**
 * @brief API User Function to read the channels declarated in a d_p_adc_oneshot_cfg_t, It verifys a valid state of config by itself
 * 
 * @param config    The d_p_adc_oneshot_cfg_t
 * @param lectures  A pointer to the lectures array
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_p_adc_oneshot_read(d_p_adc_oneshot_cfg_handle_t config_handle, int* lectures);



#ifdef __cplusplus
}
#endif