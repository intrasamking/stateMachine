
#ifndef INIT_SENSORS_h
#define INIT_SENSORS_h

/**** State Definitions ****/
typedef enum { S_NOTACTIVE = 0, S_BUFFERING = 1, S_ACTIVE = 2 } states;

typedef enum { S_NOTLOGGING = 0, S_LOGGING = 1 } loggingStates;

/**** Event Definitions ****/
typedef enum { E_doNothing = 0, E_goActive = 1, E_goPassive = 2, E_goBuffer = 3 } stateEvents;

typedef enum { E_staySame = 0, E_goLogging = 1, E_goNotLogging = 2 } loggingEvents;

typedef enum { temperature, pressure } sensor_types;

typedef enum { primary, secondary, tertiary } sensor_names;

typedef struct {
	double previous_signal;
	int previous_validity;
	int temporalCounter;
	int logSignals;
} DW;

typedef struct {
	double previousLat;
	double previousLong;
	double previousAlt;
	int previous_validity;
	int temporalCounter;
	int logSignals;
} gpsStorage;

typedef struct {
	double previous_ax;
	double previous_ay;
	double previous_az;
	double previous_gx;
	double previous_gy;
	double previous_gz;
	int previous_validity;
	int temporalCounter;
	int logSignals;
} imuStorage;

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
	int validity;
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
	int validity;
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
	double latitude;
	double longitude;
	double altitude;
	int quality;
	int satellitesInView;
	int failure;
} gpsSensorOutput;

typedef struct {
	sensor_names sensor_name;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
	int failure;

} imuSensorOutput;

typedef struct {
	analogSensorInput *bpPresIn;
	analogSensorOutput *bpPresOut;
	DW *bpStore;
	analogSensorInput *resPresIn;
	analogSensorOutput *resPresOut;
	DW *resStore;
	gpsSensorInput *gpsIn1;
	gpsSensorOutput *gpsOut1;
	gpsStorage *gpsStore;
} sensorPointers;


/* Sensor Variables for System */

extern DW *bpStorage, brakePipeStorage;
extern analogSensorInput *bpPressureIn, brakePipePressureIn;
extern analogSensorOutput *bpPressureOut, brakePipePressureOut;

extern DW *resStorage, reservoirStorage;
extern analogSensorInput *resPressureIn, reservoirPressureIn;
extern analogSensorOutput *resPressureOut, reservoirPressureOut;

extern gpsStorage *gpsStore1, gpsStorage1;
extern gpsSensorInput *gpsIn1, gpsSensorIn1;
extern gpsSensorOutput *gpsOut1, gpsSensorOut1;

extern sensorPointers sensorPtrs;

/* Initialize Sensor Methods */

extern sensorPointers initialize_sensors();
extern int initialize_pressure_sensor(DW*, analogSensorInput*, analogSensorOutput*);
extern int initialize_temperature_sensor(DW*, analogSensorInput*, analogSensorOutput*);
extern int initialize_gps_sensor(gpsStorage*, gpsSensorInput*, gpsSensorOutput*);
extern int initialize_accelerometer_sensor(imuStorage*, imuSensorInput*, imuSensorOutput*);


#endif