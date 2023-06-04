#include <SPI.h>
int cs = 5;
int mosi = 23;
int miso = 19;
int sclk = 18;

SPIClass vspi(VSPI);

void setup() {
    Serial.begin(115200);
    vspi.begin(sclk, miso, mosi, cs);
    pinMode(cs, OUTPUT);

    normal();
}

void loop() {

}

void normal() {
    uint8_t ret;
    ret = readRegister(0x0E);

    Serial.println("");
    Serial.print("canstat: ");
    Serial.print(ret, HEX);

    return;
}

uint8_t readRegister(uint8_t reg) {
    digitalWrite(cs, 0);

    vspi.transfer(0x03);
    vspi.transfer(reg & 0xFF);
    uint8_t ret;
    ret = vspi.transfer(0xFF);

    digitalWrite(cs, 1);

    return ret;
}

void writeRegister(uint8_t reg, uint8_t data) {
    digitalWrite(cs, 0);

    vspi.transfer(0x03);
    vspi.transfer(reg & 0xFF);
    vspi.transfer(data & 0xFF);
    
    digitalWrite(cs, 1);
    return;
}

void modifyRegister(uint8_t reg, uint8_t mask, uint8_t data) {
    digitalWrite(cs, 0);

    vspi.transfer(0x05);
    vspi.transfer(reg & 0xFF);
    vspi.transfer(mask & 0xFF);
    vspi.transfer(data & 0xFF);
    
    digitalWrite(cs, 1);
    return;
}

