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

extern analogSensorOutput analogSensorValidation(analogSensorInput *);
extern gpsSensorOutput gpsSensorValidation(gpsSensorInput *);
extern imuSensorOutput imuSensorValidation(imuSensorInput *);

extern void initializeAnalogSensor(analogSensorInput *, analogStorage *, analogSensorOutput *, sensorTypes, sensorNames);
extern void initializeGPSsensor(gpsSensorInput *, gpsStorage *, gpsSensorOutput *, sensorNames sName);
extern void initializeIMUsensor(imuSensorInput *, imuStorage *, imuSensorOutput *, sensorNames sName);

extern void initializeAnalogMemory(analogStorage *);
extern void initializeGPSmemory(gpsStorage *);
extern void initializeIMUmemory(imuStorage *);

extern void initializeAnalogOutput(analogSensorOutput *);
extern void initializeGPSoutput(gpsSensorOutput *);
extern void initializeIMUoutput(imuSensorOutput *);

extern void setAnalogValue(analogSensorInput *, double sensorVal);
extern void setGPSvalue(gpsSensorInput *, gpsMessage *);
extern void setIMUvalue(imuSensorInput *, imuMessage *);

extern analogSensorOutput getAnalogValueOutput(analogSensorOutput *);
extern gpsSensorOutput getGPSvalueOutput(gpsSensorOutput *);
extern imuSensorOutput getIMUvalueOutput(imuSensorOutput *);

extern enum validityStates validatePressureReading(analogSensorInput *);
extern enum validityStates validateTemperatureReading(analogSensorInput *);
extern enum validityStates validateGPSreading(gpsSensorInput *);
extern enum validityStates validateIMUreading(imuSensorInput *);

#endif //SENSOR_STATE_h