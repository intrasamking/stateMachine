#include <stddef.h>
#include <stdio.h>     
#include "initializeSensors.h"
#include "validateSensors.h"                  

int main(void)
{
	int s;
	sensorPointers sensorAddrs;

	extern DW* bpStorage, brakePipeStorage;
	extern analogSensorInput* bpPressureIn, brakePipePressureIn;
	extern analogSensorOutput* bpPressureOut, brakePipePressureOut;

	extern DW* resStorage, reservoirStorage;
	extern analogSensorInput* resPressureIn, reservoirPressureIn;
	extern analogSensorOutput* resPressureOut, reservoirPressureOut;

	extern gpsStorage* gpsStore1, gpsStorage1;
	extern gpsSensorInput* gpsIn1, gpsSensorIn1;
	extern gpsSensorOutput* gpsOut1, gpsSensorOut1;


	sensorAddrs = initialize_sensors();

	// 
	//while (s = 1)
	//{
	//	validate_pressure_state(bpStorage, bpPressureIn, bpPressureOut);
	//	validate_pressure_state(resStorage, resPressureIn, resPressureOut);
	//	validate_gps_state(gps1BufferPtr, gps1SensorInPtr, gps1SensorOutPtr);
	//}

	return 0;

}

