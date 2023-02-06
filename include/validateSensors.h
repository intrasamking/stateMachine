#ifndef RTW_HEADER_validate_h_
#define RTW_HEADER_validate_h_

#include "initializeSensors.h"

extern void validate_pressure_state(DW*, analogSensorInput*, analogSensorOutput*);
extern double get_pressure_value();
extern int validate_pressure_reading(analogSensorInput*);
extern int validate_gps_reading(gpsSensorInput*);
extern int validate_imu_reading(imuSensorInput*);

extern DW* bpStorage, brakePipeStorage;
extern analogSensorInput* bpPressureIn, brakePipePressureIn;
extern analogSensorOutput* bpPressureOut, brakePipePressureOut;

extern DW* resStorage, reservoirStorage;
extern analogSensorInput* resPressureIn, reservoirPressureIn;
extern analogSensorOutput* resPressureOut, reservoirPressureOut;

extern gpsStorage* gpsStore1, gpsStorage1;
extern gpsSensorInput* gpsIn1, gpsSensorIn1;
extern gpsSensorOutput* gpsOut1, gpsSensorOut1;

#endif