#include "L6470.h"
#define MOTOR_STEPS 200

int main(int argc, char** argv) {
    SPI bus(3);
    printf("Max speed: %d Hz\n", bus.getMaxFrequency());

    L6470* motors[1];
    for(size_t i = 0; i < sizeof(motors)/sizeof(void*); ++i)
        motors[i] = new L6470(&bus, i);

    motors[0]->resetHome();
    motors[0]->move(MOTOR_STEPS, true);
    uint32_t value;
    motors[0]->getParam(ABS_POS, value);
    printf("ABS_POS: %d\n", value);
    motors[0]->getParam(STATUS, value);
    printf("STATUS: %d\n", value);

    /*FILE* pipe = popen("frontend/bin/server", "w");
    if(!pipe) {
        printf("Could not open child process.\n");
        return 1;
    }
    char buffer[512];
    while(fread(buffer, 1, sizeof(buffer), pipe)) {
        printf("%s\n", buffer);
    }
    pclose(pipe);*/

    return 0;
}
