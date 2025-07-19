#include "I2C.h"
#include <bcm2835.h>

// GPIO 0 and 1 are with TX, RX

I2C::I2C() {
    if (!bcm2835_init()) {
        throw std::runtime_error("Failed to initialize bcm2835");
    }
}

I2C::~I2C() {
    bcm2835_close();
}

struct I2CDevice {
    std::string name;
	std::vector<int> pins; // SCL, SDA
};

std::vector<I2CDevice> I2C::devices = {
    {"Gas Sensor", {21, 20}},
    {"Gyroskop", {27, 26}},
    {"Barometer", {6, 7}},
    {"Kompass", {8, 9}},
    {"Buzzer", {10, 11}},
    {"Ultraschall", {12, 13}},
    {"Kaemra", {14, 15}},
    {"VOC", {16, 17}},
    {"Temp", {18, 19}},
    {"Druck", {20, 21}},
    {"Erschütterugen", {22, 23}},
    {"Akku", {24, 25}},
    {"GPS", {26, 27}},
    {"Antenne", {28, 29}},
    {"IR", {30, 31}},
    {"Fechtigkeitsensor", {32, 33}}
};

void I2C::begin() {
    if (!bcm2835_i2c_begin()) {
        throw std::runtime_error("Failed to begin I2C");
    }


}