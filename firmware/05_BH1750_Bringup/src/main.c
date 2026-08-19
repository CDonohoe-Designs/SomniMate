/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * Basic I2C bring-up test for the BH1750 ambient-light sensor.
 * Configures continuous high-resolution measurement mode and
 * prints light level in lux.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - GY-302 / BH1750 ambient-light sensor
 *
 * Framework:
 * - Zephyr RTOS
 * - nRF Connect SDK
 */
#include <stdio.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

int main(void)
{
    uint8_t bh1750_address = 0x23;
    uint8_t bh1750_mode = 0x10;

    uint8_t bh1750_data[2];
    uint16_t raw_light;
    uint32_t lux_x10;

    const struct device *i2c_dev =
        DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));

    printf("BH1750 Address: 0x%x\n", bh1750_address);
    printf("Board: %s\n", CONFIG_BOARD_TARGET);

    if (!device_is_ready(i2c_dev))
    {
        printf("I2C device is not ready\n");
        return -1;
    }

    printf("I2C device is ready\n");

    /* Continuous High Resolution Mode */
    i2c_write(
        i2c_dev,
        &bh1750_mode,
        1,
        bh1750_address);

    /* Allow first measurement to complete */
    k_msleep(180);

    while (1)
    {
        i2c_read(
            i2c_dev,
            bh1750_data,
            2,
            bh1750_address);

        raw_light =
            (bh1750_data[0] << 8) |
             bh1750_data[1];

        /* BH1750 conversion: lux = raw / 1.2 */
        lux_x10 = ((uint32_t)raw_light * 10) / 12;

        printf("Light = %u.%u lux\n",
               lux_x10 / 10,
               lux_x10 % 10);

        k_msleep(500);
    }

    return 0;
}
