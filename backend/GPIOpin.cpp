#include "GPIOpin.h"

void GPIOpin::set(FILE* fd, size_t value) {
    char buffer[4];
    memset(buffer, 0, 4);
    sprintf(buffer, "%d", value);
    fseek(fd, 0, SEEK_SET);
    fwrite(buffer, 1, 4, fd);
    fflush(fd);
}

size_t GPIOpin::get(FILE* fd) {
    size_t value;
    fseek(fd, 0, SEEK_SET);
    if(fscanf(fd, "%d", &value) == 0) return -1;
    return value;
}

GPIOpin::GPIOpin() :mode(0), pin(0) {

}

GPIOpin::~GPIOpin() {
    if(mode) fclose(mode);
    if(pin) fclose(pin);
}

bool GPIOpin::isValid() const {
    return mode && pin;
}

void GPIOpin::setIndex(size_t _index) {
    index = _index;
    char buffer[256];
    sprintf(buffer, "/sys/devices/virtual/misc/gpio/mode/gpio%d", index);
    mode = fopen(buffer, "r+");
    sprintf(buffer, "/sys/devices/virtual/misc/gpio/pin/gpio%d", index);
    pin = fopen(buffer, "r+");
}

size_t GPIOpin::getIndex() const {
    return index;
}

void GPIOpin::setMode(size_t value) {
    set(mode, value);
}

size_t GPIOpin::getMode() {
    return get(mode);
}

void GPIOpin::setValue(size_t value) {
    set(pin, value);
}

size_t GPIOpin::getValue() {
    return get(pin);
}
