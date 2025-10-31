
#ifndef NT_h
#define NT_h

#define step_size 0.0001
#define output_step_size 0.01
#define max_loop_cnt 1000000000
#define inputs_lb_TemperatureController_rb__lb_T_rb_ 0
#define inputs_lb_TemperatureController_rb__lb_heater_state_rb_ 1
void* TemperatureController (void* arg);
void* Environment (void* arg);
void* Logger (void* arg);
#endif