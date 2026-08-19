/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * Basic I2C bring-up test for the ADS1115 ADC.
 * Confirms that the nRF5340 DK can communicate with the
 * ADS1115 and read its configuration register.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - ADS1115 ADC
 *
 * Framework:
 * - Zephyr RTOS
 * - nRF Connect SDK
 */
#include <stdio.h>
#include <stdint.h>
#include <zephyr/drivers/i2c.h>


int main(void)
{
	
	uint8_t ads1115_address = 0x48;
	uint8_t ads1115_config_reg = 0x01;
	uint8_t ads1115_conf_bytes[2];
	const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));
	printf("ADS1115 Address: %x\n", ads1115_address);
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

if (!device_is_ready(i2c_dev))
{
	printf("device is not ready\n");
	return -1;
}

	printf("device is ready\n");
	int result = i2c_write_read(i2c_dev, ads1115_address, &ads1115_config_reg, 1, ads1115_conf_bytes, 2);
	printf("I2C result = %d\n", result);

	if (result < 0)
		{
    	printf("read write not successful, error = %d\n", result);
    	return -1;
		}
	printf("device configure MSB: 0x%x, LSB: 0x%x\n", ads1115_conf_bytes[0], ads1115_conf_bytes[1]);


	return 0;

}
