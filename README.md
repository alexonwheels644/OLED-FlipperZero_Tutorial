# OLED-FlipperZero_Tutorial

> [!WARNING]
> I do not take responsibility if you damage your board or property. This guide is for educational purposes only — proceed at your own risk.

> [!TIP]
> ❓ Need help or have questions about building/flashing the DIY Flipper? 
> Join our community Q&A and troubleshooting discussion: **[GitHub Q&A Discussion #4](https://github.com/artema0g/oled_flipper/discussions/4)**

## 📷 Hardware Showcase
<p align="center">
<img width="780" height="320" alt="4" src="https://github.com/user-attachments/assets/8a177a3e-9cd5-4d71-8573-a7fa3f7335d0" />
<img width="798" height="321" alt="3" src="https://github.com/user-attachments/assets/eeb93c98-ed6c-40b2-840a-538623564af4" />
<img width="1200" height="513" alt="6" src="https://github.com/user-attachments/assets/2f464dc2-1f3a-40db-b949-68eb6d709d87" />
<img width="1180" height="500" alt="5" src="https://github.com/user-attachments/assets/c31260ff-c8e0-4f6b-9c0a-8e2346693607" />



## 🔍 Summary
This project implements a custom target for a DIY Flipper-style board based on the **WeAct STM32WB55CGU6** board. It integrates the following components:

*   **Display**: I2C OLED display (SH1106 / SSD1306)
*   **Sensors**: INA219 / INA226 power & battery monitor (I2C) with hardware Alert (PB1)
*   **I/O Expander**: MCP23017 (handles buttons, RGB LED, and vibration motor)
*   **Storage**: microSD slot (SPI)
*   **Radio**: CC1101 sub-GHz module (SPI)
*   **NFC**: ST25R3916 Elechouse module (SPI)
*   **LF-RFID (125 kHz)**: Antenna coil driver & envelope detector (PA5 Carrier TX / PA1 Data RX)
*   **Peripherals**: Speaker/buzzer, IR transmitter/receiver, vibration motor

The long-awaited tutorial on Flipper Zero OLED FW **SSD1306** / **SH1106**.

## 🚀 Flashing Process

### 1. First Stage — OTP
> [!CAUTION]
> OTP memory can only be written **ONCE**. It cannot be erased or changed. Proceed at your own risk.
First of all, we flash the OTP:
1. Download the **STM32CubeProgrammer**.
2. Connect the board with the `BOOT` pin clamped via USB.
3. Go to the **Erasing & programming** tab.
4. <img width="1199" height="694" alt="1" src="https://github.com/user-attachments/assets/64fc4ae4-737d-40a3-aa5e-8c87be5ee0b3" />
5. Click `Browse` and select the `First_otp.bin` file and enter the address `0x1FFF7000` (we don't check any boxes) and click **Start Programming**.
6. <img width="1135" height="657" alt="2" src="https://github.com/user-attachments/assets/5c924cd3-95b6-483a-972c-dff30ef16ecd" />
7. Next, select the file `Second_otp.bin` and enter the address `0x1FFF7018`. 

**Congratulations, you have flashed the OTP addresses onto your board!**

---

### 2. Second Stage — Flashing qFlipper
1. Download **qFlipper**.
2. Connect the STM32 while holding down the `BOOT` button, click **Install from file**, select `First.dfu` and click **INSTALL**, then wait for it to finish.
> [!NOTE]
> Next, you **MUST** connect the micro SD card according to this scheme:
> * **SD CS:** `A10`
> * **SD MOSI:** `B5`
> * **SD MISO:** `A8`
> * **SD SCK:** `B3`

As soon as you connect the SD card, plug in the STM32 **without** holding down the `BOOT` button so that it starts in normal mode. As soon as it starts, click **Install from file** again and select `update_v2-1.tgz`.

After that, your board is fully flashed!

## :zap: Hardware

The best way to connect it would, of course, be to purchase my printed circuit board, which is designed to fit the original housing, but I will also fully demonstrate the correct wiring diagram.
<img width="997" height="700" alt="scheme" src="https://github.com/user-attachments/assets/ebb01911-c022-470e-83f7-42fc71f0c7f9" />

## 🔌 External GPIO Header Pinout (18-Pin)

The DIY Flipper Zero features a standard 18-pin expansion header fully compatible with Flipper Zero accessories. Below is the exact hardware routing and peripheral mapping:

| Header Pin | Flipper OS Name | Physical MCU Pin | Available Hardware Functions | Notes & Usage |
|:---:|:---:|:---:|:---|:---|
| **1** | **5V** | — | +5V Power Output (from USB VBUS) | Power external modules |
| **2** | **A7 (PA7)** | **PB5** | GPIO, PWM (TIM1), SPI1 MOSI | Shared with on-board SPI1 MOSI bus (SD / CC1101) |
| **3** | **A6 (PA6)** | **PA6** | GPIO, ADC (CH11), SPI1 MISO | Shared with on-board SPI1 MISO bus (SD / CC1101) |
| **4** | **A4 (PA4)** | **PA4** | GPIO, ADC (CH9), PWM (LPTIM2) | **Dedicated free GPIO / ADC / PWM** |
| **5** | **B3 (PB3)** | **PB3** | GPIO, SPI1 SCK | Shared with on-board SPI1 SCK clock line |
| **6** | **B2 (PB2)** | **PB2** | GPIO | **Dedicated free GPIO** |
| **7** | **C3 (PC3)** | **PA5** | GPIO, ADC (CH4), TIM2_CH1 | Routed to PA5 (used internally for LF-RFID 125 kHz TX carrier) |
| **8** | **GND** | — | Ground (GND) | Common ground |
| **9** | **3V3** | — | +3.3V Power Output | Main regulated 3.3V power rail |
| **10** | **SWCLK** | **PA14** | SWD Clock, Debug GPIO | Hardware debug / ST-Link SWD clock |
| **11** | **GND** | — | Ground (GND) | Common ground |
| **12** | **SWDIO** | **PA13** | SWD Data, Debug GPIO | Hardware debug / ST-Link SWD data |
| **13** | **TX** | **PB6** | USART1 TX, GPIO | Hardware UART Transmit (Serial CLI / external sensors) |
| **14** | **RX** | **PB7** | USART1 RX, GPIO | Hardware UART Receive (Serial CLI / external sensors) |
| **15** | **C1 (PC1)** | **PB4** | GPIO, ADC (CH2), I2C3 SDA | Shared internally with I2C3 SDA and NFC MISO |
| **16** | **C0 (PC0)** | **PA7** | GPIO, ADC (CH1), I2C3 SCL | Shared internally with I2C3 SCL |
| **17** | **1W (iButton)** | **PA3** | 1-Wire, GPIO | Dallas 1-Wire key read & emulation (DS1990) |
| **18** | **GND** | — | Ground (GND) | Common ground |

> [!TIP]
> * **Recommended General-Purpose Pins**: Pins **4 (PA4)** and **6 (PB2)** are completely unshared and ideal for relays, servos, buttons, or custom sensors.
> * **External SPI Modules**: When connecting external SPI devices to Pins 2 (MOSI), 3 (MISO), and 5 (SCK), use Pin 4 (PA4) or Pin 6 (PB2) as a dedicated Chip Select (CS) line.


## 🤝 We all need to say thank you to [artema0g](https://github.com/artema0g) for this firmware!




