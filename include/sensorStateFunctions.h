#pragma once

#ifndef SENSOR_STATE_h
#define SENSOR_STATE_h

typedef enum {
	S_NOTCONNECTED = 0,
	S_NOTACTIVE = 1,
	S_BUFFERING = 2,
	S_ACTIVE = 3
} sensorStates;

typedef enum { S_NOTLOGGING = 0, S_LOGGING = 1 } loggingStates;

typedef enum { E_doNothing = 0, E_goActive = 1, E_goPassive = 2, E_goBuffer = 3 } stateEvents;

typedef enum { E_staySame = 0, E_goLogging = 1, E_goNotLogging = 2 } loggingEvents;

typedef enum { temperature, pressure } sensorTypes;

typedef enum { primary, secondary, tertiary } sensorNames;

typedef enum { noConnect, notValid, Valid} validityStates;

/** Storage Structs **/

typedef struct {
	double previous_signal;
	enum validityStates previous_validity;
	int temporalCounter;
	int logSignals;
} analogStorage;

typedef struct {
	double previousLat;
	double previousLong;
	double previousAlt;
	enum validityStates previous_validity;
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
	enum validityStates previous_validity;
	int temporalCounter;
	int logSignals;
} imuStorage;

/** Sensor Structs **/
typedef struct {
	sensorTypes sensor_type;
	sensorNames sensor_name;
	sensorStates currentState;
	double sensorValue;
	enum validityStates validity;
	analogStorage *sensor_store;
} analogSensorInput;

typedef struct {
	sensorNames sensor_name;
	sensorStates currentState;
	double latitude;
	double longitude;
	double altitude;
	enum validityStates validity;
	int quality;
	int satellitesInView;
	gpsStorage *gps_store;
} gpsSensorInput;

typedef struct {
	sensorNames sensor_name;
	sensorStates currentState;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
	enum validityStates validity;
	imuStorage *imu_store;
} imuSensorInput;

extern analogStorage brakePipeStorage;
extern analogStorage reservoirStorage;

extern analogSensorInput brakePipeSensor;
extern analogSensorInput reservoirSensor;

extern gpsStorage gpsStorageFront;
extern gpsStorage gpsStorageRear;

extern gpsSensorInput gpsSensorFront;
extern gpsSensorInput gpsSensorRear;

extern imuStorage imuStorageFront;
extern imuStorage imuStorageRear;

extern imuSensorInput imuSensorFront;
extern imuSensorInput imuSensorRr;

void analogSensorValidation(analogSensorInput *);
void gpsSensorValidation(gpsSensorInput *);
void imuSensorValidation(imuSensorInput *);

void initializeAnalogSensor(analogSensorInput *, analogStorage *, sensorNames sName, sensorTypes sTypes);
void initializeGPSsensor(gpsSensorInput *, gpsStorage *, sensorNames sName);
void initializeIMUsensor(imuSensorInput *, imuStorage *, sensorNames sName);

void initializeAnalogMemory(analogStorage *);
void initializeGPSmemory(gpsStorage *);
void initializeIMUmemory(imuStorage *);

void setAnalogValue(analogSensorInput *, double sensorVal);
void setGPSvalue(gpsSensorInput *, double latVal, double longVal, double altVal, int qualVal, int SIV);
void setIMUvalue(imuSensorInput *, double axVal, double ayVal, double azVal, double gxVal, double gyVal, double gzVal);

enum validityStates  validatePressureReading(analogSensorInput *);
enum validityStates  validateTemperatureReading(analogSensorInput *);
enum validityStates  validateGPSreading(gpsSensorInput *);
enum validityStates  validateIMUreading(imuSensorInput *);




#endif //SENSOR_STATE_h