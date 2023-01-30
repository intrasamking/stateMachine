#include <stddef.h>
#include <stdio.h>            
#include "initializeSensors.h"
#include "validateSensors.h"


DW* bpStorage, brakePipeStorage;
analogSensorInput* bpPressureIn, brakePipePressureIn;
analogSensorOutput* bpPressureOut, brakePipePressureOut;

DW* resStorage, reservoirStorage;
analogSensorInput* resPressureIn, reservoirPressureIn;
analogSensorOutput* resPressureOut, reservoirPressureOut;

gpsSensorBuffer* gps1BufferPtr, gps1Buffer;
gpsSensorInput* gps1SensorInPtr, gps1SensorIn;
gpsSensorOutput* gps1SensorOutPtr, gps1SensorOut;

void initialize_brakepipe_sensor(void)
{

	brakePipePressureIn.sensor_name = primary;
	brakePipePressureIn.sensor_type = pressure;
	brakePipePressureIn.currentState = S_NOTACTIVE;

	brakePipePressureOut.sensor_name = primary;
	brakePipePressureOut.sensor_type = pressure;
	brakePipePressureOut.failure = 1;

	brakePipeStorage.previous_signal = 0;
	brakePipeStorage.previous_validity = 0;
	brakePipeStorage.logSignals = 0;

	bpStorage = &brakePipeStorage;
	bpPressureIn = &brakePipePressureIn;
	bpPressureOut = &brakePipePressureOut;

}

void initialize_reservoir_sensor(void)
{
	reservoirPressureIn.sensor_name = primary;
	reservoirPressureIn.sensor_type = temperature;
	reservoirPressureIn.currentState = S_NOTACTIVE;

	reservoirPressureOut.sensor_name = primary;
	reservoirPressureOut.sensor_type = temperature;
	reservoirPressureOut.failure = 1;

	reservoirStorage.previous_signal = 0;
	reservoirStorage.previous_validity = 0;
	reservoirStorage.logSignals = 0;

	resStorage = &reservoirStorage;
	resPressureIn = &reservoirPressureIn;
	resPressureOut = &reservoirPressureOut;

}

void initialize_gps_sensor(void)
{
	gps1SensorIn.sensor_name = primary;
	gps1SensorIn.currentState = S_NOTACTIVE;
	gps1SensorIn.latitude = 0;
	gps1SensorIn.longitude = 0;
	gps1SensorIn.altitude = 0;
	gps1SensorIn.quality = 0;
	gps1SensorIn.satellitesInView = 0;

	gps1SensorInPtr = &gps1SensorIn;

	gps1SensorOut.sensor_name = gps1SensorIn.sensor_name;
	gps1SensorOut.currentState = S_NOTACTIVE;
	gps1SensorOut.latitude = 0;
	gps1SensorOut.longitude = 0;
	gps1SensorOut.altitude = 0;
	gps1SensorOut.quality = 0;
	gps1SensorOut.satellitesInView = 0;

	gps1SensorOutPtr = &gps1SensorOut;

	gps1Buffer.logSignals = 0;
	gps1Buffer.temporalCounter = 0;
	gps1Buffer.previous_validity = 0;
	gps1Buffer.previous_lat = 0;
	gps1Buffer.previous_long = 0;
	gps1Buffer.previous_alt = 0;

	gps1BufferPtr = &gps1Buffer;
}