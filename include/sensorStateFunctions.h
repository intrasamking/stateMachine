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

typedef struct analogSensorInput analogIn;
typedef struct analogSensorOutput analogOut;
typedef struct analogSensorStorage analogStorage;

analogIn *init();

void set_analog_value(analogIn *inst, double analogValue);
void initialize_pressure_sensor(analogIn *inst, enum sensorName sName);
double get_analog_value(analogIn *inst);
int validate_pressure_reading(analogIn *inst);

#endif //SENSOR_STATE_h