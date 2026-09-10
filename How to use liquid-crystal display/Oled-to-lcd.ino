#include <Wire.h>
#include <SPI.h>

#define I2C_SDA_PIN 8
#define I2C_SCL_PIN 9

#define SPI_MOSI_PIN 6
#define SPI_SCK_PIN  4
#define SPI_CS_PIN   3
#define SPI_DC_PIN   1
#define SPI_RES_PIN  0

#define OLED_I2C_ADDRESS 0x3C

uint8_t oled_buffer[8][128];
uint8_t current_page = 0;
uint8_t current_column = 0;
volatile bool screen_updated = false;

void spiSendCommand(uint8_t cmd) {
    digitalWrite(SPI_DC_PIN, LOW);
    digitalWrite(SPI_CS_PIN, LOW);
    SPI.transfer(cmd);
    digitalWrite(SPI_CS_PIN, HIGH);
}

void initST7567() {
    pinMode(SPI_CS_PIN, OUTPUT);
    pinMode(SPI_DC_PIN, OUTPUT);
    pinMode(SPI_RES_PIN, OUTPUT);
    
    digitalWrite(SPI_RES_PIN, LOW);
    delay(50);
    digitalWrite(SPI_RES_PIN, HIGH);
    delay(50);

    spiSendCommand(0xAE); 
    spiSendCommand(0xA2); 
    spiSendCommand(0xA0); 
    spiSendCommand(0xC8); 
    spiSendCommand(0x2F); 
    spiSendCommand(0x25);
    spiSendCommand(0x81); 
    spiSendCommand(0x1C); 
    spiSendCommand(0x40); 
    spiSendCommand(0xA6); 
    spiSendCommand(0xAF);
}
void flushToLCD() {
    for (uint8_t page = 0; page < 8; page++) {
        spiSendCommand(0xB0 | page);      
        spiSendCommand(0x00);              
        spiSendCommand(0x10);              
        uint8_t shifted_line[128];
        for (int i = 0; i < 127; i++) {
            shifted_line[i] = oled_buffer[page][i + 2]; 
        }
        shifted_line[127] = 0;

        digitalWrite(SPI_DC_PIN, HIGH);
        digitalWrite(SPI_CS_PIN, LOW);
        SPI.writeBytes(shifted_line, 128);
        digitalWrite(SPI_CS_PIN, HIGH);
    }
}
void onReceive(int len) {
    bool is_data = false;
    
    while (Wire.available()) {
        uint8_t b = Wire.read();
        len--;
        if (!is_data) {
            if (b == 0x40) {
                is_data = true;
            } else if ((b & 0xF0) == 0xB0) {
                current_page = b & 0x07; 
            } else if ((b & 0xF0) == 0x00) {
                current_column = (current_column & 0xF0) | (b & 0x0F); 
            } else if ((b & 0xF0) == 0x10) {
                current_column = (current_column & 0x0F) | ((b & 0x0F) << 4);
            }
        } else {
            if (current_page < 8 && current_column < 128) {
                oled_buffer[current_page][current_column] = b;
                current_column++;
                if (current_column >= 128) {
                    current_column = 0;
                    current_page = (current_page + 1) % 8;
                }
            }
        }
    }
    screen_updated = true;
}

void setup() {
    Serial.begin(115200);
    delay(500);

    memset(oled_buffer, 0, sizeof(oled_buffer));

    SPI.begin(SPI_SCK_PIN, -1, SPI_MOSI_PIN, SPI_CS_PIN);
    SPI.setFrequency(20000000); 
    
    initST7567();

    Wire.begin(OLED_I2C_ADDRESS, I2C_SDA_PIN, I2C_SCL_PIN, 400000);
    Wire.onReceive(onReceive);
}

void loop() {
    if (screen_updated) {
        screen_updated = false;
        flushToLCD();
    }
}