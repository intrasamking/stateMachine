#include <stddef.h>
#include <stdio.h>            
#include "initializeSensors.h"

DW* bpStorage, brakePipeStorage;
analogSensorInput* bpPressureIn, brakePipePressureIn;
analogSensorOutput* bpPressureOut, brakePipePressureOut;

DW* resStorage, reservoirStorage;
analogSensorInput* resPressureIn, reservoirPressureIn;
analogSensorOutput* resPressureOut, reservoirPressureOut;

gpsStorage* gpsStore1, gpsStorage1;
gpsSensorInput* gpsIn1, gpsSensorIn1;
gpsSensorOutput* gpsOut1, gpsSensorOut1;


sensorPointers initialize_sensors()
{
	int bp_init;
	int res_init;
	int gps_init;
	sensorPointers sensorPtrs;

	DW brakePipeStorage = { .temporalCounter = 0 };
	DW *bpStorage = &brakePipeStorage;
	analogSensorInput brakePipePressureIn = { .sensor_name = primary };
	analogSensorInput *bpPressureIn = &brakePipePressureIn;
	analogSensorOutput brakePipePressureOut = { .sensor_name = primary };
	analogSensorOutput *bpPressureOut = &brakePipePressureOut;

	DW reservoirStorage = { .temporalCounter = 0 };
	DW *resStorage = &reservoirStorage;
	analogSensorInput reservoirPressureIn = { .sensor_name = primary };
	analogSensorInput *resPressureIn = &reservoirPressureIn;
	analogSensorOutput reservoirPressureOut = { .sensor_name = primary };
	analogSensorOutput *resPressureOut = &reservoirPressureOut;

	gpsStorage gpsStorage1 = { .temporalCounter = 0 };
	gpsStorage *gpsStore1 = &gpsStorage1;
	gpsSensorInput gpsSensorIn1 = { .sensor_name = primary };
	gpsSensorInput *gpsIn1 = &gpsSensorIn1;
	gpsSensorOutput gpsSensorOutput1 = { .sensor_name = primary };
	gpsSensorOutput *gpsOut1 = &gpsSensorOutput1;

	bp_init = initialize_pressure_sensor(bpStorage, bpPressureIn, bpPressureOut);
	res_init = initialize_pressure_sensor(resStorage, resPressureIn, resPressureOut);
	gps_init = initialize_gps_sensor(gpsStore1, gpsIn1, gpsOut1);

	sensorPtrs.bpPresIn = bpPressureIn;
	sensorPtrs.bpPresOut = bpPressureOut;
	sensorPtrs.bpStore = bpStorage;
	sensorPtrs.resPresIn = resPressureIn;
	sensorPtrs.resPresOut = resPressureOut;
	sensorPtrs.resStore = resStorage;
	sensorPtrs.gpsIn1 = gpsIn1;
	sensorPtrs.gpsOut1 = gpsOut1;
	sensorPtrs.gpsStore = gpsStore1;

	return sensorPtrs;
}


int initialize_pressure_sensor(DW *pressureStorage, analogSensorInput *pressureSensorIn, analogSensorOutput *pressureSensorOut)
{

	pressureSensorIn->sensor_type = pressure;
	pressureSensorIn->currentState = S_NOTACTIVE;

	pressureSensorOut->sensor_name = primary;
	pressureSensorOut->sensor_type = pressure;
	pressureSensorOut->failure = 1;

	pressureStorage->previous_signal = 0;
	pressureStorage->previous_validity = 0;
	pressureStorage->logSignals = 0;
	return 1;


}

int initialize_temperature_sensor(DW* pressureStorage, analogSensorInput* pressureSensorIn, analogSensorOutput* pressureSensorOut)
{

	pressureSensorIn->sensor_type = temperature;
	pressureSensorIn->currentState = S_NOTACTIVE;

	pressureSensorOut->sensor_name = primary;
	pressureSensorOut->sensor_type = pressure;
	pressureSensorOut->failure = 1;

	pressureStorage->previous_signal = 0;
	pressureStorage->previous_validity = 0;
	pressureStorage->logSignals = 0;
	return 1;


}

int initialize_gps_sensor(gpsStorage* gpsStore, gpsSensorInput* gpsSensorIn, gpsSensorOutput* gpsSensorOut)
{
	gpsSensorIn->currentState = S_NOTACTIVE;
	gpsSensorIn->latitude = 0;
	gpsSensorIn->longitude = 0;
	gpsSensorIn->altitude = 0;
	gpsSensorIn->quality = 0;
	gpsSensorIn->satellitesInView = 0;
	gpsSensorIn->validity = 0;

	gpsSensorOut->currentState = S_NOTACTIVE;
	gpsSensorOut->latitude = 0;
	gpsSensorOut->longitude = 0;
	gpsSensorOut->altitude = 0;
	gpsSensorOut->quality = 0;
	gpsSensorOut->satellitesInView = 0;
	gpsSensorOut->failure = 1;

	gpsStore->previousAlt = 0;
	gpsStore->previousLat = 0;
	gpsStore->previousLong = 0;
	gpsStore->previous_validity = 0;
	gpsStore->logSignals = 0;

	return 1;


}

int initialize_accelerometer_sensor(imuStorage* imuStore, imuSensorInput* imuSensorIn, imuSensorOutput* imuSensorOut)
{
	imuSensorIn->currentState = S_NOTACTIVE;
	imuSensorIn->ax = 0;
	imuSensorIn->ay = 0;
	imuSensorIn->az = 0;
	imuSensorIn->gx = 0;
	imuSensorIn->gy = 0;
	imuSensorIn->gz = 0;
	imuSensorIn->validity = 0;

	imuSensorOut->currentState = S_NOTACTIVE;
	imuSensorOut->ax = 0;
	imuSensorOut->ay = 0;
	imuSensorOut->az = 0;
	imuSensorOut->gx = 0;
	imuSensorOut->gy = 0;
	imuSensorOut->gz = 0;
	imuSensorOut->failure = 0;

	imuStore->previous_ax = 0;
	imuStore->previous_ay = 0;
	imuStore->previous_az = 0;
	imuStore->previous_gx = 0;
	imuStore->previous_gy = 0;
	imuStore->previous_gz = 0;
	imuStore->logSignals = 0;
	imuStore->temporalCounter = 0;
	imuStore->previous_validity = 0;

	return 1;

}