# OLED-FlipperZero_Tutorial
Hardware wiring, pinouts and how to flash stm32 to oled fw

The long-awaited tutorial on Flipper zero OLED FW SSD1306/SH1106
1. You just bought your stm32, first of all we flash the OTP, download the stm32 cube programmer, connect the stm with the BOOT clamped via usb and go to the Earsing & programming tab, click Browse and select the First_otp.bin file and enter the address 0x1FFF7000 we don't check any boxes and click Start Programming. Next, select the file Second_otp.bin and enter the address 0x1FFF7010. Congratulations, you have flashed the OTP addresses onto your board!

2. Stage 2 — flashing.
Download qFlipper, connect the STM32 while holding down the BOOT button, click “Install from file,” select First.dfu, and click “INSTALL,” then wait for it to finish. 
Next, you MUST connect the micro SD card according to this scheme:
SD STM
MOSI B5
MISO A6
SCK B3
CS A10

As soon as you connect the SD card, plug in the STM32 without holding down the BOOT button so that it starts in normal mode. As soon as it starts, click Install from file again and select update_v2-1.tgz. After that, your board is fully flashed!

