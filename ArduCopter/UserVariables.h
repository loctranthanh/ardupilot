// user defined variables

// example variables used in Wii camera testing - replace with your own
// variables


#ifdef USERHOOK_VARIABLES

#define BUFFER_FRAME_SIZE   512

uint16_t ips_bytes;
uint16_t ips_flag;
uint16_t ips_data[4];
uint16_t c_buff;
uint16_t c_state;
char ips_char[BUFFER_FRAME_SIZE];
uint32_t ips_delay_ms; 
float air_temperature;
Vector3f ips_gyro, ips_accel;
Vector2f opt_flowRate;
Vector2f opt_bodyRate;
uint32_t opt_integration_timespan;
// char data[BUFFER_FRAME_SIZE];
uint16_t s16_US_HEIGHT;
bool newData_flag = false;
char requestToServer[BUFFER_FRAME_SIZE];
int error_x, error_y;
bool flag_tr_control_pass = false;
bool flag_tr_timer_up = false;
int count_tr = 0;
uint32_t rya_time;

int rya_rangefinder;

bool flag_tr_pitch = false;
int tr_dir = 0;

float error_x_cm, error_y_cm;

PID pid_posx;
PID pid_posy;

float pid_roll;
float pid_pitch;

int object;

bool rya_control_buzzer, toggle;

Buzzer rya_buzzer;


// #if WII_CAMERA == 1
// WiiCamera           ircam;
// int                 WiiRange=0;
// int                 WiiRotation=0;
// int                 WiiDisplacementX=0;
// int                 WiiDisplacementY=0;
// #endif  // WII_CAMERA

#endif  // USERHOOK_VARIABLES


