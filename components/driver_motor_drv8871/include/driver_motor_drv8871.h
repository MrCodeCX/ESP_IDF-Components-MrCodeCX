#pragma once
#include <driver/mcpwm.h>
#include <d_m_drv8871_config.h>


/**
 * API FUNCTIONS to be used by the user with his own config handle (d_p_adc_oneshot_cfg_handle_t) declared in config.h
 */

// ------------------------------ SETUP ------------------------------

/**
 * @brief API User Function to setup the driver
 * 
 * @note This Function have to be called only one time
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_setup();

// ------------------------------ WRITE ------------------------------

/**
 * @brief API User Function to write to the 2 drivers motors a and b
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_write(float write_a, float write_b);