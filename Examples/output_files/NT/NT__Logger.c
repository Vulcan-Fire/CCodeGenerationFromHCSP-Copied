
#include <math.h>
#include "hcsp2c.h"
#include "NT.h"

static int threadNumber = 0;
static int midInt = 0;
static int is_term = 0;
static String* midString = NULL;
static List* midList = NULL;
static Channel channel;
static Channel channels[2];
static double h = step_size;
static double* midDouble = NULL;
static double data = 0.0;
static double heater_state = 0.0;

void* Logger (void* arg) {
    threadNumber = (int)(*((int*)arg));
    while (1) {
        channel.channelNo = inputs_lb_TemperatureController_rb__lb_T_rb_;
        channel.type = 0;
        channel.pos = &data;
        input(threadNumber, channel);
        channel.channelNo = inputs_lb_TemperatureController_rb__lb_heater_state_rb_;
        channel.type = 0;
        channel.pos = &heater_state;
        input(threadNumber, channel);
        ;
    }
    threadState[threadNumber] = STATE_STOPPED;
    updateCurrentTime(threadNumber);
    return NULL;
}