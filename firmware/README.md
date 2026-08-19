# Firmware Development

This folder contains the staged Zephyr / nRF Connect SDK bring-up work used during Phase 1 of SomniMate.

The examples are intentionally kept small so that each interface can be verified independently before moving to the next stage.

## Bring-up sequence

1. **01_ADS1115_Bringup** — basic I²C communication with the ADS1115 and configuration-register readback.
2. **02_MAX30102_Bringup** — basic I²C communication with the MAX30102 and Part ID verification.
3. **03_ADS1115_MAX30102** — confirms that the ADS1115 and MAX30102 operate together on the same I²C bus.
4. **04_ADS1115_Potentiometer** — configures ADS1115 AIN3 for single-ended conversion and verifies analogue voltage measurement using a potentiometer.
5. **05_BH1750_Bringup** — reads ambient-light level from a GY-302 / BH1750 sensor in continuous high-resolution mode.
6. **06_ADS1115_MAX30102_BH1750** — confirms that the ADS1115, MAX30102 and BH1750 can operate together on the same I²C bus.

Current bring-up platform: **Nordic nRF5340 DK** with **Zephyr / nRF Connect SDK**.

The nRF5340 DK is being used as the initial firmware-learning and sensor-integration platform before moving the prototype to the planned nRF54L20A hardware.
