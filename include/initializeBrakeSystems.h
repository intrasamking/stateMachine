#ifndef INIT_BRAKES_h
#define INIT_BRAKES_h

#include "brakeStatusManager.h"

extern analogSensorOutput* bpPressureOut, brakePipePressureOut;
extern BMS_status* bmsPtr, bmsInfo;
extern regenBrakeStatus* regenSysPtr, regenSysStatus;
extern airBrakeStatus* airSysPtr, airSysStatus;
extern emergencyBrakeStatus* embSystPtr, embSysStatus;

void initialize_regen_status(void);
void initialize_airbrake_status(void);
void intialize_emergenbybrake_status(void);


#endif