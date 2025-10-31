
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
static double t = 0.0;
static double env_temp = 0.0;

void* Environment (void* arg) {
    threadNumber = (int)(*((int*)arg));
    env_temp = 18.0;
    t = 0.0;
    while (1) {
        h = step_size;
        while (1) {
            if ((int) (localTime[threadNumber] * 1000 + 0.5) % (int) (output_step_size * 1000 + 0.5) == 0) {
                printf("%.3f: env_temp = %.3f\n", localTime[threadNumber], env_temp);
            }
            double t_ori = t;
            double env_temp_ori = env_temp;
            double t_dot1 = 1;
            double env_temp_dot1 = 0.01 * sin(3.1415 * t / 60);
            t = t_ori + t_dot1 * h / 2;
            env_temp = env_temp_ori + env_temp_dot1 * h / 2;
            double t_dot2 = 1;
            double env_temp_dot2 = 0.01 * sin(3.1415 * t / 60);
            t = t_ori + t_dot2 * h / 2;
            env_temp = env_temp_ori + env_temp_dot2 * h / 2;
            double t_dot3 = 1;
            double env_temp_dot3 = 0.01 * sin(3.1415 * t / 60);
            t = t_ori + t_dot3 * h;
            env_temp = env_temp_ori + env_temp_dot3 * h;
            double t_dot4 = 1;
            double env_temp_dot4 = 0.01 * sin(3.1415 * t / 60);
            t = t_ori + (t_dot1 + 2 * t_dot2 + 2 * t_dot3 + t_dot4) * h / 6;
            env_temp = env_temp_ori + (env_temp_dot1 + 2 * env_temp_dot2 + 2 * env_temp_dot3 + env_temp_dot4) * h / 6;
            delay(threadNumber, h);
            if (!(t < 1000.0)) {
            	break;
            }
        }
    }
    threadState[threadNumber] = STATE_STOPPED;
    updateCurrentTime(threadNumber);
    return NULL;
}