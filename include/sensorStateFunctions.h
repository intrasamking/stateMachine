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
	double previousVx;
	double previousVy;
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

typedef struct {
	enum validityStates state;
	double sensorVal;
	int failure;
} analogSensorOutput;

typedef struct {
	enum validityStates state;
	double latitude;
	double longitude;
	double altitude;
	double vx;
	double vy;
	int failure;
} gpsSensorOutput;

typedef struct {
	enum validityStates state;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
	int failure;
} imuSensorOutput;

/** Sensor Structs **/
typedef struct {
	sensorTypes sensor_type;
	sensorNames sensor_name;
	sensorStates currentState;
	double sensorValue;
	enum validityStates validity;
	analogStorage *sensor_store;
	analogSensorOutput *sensor_out;
} analogSensorInput;

typedef struct {
	sensorNames sensor_name;
	sensorStates currentState;
	double latitude;
	double longitude;
	double altitude;
	double vx;
	double vy;
	enum validityStates validity;
	int quality;
	int satellitesInView;
	gpsStorage *gps_store;
	gpsSensorOutput *gps_out;
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
	imuSensorOutput *imu_out;
} imuSensorInput;

typedef struct {
	double latitude;
	double longitude;
	double altitude;
	int quality;
	int satellitesInView;
} gpsMessage;

typedef struct {
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz; 
} imuMessage;

extern analogSensorInput brakePipeSensorIn;
extern analogStorage brakePipeStorage;
extern analogSensorOutput brakePipeSensorOut;

extern analogSensorInput reservoirSensorIn;
extern analogStorage reservoirStorage;
extern analogSensorOutput reservoirSensorOut;

extern gpsStorage gpsStorageFr;
extern gpsStorage gpsStorageRr;

extern gpsSensorInput gpsSensorFrIn;
extern gpsSensorInput gpsSensorRrIn;

extern gpsSensorOutput gpsSensorFrOut;
extern gpsSensorOutput gpsSensorRrOut;

extern imuStorage imuStorageFr;
extern imuStorage imuStorageRr;

extern imuSensorInput imuSensorFrIn;
extern imuSensorInput imuSensorRrIn;

extern imuSensorOutput imuSensorFrOut;
extern imuSensorOutput imuSensorRrOut;

analogSensorOutput analogSensorValidation(analogSensorInput *);
gpsSensorOutput gpsSensorValidation(gpsSensorInput *);
imuSensorOutput imuSensorValidation(imuSensorInput *);

void initializeAnalogSensor(analogSensorInput *, analogStorage *, analogSensorOutput *, sensorNames sName, sensorTypes sTypes);
void initializeGPSsensor(gpsSensorInput *, gpsStorage *, gpsSensorOutput *, sensorNames sName);
void initializeIMUsensor(imuSensorInput *, imuStorage *, imuSensorOutput *, sensorNames sName);

void initializeAnalogMemory(analogStorage *);
void initializeGPSmemory(gpsStorage *);
void initializeIMUmemory(imuStorage *);

void intializeAnalogOutput(analogSensorOutput *);
void initializeGPSoutput(gpsSensorOutput *);
void initializeIMUoutput(imuSensorOutput *);

void setAnalogValue(analogSensorInput *, double sensorVal);
void setGPSvalue(gpsSensorInput *, gpsMessage *);
void setIMUvalue(imuSensorInput *, imuMessage *);

analogSensorOutput getAnalogValueOutput(analogSensorOutput *);
gpsSensorOutput getGPSvalueOutput(gpsSensorOutput *);
imuSensorOutput getIMUvalueOutput(imuSensorOutput *);

enum validityStates validatePressureReading(analogSensorInput *);
enum validityStates validateTemperatureReading(analogSensorInput *);
enum validityStates validateGPSreading(gpsSensorInput *);
enum validityStates validateIMUreading(imuSensorInput *);

#endif //SENSOR_STATE_h