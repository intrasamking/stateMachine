#ifndef RTW_HEADER_validate_h_
#define RTW_HEADER_validate_h_

/* Macros for accessing real-time model data structure */
//#ifndef rtmGetErrorStatus
//#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
//#endif
//
//#ifndef rtmSetErrorStatus
//#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
//#endif

/* Forward declaration for rtModel */
//typedef struct tag_RTM RT_MODEL;

/**** State Definitions ****/
typedef enum { S_NOTACTIVE = 0, S_BUFFERING = 1, S_ACTIVE = 2 } states;

typedef enum { S_NOTLOGGING = 0, S_LOGGING = 1 } loggingStates;

/**** Event Definitions ****/
typedef enum { E_doNothing = 0, E_goActive = 1, E_goPassive = 2, E_goBuffer = 3 } stateEvents;

typedef enum { E_staySame = 0, E_goLogging = 1, E_goNotLogging = 2 } loggingEvents;

typedef enum { temperature, pressure } sensor_types;

typedef enum { primary, secondary, tertiary } sensor_names;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
	double previous_signal;
	int previous_validity;
	int temporalCounter;
	int logSignals;
} DW;

/* External inputs */
typedef struct {
	sensor_types sensor_type;
	sensor_names sensor_name;
	states currentState;
	double sensorValue;
} analogSensorInput;

typedef struct {
	sensor_names sensor_name;
	states currentState;
	double latitude;
	double longitude;
	double altitude;
	int quality;
	int satellitesInView;
} gpsSensorInput;

typedef struct {
	sensor_names sensor_name;
	states currentState;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
} imuSensorInput;

/* External outputs */
typedef struct {
	sensor_types sensor_type;
	sensor_names sensor_name;
	double sensorValue;
	int failure;
} analogSensorOutput;

typedef struct {
	sensor_names sensor_name;
	states currentState;
	double latitude;
	double longitude;
	double altitude;
	int quality;
	int satellitesInView;
	int failure;
} gpsSensorOutput;

typedef struct {
	sensor_names sensor_name;
	states currentState;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
} imuSensorOutput;

extern DW* bpStorage, brakePipeStorage;
extern analogSensorInput* bpPressureIn, brakePipePressureIn;
extern analogSensorOutput* bpPressureOut, brakePipePressureOut;
extern DW* resStorage, reservoirStorage;
extern analogSensorInput* resPressureIn, reservoirPressureIn;
extern analogSensorOutput* resPressureOut, reservoirPressureOut;

extern void validate_pressure_state(DW*, analogSensorInput*, analogSensorOutput*);
extern double get_pressure_value();
extern int validate_pressure_reading(analogSensorInput*);
extern int validate_gps_reading(gpsSensorInput*);
extern int validate_imu_reading(imuSensorInput*);

//struct tag_RTM {
//	const char_T* volatile errorStatus;
//};
//
//extern void validate_step(void);s
//extern RT_MODEL* const rtM;

#endif