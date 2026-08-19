/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * Basic I2C bring-up test for the MAX30102 sensor.
 * Confirms that the nRF5340 DK can communicate with the
 * MAX30102 and read its Part ID register.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - MAX30102 optical sensor
 *
 * Framework:
 * - Zephyr RTOS
 * - nRF Connect SDK
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <zephyr/drivers/i2c.h>

int main(void)
{

    uint8_t ads1115_address = 0x48;
    uint8_t ads1115_config_reg = 0x01;
    uint8_t ads1115_conf_bytes[2];

    uint8_t max30102_address = 0x57;
    uint8_t max30102_part_id_reg = 0xFF;
    uint8_t max30102_part_id;

    const struct device *i2c_dev =
    DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));

    printf("MAX30102 Address: 0x%x\n", max30102_address);
    printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

    if (!device_is_ready(i2c_dev))
    {
        printf("device is not ready\n");
        return -1;
    }

    printf("device is ready\n");

    int result = i2c_write_read(i2c_dev,
                                max30102_address,
                                &max30102_part_id_reg,
                                1,
                                &max30102_part_id,
                                1);

    printf("I2C result = %d\n", result);

    if (result < 0)
    {
        printf("MAX30102 read not successful, error = %d\n", result);
        return -1;
    }

    printf("MAX30102 Part ID: 0x%x\n", max30102_part_id);

    if (max30102_part_id == 0x15)
    {
        printf("MAX30102 detected\n");
    }
    else
    {
        printf("Unexpected Part ID\n");
    }

    return 0;
}
