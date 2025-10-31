
#include <math.h>
#include "hcsp2c.h"
#include "NT.h"

static int threadNumber = 0;
static int midInt = 0;
static int is_term = 0;
static String* midString = NULL;
static List* midList = NULL;
static Channel channel;
static Channel channels[0];
static double h = step_size;
static double* midDouble = NULL;
static double T_set = 0.0;
static double heating_rate = 0.0;
static double T = 0.0;
static double env_temp = 0.0;
static double t = 0.0;
static double heater_state = 0.0;
static double cooling_rate = 0.0;
static double tt = 0.0;

void* TemperatureController (void* arg) {
    threadNumber = (int)(*((int*)arg));
    T = 20.0;
    T_set = 22.0;
    heater_state = 0;
    t = 0.0;
    tt = 0.0;
    env_temp = 18.0;
    heating_rate = 0.1;
    cooling_rate = 0.05;
    while (1) {
        if (T < T_set - 0.5) {
            heater_state = 1;
        } else if (T > T_set + 0.5) {
            heater_state = 0;
        }
        h = step_size;
        while (1) {
            if ((int) (localTime[threadNumber] * 1000 + 0.5) % (int) (output_step_size * 1000 + 0.5) == 0) {
                printf("%.3f: T = %.3f, heater_state = %.3f\n", localTime[threadNumber], T, heater_state);
            }
            double tt_ori = tt;
            double T_ori = T;
            double tt_dot1 = 1;
            double T_dot1 = (equalInLimit(heater_state, 1) ? heating_rate : -cooling_rate) * (T - env_temp);
            tt = tt_ori + tt_dot1 * h / 2;
            T = T_ori + T_dot1 * h / 2;
            double tt_dot2 = 1;
            double T_dot2 = (equalInLimit(heater_state, 1) ? heating_rate : -cooling_rate) * (T - env_temp);
            tt = tt_ori + tt_dot2 * h / 2;
            T = T_ori + T_dot2 * h / 2;
            double tt_dot3 = 1;
            double T_dot3 = (equalInLimit(heater_state, 1) ? heating_rate : -cooling_rate) * (T - env_temp);
            tt = tt_ori + tt_dot3 * h;
            T = T_ori + T_dot3 * h;
            double tt_dot4 = 1;
            double T_dot4 = (equalInLimit(heater_state, 1) ? heating_rate : -cooling_rate) * (T - env_temp);
            tt = tt_ori + (tt_dot1 + 2 * tt_dot2 + 2 * tt_dot3 + tt_dot4) * h / 6;
            T = T_ori + (T_dot1 + 2 * T_dot2 + 2 * T_dot3 + T_dot4) * h / 6;
            delay(threadNumber, h);
            if (!(tt < 1.0)) {
            	break;
            }
        }
        t = t + tt;
        tt = 0;
    }
    threadState[threadNumber] = STATE_STOPPED;
    updateCurrentTime(threadNumber);
    return NULL;
}