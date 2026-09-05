# OLED-FlipperZero_Tutorial

Hardware wiring, pinouts and how to flash STM32 to OLED FW.

The long-awaited tutorial on Flipper Zero OLED FW **SSD1306** / **SH1106**.

## 🚀 Flashing Process

### 1. First Stage — OTP
First of all, we flash the OTP:
1. Download the **STM32CubeProgrammer**.
2. Connect the board with the `BOOT` pin clamped via USB.
3. Go to the **Erasing & programming** tab.
4. Click `Browse` and select the `First_otp.bin` file and enter the address `0x1FFF7000` (we don't check any boxes) and click **Start Programming**.
5. Next, select the file `Second_otp.bin` and enter the address `0x1FFF7018`. 

**Congratulations, you have flashed the OTP addresses onto your board!**

---

### 2. Second Stage — Flashing qFlipper
1. Download **qFlipper**.
2. Connect the STM32 while holding down the `BOOT` button, click **Install from file**, select `FW.dfu` and click **INSTALL**, then wait for it to finish.
> [!WARNING]
> Next, you **MUST** connect the micro SD card according to this scheme:
   * **SD CS:** `A10`
   * **SD MOSI:** `B5`
   * **SD MISO:** `A8`
   * **SD SCK:** `B3`

As soon as you connect the SD card, plug in the STM32 **without** holding down the `BOOT` button so that it starts in normal mode. As soon as it starts, click **Install from file** again and select `update_v1-1.tgz`.

After that, your board is fully flashed!
