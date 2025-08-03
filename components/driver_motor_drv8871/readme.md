DRIVER MOTOR DRV8871

A SIMPLE DRIVER TO MANAGE TWO DRIVERS DRV8871 TO CONTROL MOTORS 
IS IDEAL FOR COMPETITIVE ROBOTS WITH 2 MOTORS (sumo, line-follower, etc)

This driver depends of driver from the espressif oficial components

To config edit the d_m_drv8871_config.h and d_m_drv8871_config.c files
At least is needed to config the pins in d_m_drv8871_config.h

WORKFLOW API

// SETUP
d_m_drv8871_setup();

// WRITE
d_m_drv8871_write(write_a, write_b);