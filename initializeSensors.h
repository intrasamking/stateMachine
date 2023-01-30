
#ifndef INIT_SENSORS_h
#define INIT_SENSORS_h

#include "validateSensors.h"

extern DW* bpStorage, brakePipeStorage;
extern analogSensorInput* bpPressureIn, brakePipePressureIn;
extern analogSensorOutput* bpPressureOut, brakePipePressureOut;

extern DW* resStorage, reservoirStorage;
extern analogSensorInput* resPressureIn, reservoirPressureIn;
extern analogSensorOutput* resPressureOut, reservoirPressureOut;

//extern DW brakePipeStorage;
//extern analogSensorInput brakePipePressureIn;
//extern analogSensorOutput brakePipePressureOut;
//
//extern DW reservoirStorage;
//extern analogSensorInput reservoirPressureIn;
//extern analogSensorOutput reservoirPressureOut;

void initialize_brakepipe_sensor(void);

void initialize_reservoir_sensor(void);


#endif