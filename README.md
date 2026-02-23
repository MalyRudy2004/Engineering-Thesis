# Development of a fiber optic system for spatial localization of a person in a room

### Engineering Thesis
**Author:** Piotr Łuczak  
**Student ID:** 246965  
 

---

## Project Overview
This repository contains all the necessary files to understand, recreate, and further develop the project presented in the engineering thesis. The system utilizes fiber-optic microbending sensors to detect and localize human presence in a room.

## Repository Contents

The repository is organized into the following main sections:

- **Python Application** PC software for real-time visualization of the object's position (GUI).

- **STM32 Firmware** Full `STM32CubeIDE` project for the **STM32F303K8** microcontroller. Contains source code, drivers, and logic implementation.

- **KiCad Design Files** Complete hardware design including:
  - Schematics (`.kicad_sch`)
  - PCB Layout (`.kicad_pcb`)
  - **Component Libraries:** Project-specific schematic symbols, footprints, and 3D models of the components used.

- **Datasheets** Technical documentation for key components used in the project (Laser Drivers, MOSFETs, Photodiodes, etc.).

---

## Important Hardware Disclaimer

**Please read before reproducing the PCB:**

There is a discrepancy in the STM32 pin connections between the KiCad schematics and the STM32CubeIDE project configuration. 

- The connection on the physical PCB was **corrected manually after production** (hardware patch).
- **The correct pinout** is defined and explained in the STM32 Project source code.
- Please refer specifically to the **GPIO library header file** for the verified and working pin configuration.

---
*Politechnika Łódzka (Lodz University of Technology) - 2026*
