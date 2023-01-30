#include <stddef.h>
#include <stdio.h>     
#include "initializeSensors.h"
#include "validateSensors.h"                  

int main(void)
{
	int s;
	s = 1;

	extern DW* bpStorage, brakePipeStorage;
	extern analogSensorInput* bpPressureIn, brakePipePressureIn;
	extern analogSensorOutput* bpPressureOut, brakePipePressureOut;

	extern DW* resStorage, reservoirStorage;
	extern analogSensorInput* resPressureIn, reservoirPressureIn;
	extern analogSensorOutput* resPressureOut, reservoirPressureOut;

	initialize_brakepipe_sensor();
	initialize_reservoir_sensor();

	while (s = 1)
	{
		validate_pressure_state(bpStorage, bpPressureIn, bpPressureOut);
		validate_pressure_state(resStorage, resPressureIn, resPressureOut);
	}

	return 0;

}

