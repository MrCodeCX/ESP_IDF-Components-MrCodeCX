### DRIVER PERIPHERAL ADC ONESHOT by MrCodeCX (Misael Fernandez Prada)

### BRIEF
    A COMPLETE EASY MANAGER FOR MULTIPLE ADC ONESHOTS LECTURES

### COMPONENT DEPENDS
    esp_adc from the espressif oficial components

### COMPATIBLE
    Language: C / C++
    Documentation: Doxygen


### DESCRIPTION

For multiple lectures this driver is more stable than adc_continuous from espressif because, the adc_continuous works bad with 3 channels or more in esp32 classic.

This driver use global handles and global states, manages evrything related to them by itself
Then the user just have to call to the setup function with his own config of dp_adc_oneshot_cfg_t, and the driver will config and manage this

The user can have only one config per combination of adc unit and adc channels, if two configs have common channels in an adc unit, its a fatal error


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

In this case the driver has 100% easy deterministic workflow, dosent use task functions or interrupt servie routines.


### WORKFLOW API (EXAMPLE)
    
    // Optionally edit the d_p_adc_oneshot_config.h to setup the global macros, like voltage attenuated, etc

    // Create your own config
    d_p_adc_oneshot_cfg_t adc_oneshot_config = {
        .adc_unit = ADC_UNIT_1,
        .n_channels = 3,
        .adc_channels = {ADC_CHANNELS_0, ADC_CHANNELS_1, ADC_CHANNEL_2}
    }

    // SETUP
    d_p_adc_oneshot_setup(&adc_oneshot_config);

    // READ
    int lectures[3];
    d_p_adc_oneshot_read(&adc_oneshot_config, lectures);

    // KILL
    d_p_adc_oneshot_kill(&adc_oneshot_config);
