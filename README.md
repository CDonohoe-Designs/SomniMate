# SomniMate

**Dual-channel sleep respiratory monitoring R&D platform**

SomniMate is a personal engineering R&D project I am developing to investigate **thoraco-abdominal respiratory effort**, particularly the relationship between chest and abdominal movement during sleep.

The project is built around two synchronized respiratory-effort channels with supporting physiological and contextual sensing. My aim is to develop the sensing electronics, embedded firmware and signal-processing chain, then use the platform to explore respiratory coordination, paradoxical breathing and breath-by-breath changes in respiratory effort.

> **Project status:** active research and development. SomniMate is not a diagnostic medical device and is not intended for clinical use.

## System concept

The planned system has two wearable modules:

- **SomniMate** — main controller with the first respiratory-effort front end
- **SomniLink** — second respiratory-effort module for the other strap

Supporting signals under investigation include:

- PPG / heart-rate / experimental SpO₂ using the MAX30102
- body position and movement using an IMU
- snoring / acoustic features using a microphone
- BLE data transfer and logging

## High-level architecture

```text
Thoracic effort strap ──> SomniMate AFE ──┐
                                          │
SomniLink <── Abdominal effort strap      ├──> SomniMate controller
                                          │        │
PPG ──────────────────────────────────────┤        ├──> BLE / logging
IMU ──────────────────────────────────────┤        │
Microphone ───────────────────────────────┘        └──> signal processing
```

The exact SomniLink-to-SomniMate interconnect is still part of the development work. The important architectural requirement is synchronized thoracic and abdominal effort measurement.

## Engineering areas

This project brings together:

- analog front-end design
- inductive respiratory-effort sensing
- low-power embedded hardware
- Nordic nRF / Zephyr firmware
- I²C and sensor integration
- BLE data transfer
- mixed-signal PCB design
- signal processing and phase analysis
- bench and overnight test methods
- wearable mechanical integration

## Development approach

I am building the project in stages:

1. establish the sensor and firmware development environment
2. characterise respiratory-effort sensing on the bench
3. develop a single-channel front end
4. expand to synchronized thoracic + abdominal channels
5. integrate PPG, motion and acoustic context
6. collect repeatable test data
7. develop respiratory coordination / paradox analysis
8. iterate toward a compact wearable implementation

## Repository scope

This public repository is the portfolio-facing record of the project. It will contain selected architecture notes, hardware milestones, diagrams, firmware demonstrations, test results and signal-processing outputs.

Detailed working files, raw data and development material are maintained separately.

## Current status

- [x] Project architecture defined
- [x] Nordic / Zephyr development environment established
- [x] MAX30102 and external ADC I²C bring-up completed during early prototyping
- [x] Dual thorax / abdomen measurement strategy selected
- [ ] Single-channel respiratory AFE prototype
- [ ] SomniMate hardware prototype
- [ ] SomniLink hardware prototype
- [ ] Synchronized dual-channel bench testing
- [ ] Overnight data collection
- [ ] Thoraco-abdominal phase / paradox analysis

## Why I am building it

I wanted a project that combines the parts of electronics engineering I enjoy most: **analog sensing, embedded hardware, firmware, PCB design and real-world measurement**. Sleep respiratory monitoring provides a useful system-level challenge because signal quality depends on electronics, mechanics, firmware and signal processing working together.

---

**SomniMate is an independent R&D project and is not a diagnostic or therapeutic medical device.**