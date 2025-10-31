
#include <math.h>
#include "NT.h"
#include "hcsp2c.h"

int main() {
    const int threadNumber = 3;
    const int channelNumber = 2;
    void* (*threadFuns[threadNumber])(void*);
	threadFuns[0] = &TemperatureController;
	threadFuns[1] = &Environment;
	threadFuns[2] = &Logger;

    init(threadNumber, channelNumber);
    maxTime = 40.000000;
	channelNames[0] = "inputs_lb_TemperatureController_rb__lb_T_rb_";
	channelNames[1] = "inputs_lb_TemperatureController_rb__lb_heater_state_rb_";

    run(threadNumber, channelNumber, threadFuns);

    destroy(threadNumber, channelNumber);
    return 0;
}
