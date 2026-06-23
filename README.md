# PET Bottle to 3D Printing Filament Recycler – Arduino Firmware

This repository contains the C++ firmware for an engineering thesis project completed at the University of the National Education Commission, Krakow. 

The software is specifically designed for the **Arduino Uno R4 Minima** microcontroller to control and automate a machine that recycles post-consumer PET bottles into 3D printing filament.

⚠️ **Project Status: Active Development** This repository currently holds the source code for the working prototype built for my Engineering Degree. This project is under continuous development and will be significantly expanded and optimized as part of my upcoming master's thesis. For this reason, the repository contains **only the C++ source file**.


## 🚀 Implemented Features (C++)
- **Non-Blocking Multitasking:** Designed using a non-blocking architecture (`millis()` and `micros()` timers) allowing simultaneous, high-frequency stepper motor driving and temperature regulation without system freezes.
- **Signal Filtering & Mathematical Modeling:** Implemented a moving-average filter (`avarageTemp`) to stabilize raw sensor data, and applied the *Steinhart-Hart equation* for high-accuracy thermistor resistance-to-temperature translation.
- **Proportional-like Thermal Regulation:** Uses a custom mathematical mapping function (via PWM) to dynamically reduce heating power as the system approaches the target temperature, minimizing thermal overshoot.
- **I2C User Interface:** Real-time hardware telemetry transmission via I2C protocol to a 20x4 LCD screen.

## 🛠️ Tech Stack & Hardware Target
- **Language & Framework:** C++ / Arduino Framework
- **Key APIs:** Wire.h, LiquidCrystal_I2C
- **Microcontroller:** Arduino Uno R4 Minima

## 📄 Thesis Context
- **Original Title:** Projekt i oprogramowanie urządzenia recyklingującego butelki PET na filament do druku 3D
- **Institution:** University of the National Education Commission, Krakow
