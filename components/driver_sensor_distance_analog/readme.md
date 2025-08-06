### DRIVER SENSOR DISTANCE ANALOG by MrCodeCX (Misael Fernandez Prada)

### BRIEF
    A COMPLETE EASY MANAGER FOR MULTIPLE ANALOG SENSOR DISTANCE LECTURES DEFINED BY A CONFIG HANDLE

### COMPONENT DEPENDS
    driver_peripheral_adc_oneshot from MrCodeCX components

### COMPATIBLE
    Language: C / C++
    Documentation: Doxygen


### DESCRIPTION

The drivers provides a simple deterministic api, just understand how to create your config handle, and provide your conversion function, and the driver will do all the rest with his setup, read, and kill functions.

The user can use multiple config handles at the same time, the one restriction is two config handles never can have channels of the same unit in common.

To create a config handle, the user have to provide an adc oneshot config instance, with his own adc unit, number of channels, and adc channels. Note that a config handle can only manage sensors of one adc unit, because only have one adc oneshot config element.

To provide the d_s_distance_analog_conversion_t f_conversion you can use one of the provided by the driver or just create a function of the shape float f_conversion (float), it will recieve a voltage (from 0 to 3.3V) and have to return the respectly distance (cm).

The default flag for d_s_distance_analog_conversion_t out of range and dead zone lectures is -1

Is neever needed to touch the configuration of the dependency driver_peripheral_adc_oneshot, at least you were using an esp32 variant (not classic)

Of course you also can use this driver to manage sensor distances with digital output, it isnt neceesay, and you can use other drivers specific for digital sensors (more efficient), but maybe for easy integration of multiples distances sensors, and etc, it could be a better option
Is for that reazon that the api provide conversion functions for some digital sensors


### PHILOSOPHY STRUCTURE (API AND INTERNAL)

The functions are divided in api functions, and internal functions

The api functions will be under the name component_api_function
The internal functions will be under the name component_internal_function

The user is just recomended to use the api functions, no one internal function is included by default when includind the component header
This is because the internal functions depends of low level logic and macros, and usually global memory objects

### PHILOSOPHY ERROR (ROBUST)

A simple function is one who return a direct value, are usually used to transform simple data (example: map, pow, etc), etc
A complex function, do more, and if it have to return a value, this is returned by references at parameters, return esp_err_t.

The function_x first do all his own verifications (if are needed), if one give an error, the function will stop and return the error code

If the function_x pass the verifications, it can continue with his normal execution.
If the esecution includes calls to other functions a, b, c ..., the functions will be called with ESP_ERROR_CHECK(function_a())
Then, all the program will be stopped if at least one of this functions give an error

### PHILOSOPHY WORKFLOW-EXECUTION (SIMPLE)

To do easier the deterministic understand of the aplications executions, the driver almost never use task functions, or interupt service routines (ISR).
But if one function do, it always have a simple deterministic logic, for example with vTaskDelay

In this case the driver has 100% easy deterministic workflow, dosent use task functions or interrupt service routines.


### WORKFLOW API (EXAMPLE)

    // Create your own config
    d_s_distance_analog sensor_config = {
        .adc_oneshot_cfg = (d_p_adc_oneshot_cfg_t) {
            .adc_unit = ADC_UNIT_1,
            .n_channels = 3,
            .adc_channels = {D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_35_ADC_CHANNEL, D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_34_ADC_CHANNEL, D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_33_ADC_CHANNEL}
        },
        .f_conversion = d_s_distance_analog_conversion_sharp_gp2y0a21
    }

    // Setup
    d_s_distance_analog_setup(&sensor_config);

    // Read
    float distances[3];
     d_s_distance_analog_read_distances(&sensor_config, distances);

    // Kill
    d_s_distance_analog_kill(&sensor_config);

    // You can repeat the workflow, optionally resetting up a change config like this, or creating other configs, you can have various config setted up at the same time
    sensor_config.adc_oneshot_cfg.n_channels = 2;
    sensor_config.adc_oneshot_cfg.adc_channels = {D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_35_ADC_CHANNEL, D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_34_ADC_CHANNEL};

