#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

class GPIOpin {
    std::fstream mode, pin;
    bool set(std::fstream& fd, size_t value) const;
    bool get(std::fstream& fd, size_t& value) const;

    public:
    size_t index;
    GPIOpin(size_t index);
    bool isValid() const;
    bool setMode(size_t value) const;
    bool setValue(size_t value) const;
    bool getMode(size_t& value) const;
    bool getValue(size_t& value) const;
};
