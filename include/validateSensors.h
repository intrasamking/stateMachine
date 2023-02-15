#ifndef RTW_HEADER_validate_h_
#define RTW_HEADER_validate_h_

/**** State Definitions ****/
typedef enum {	S_NOTCONNECTED = 0, 
				S_NOTACTIVE = 1, 
				S_BUFFERING = 2, 
				S_ACTIVE = 3 } states;

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

//typedef struct {
	//analogSensorInput *bpPresIn;
	//analogSensorOutput *bpPresOut;
	//DW *bpStore;
	//analogSensorInput *resPresIn;
	//analogSensorOutput *resPresOut;
	//DW *resStore;
	//gpsSensorInput *gpsIn1;
	//gpsSensorOutput *gpsOut1;
	//gpsStorage *gpsStore;
//	analogIn inputSensor;
//	analogOut outputSensor;
//	analogStorage storage;
//
//} sensorPointers;

/* Sensor Variables for System */

//extern DW *bpStorage, brakePipeStorage;
//extern analogSensorInput *bpPressureIn, brakePipePressureIn;
//extern analogSensorOutput *bpPressureOut, brakePipePressureOut;
//
//extern DW *resStorage, reservoirStorage;
//extern analogSensorInput *resPressureIn, reservoirPressureIn;
//extern analogSensorOutput *resPressureOut, reservoirPressureOut;

//extern gpsStorage *gpsStore1, gpsStorage1;
//extern gpsSensorInput *gpsIn1, gpsSensorIn1;
//extern gpsSensorOutput *gpsOut1, gpsSensorOut1;
//
//extern sensorPointers sensorPtrs;

//extern states validate_pressure_state(analogStorage, analogIn, analogOut);
//extern states validate_gps_state(gpsStorage *, gpsSensorInput *, gpsSensorOutput *);
//extern states validate_imu_state(imuStorage *, imuSensorInput *, imuSensorOutput *);

extern void set_analog_value(analogIn inst, double pressureVal);
//extern void set_gps_value(double latVal, double longVal, double altVal, int qual, int sats, gpsSensorInput *);
//extern void set_accelerometer_value(double ax, double ay, double az, double gx, double gy, double gz, imuSensorInput *);

extern double get_analog_value( analogIn inst);
//extern int get_gps_value(gpsSensorInput *);
//extern int get_imu_value(imuSensorInput *);

extern int validate_pressure_reading(analogIn inst);
//extern int validate_gps_reading(gpsSensorInput *);
//extern int validate_imu_reading(imuSensorInput *);

//extern sensorPointers initialize_sensors(analogIn, analogOut, analogStorage);
extern void initialize_pressure_sensorIn(analogIn inst, enum sensor_name sName);
//extern analogOut intialize_pressure_sensorOut(analogIn, analogOut);
//extern analogStorage intialize_pressure_sensorStorage(analogIn, analogStorage);

//extern int initialize_temperature_sensor(DW *, analogSensorInput *, analogSensorOutput *);
//extern int initialize_gps_sensor(gpsStorage *, gpsSensorInput *, gpsSensorOutput *);
//extern int initialize_accelerometer_sensor(imuStorage *, imuSensorInput *, imuSensorOutput *);
//

#endif