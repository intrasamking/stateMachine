#include <stddef.h>
#include <stdio.h>
#include "initializeBrakeSystems.h"
#include "brakeStatusManager.h"

analogSensorOutput* bpPressureOut, brakePipePressureOut;
BMS_status* bmsPtr, bmsInfo;
regenBrakeStatus* regenSysPtr, regenSysStatus;
airBrakeStatus* airSysPtr, airSysStatus;
emergencyBrakeStatus* embSysPtr, embSysStatus;

void initialize_regen_status(void)
{
	bmsInfo.stateOfCharge = 0.0;
	bmsInfo.maxCharge = 1.0;
	bmsInfo.maxDischarge = 1.0;
	bmsPtr = &bmsInfo;

	regenSysStatus.regen_status = 0;
	regenSysStatus.previous_regen_status = 0;
	regenSysPtr = &regenSysStatus;
}

void initialize_airbrake_status(void)
{
	brakePipePressureOut.sensor_name = primary;
	brakePipePressureOut.sensor_type = pressure;
	brakePipePressureOut.failure = 1;
	bpPressureOut = &brakePipePressureOut;

	airSysStatus.airbrake_status = 0;
	airSysStatus.previous_airbrake_status = 0;
	airSysPtr = &airSysStatus;
}

void intialize_emergenbybrake_status(void)
{
	embSysStatus.emergencyBrake_status = 0;
	embSysStatus.previous_emergencyBrake_status = 0;
	embSysPtr = &embSysStatus;
}