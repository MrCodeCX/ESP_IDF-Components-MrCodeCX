#pragma once
#include <driver/mcpwm.h>
#include <d_m_drv8871_config.h>

#define D_M_DRV8871_PWM_MIN 0
#define D_M_DRV8871_PWM_MAX 100


/**
 * INTERNAL HARDWARE FUNCTIONS
 */

// INTERNAL LOGIC

/**
 * @brief Internal Logic Function, constrain
 */
#define d_m_drv8871_internal_constrain(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

/**
 * @brief Internal Logic Function, map a value betwen two new limits
 */
float d_m_drv8871_internal_map(float value, float fromLow, float fromHigh, float toLow, float toHigh);


// INTERNAL MAP

/**
 * @note OVERRIDE -> If you want a other mode, change the function d_m_drv8871_internal_map_pwm_mode_ that is called
 * 
 * @brief Internal Function usefull to map the pwm percent to the pwm mode
 * 
 * @param value The value to map, it have to be between -1 and 1, and the will be maped between D_M_DRV8871_PWM_MIN and D_M_DRV8871_PWM_MAX
 * @return The float value maped, duty cicle direct to insert in a mcpwm write function
 * 
 * @see d_m_drv8871_internal_map_pwm_mode_up (default)
 * 
 * @see d_m_drv8871_internal_constrain
 */
float d_m_drv8871_internal_map_pwm(float value);

/**
 * @brief Internal Function default to map pwm UP MODE
 * 
 * @see d_m_drv8871_internal_map
 */
float d_m_drv8871_internal_map_pw_mode_up(float value);


// INTERNAL SETUP

/**
 * @note OVERRIDE -> If you want a other mode, change the function d_m_drv8871_internal_setup_mcpwm_mode_ that is called
 * 
 * @brief Internal Function to total setup for the mcpwm
 * 
 * @return esp_err_t ESP_OK
 * 
 * @see d_m_drv8871_internal_setup_mcpwm_mode_up (default)
 */
esp_err_t d_m_drv8871_internal_setup_mcpwm();

/**
 * @brief Internal Function default to total setup for the mcpwm UP MODE
 * 
 * @return esp_err_t ESP_OK
 * 
 * @see d_m_drv8871_internal_setup_mcpwm_init_mode_up
 * @see d_m_drv8871_internal_setup_mcpwm_gpio_init_mode_up
 */
esp_err_t d_m_drv8871_internal_setup_mcpwm_mode_up();

/**
 * @brief Internal Function default init setup for the mcpwm UP MODE
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_setup_mcpwm_init_mode_up();

/**
 * @brief Internal Function default gpio init setup for the mcpwm UP MODE
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_setup_mcpwm_gpio_init_mode_up();


// INTERNAL WRITE MOTOR A

/**
 * @brief Internal Function to write motor a positive direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_a_positive_mode_up(float duty);

/**
 * @brief Internal Function to write motor a negative direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_a_negative_mode_up(float duty);

/**
 * @brief Internal Function to write motor a negative direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_a_zero_mode_up(float duty);


// INTERNAL WRITE MOTOR B

/**
 * @brief Internal Function to write motor b positive direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_b_positive_mode_up(float duty);

/**
 * @brief Internal Function to write motor b negative direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_b_negative_mode_up(float duty);

/**
 * @brief Internal Function to write motor b negative direction, with duty cicle, for the mcpwm MODE UP
 * 
 * @return esp_err_t ESP_OK
 */
esp_err_t d_m_drv8871_internal_write_motor_b_zero_mode_up(float duty);