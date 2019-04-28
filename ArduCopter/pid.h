#ifndef PID_H
#define PID_H

#include <stdint.h>
#define DPART_N_AVG 3
class PID
{
public:
    typedef struct
    {
        float Kp;
        float Ki;
        float Kd;
        float ppart;
        float ipart;
        float dpart;
        float dpart_tmp[DPART_N_AVG];
        float dpart_alpha;
        float u;
        float u_;
        float e;
        float e_;
        float e__;
        float Ts;
        bool flag_first_time;
        float PID_Saturation;
        uint32_t time;
    } PID_PARAMETERS;

    PID();
    ~PID();

    float pid_process(float error,uint32_t time);
    void pid_reset();
    void pid_set_k_params(float Kp,float Ki, float Kd, float Ts, float PID_Saturation);
    PID_PARAMETERS pid_param;
};

#endif // PID_H