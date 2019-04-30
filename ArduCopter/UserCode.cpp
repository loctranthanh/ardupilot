#include "Copter.h"
// #include <stdio.h>
// #include <iostream>
// using namespace std;

#define LOG(x,...)  hal.console->printf(x, __VA_ARGS__)
#define FOCAL   720.5f

#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    optflow.init();
    // hal.uartB->begin(115200);
    hal.uartF->begin(115200);
    error_x = 0;
    error_y = 0;
    error_x_cm = 0;
    error_x_cm = 0;

    pid_posx.pid_set_k_params((float)g.rya_pid_kp, (float)g.rya_pid_ki, (float)g.rya_pid_kd, 0.01, 250);
    pid_posy.pid_set_k_params((float)g.rya_pid_kp, (float)g.rya_pid_ki, (float)g.rya_pid_kd, 0.01, 250);
    object = 1;
    rya_rangefinder = 0;
    // put your initialisation code here
    // this will be called once at start-up
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    // put your 100Hz code here
    // uartF: serial5, baud 115200
    //================================IPS_POSITION====================================//

    //rya_buzzer.on(true);
    ips_bytes = hal.uartF->available();
    // LOG("%d", ips_bytes);
    int data_len = 0;
    char data[BUFFER_FRAME_SIZE];
    FILE *stream;
    int detected = 0;
    while (ips_bytes > 0)
    {
        ips_bytes--;
        // Get data string here
        char c = hal.uartF->read();
        // start-of-frame
        if (c == 's')
        {
            data_len = 0;
        }
        else if (c == '\n')
        {
            data[data_len] = '\0';
            // stream = fmemopen(data, strlen(data), "r");
            // fscanf(stream, "%d %d %d", &object, &error_x, &error_y);
            // fclose(stream);
            stringstream os;
            os << data;
            os >> detected >> error_x >> error_y;
            LOG("\nReceive from server: error_x = %d, error_y = %d\n", error_x, error_y);
            if (detected == 1)
            {
                //rya_buzzer.on(true);
                // error_x_cm = error_x/720.5f*rya_rangefinder - rya_rangefinder*tanf(ahrs.roll);
                // error_y_cm = error_y/720.5f*rya_rangefinder - rya_rangefinder*tanf(-ahrs.pitch);
                //hal.console->printf("rangefinder: %d, tan(roll): %.2f, error_x: %d, error_x_cm: %.2f\n", rya_rangefinder, tanf(ahrs.roll), error_x, error_x_cm);
                // rya_time = Utility::millis();
                float delta_alpha_x = atan(error_x / FOCAL) + ahrs.roll;
                float delta_alpha_y = atan(error_y / FOCAL) + ahrs.pitch;
                // if (delta_alpha_x > 0 ) {
                    error_x_cm = tanf(delta_alpha_x) * FOCAL;
                // } else {
                    // error_x_cm = tanf(-delta_alpha_x) * FOCAL;
                // }
                // if (delta_alpha_y > 0 ) {
                    error_y_cm = tanf(delta_alpha_y) * FOCAL;
                // } else {
                    // error_y_cm = tanf(-delta_alpha_y) * FOCAL;
                // }
                // error_x_cm = (float)error_x + tanf(ahrs.roll) * 720.5;
                // error_y_cm = (float)error_y + tanf(ahrs.pitch) * 720.5;
                pid_roll = pid_posx.pid_process(error_x_cm, Utility::millis()); //Uc: control angle [degree]
                pid_pitch = pid_posy.pid_process(error_y_cm, Utility::millis());
                // pid_pitch *= 0.5;
                // pid_roll *= 0.5;
                // mode_rya.new_request = true;
                mode_rya.control(pid_roll, pid_pitch);
                LOG("detected: %d, error_x: %d, error_y: %d, (x,y): (%.2f, %.2f), (roll,pitch): (%.2f,%.2f)\n", object, error_x, error_y, error_x_cm, error_y_cm, ahrs.roll, ahrs.pitch);
                // LOG("error_x: %d, error_y: %d, (x,y): (%.2f, %.2f), (roll,pitch): (%.2f,%.2f): %s\n", object, error_x, error_y, error_x_cm, error_y_cm, pid_roll, pid_pitch, data);
                // LOG("hello %d", 1);
            }
            else
            {
                //rya_buzzer.on(false);
                pid_posx.pid_reset();
                pid_posy.pid_reset();
                // rya_control_buzzer = false;
            }
        }
        else
        { // fill buffer after catch start header
            data[data_len] = c;
            data_len++;
        }
    }
}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // LOG("g.rya_pid_kp: %.2f %.2f\n", (float)g.rya_pid_kp, (float)g.rya_pid_kd);
    pid_posx.pid_set_k_params((float)g.rya_pid_kp, (float)g.rya_pid_ki, (float)g.rya_pid_kd, 0.01, 250);
    pid_posy.pid_set_k_params((float)g.rya_pid_kp, (float)g.rya_pid_ki, (float)g.rya_pid_kd, 0.01, 250);
    // LOG("g.rya_pid_kp: %.2f %.2f\n", g.rya_pid_kp, g.rya_pid_kd);
    hal.uartF->printf("hello\n");
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
}
#endif

#ifdef USERHOOK_AUXSWITCH
void Copter::userhook_auxSwitch1(uint8_t ch_flag)
{
    // put your aux switch #1 handler here (CHx_OPT = 47)
}

void Copter::userhook_auxSwitch2(uint8_t ch_flag)
{
    // put your aux switch #2 handler here (CHx_OPT = 48)
}

void Copter::userhook_auxSwitch3(uint8_t ch_flag)
{
    // put your aux switch #3 handler here (CHx_OPT = 49)
}
#endif
