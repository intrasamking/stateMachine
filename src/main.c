#include <stddef.h>
#include <stdio.h>     
#include "initializeSensors.h"
#include "validateSensors.h"                  

int main(void)
{
	int s;
	sensorPointers sensorAddrs;

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

