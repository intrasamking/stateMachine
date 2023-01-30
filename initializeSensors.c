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