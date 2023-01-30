
#ifndef INIT_SENSORS_h
#define INIT_SENSORS_h

#include "validateSensors.h"

extern DW* bpStorage, brakePipeStorage;
extern analogSensorInput* bpPressureIn, brakePipePressureIn;
extern analogSensorOutput* bpPressureOut, brakePipePressureOut;

extern DW* resStorage, reservoirStorage;
extern analogSensorInput* resPressureIn, reservoirPressureIn;
extern analogSensorOutput* resPressureOut, reservoirPressureOut;

extern gpsSensorBuffer* gps1BufferPtr, gps1Buffer;
extern gpsSensorInput* gps1SensorInPtr, gps1SensorIn;
extern gpsSensorOutput* gps1SensorOutPtr, gps1SensorOut;

void initialize_brakepipe_sensor(void);

void initialize_reservoir_sensor(void);

void initialize_gps_sensor(void);

#endif