# stepper-endstop-ref-060825

**Project:** `stepper-endstop-ref`  
**Platform:** Raspberry Pi Pico W (C with pico-sdk)  
**Purpose:** Simulated reference movement using a stepper motor and endstops – ideal for measurement setups, 3D axes, or CNC systems.

---

## Features

- Controls a 28BYJ-48 stepper motor via ULN2003 driver
- Uses GPIO buttons as simulated endstop switches
- Automatically changes direction on endstop trigger (via interrupt)
- Tracks current step position and prints it via USB serial
- Clean step-sequencing using lookup table

---

## Hardware Used

| Component            | Description                        |
|----------------------|------------------------------------|
| Raspberry Pi Pico W  | Microcontroller (C SDK)            |
| 28BYJ-48 Stepper     | 5V Unipolar stepper motor          |
| ULN2003 Driver Board | For stepper control                |
| 2x Push Buttons      | Simulate upper and lower endstops  |
| USB Cable            | For code upload and serial output  |

---

## Wiring

**Stepper Motor:**  
IN1 → GPIO 13  
IN2 → GPIO 12  
IN3 → GPIO 11  
IN4 → GPIO 10  

**Endstops (Buttons):**  
Upper limit → GPIO 14  
Lower limit → GPIO 15  
