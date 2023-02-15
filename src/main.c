#include <stddef.h>
#include <stdio.h>     
//#include "validateSensors.h"                  
#include "sensorStateFunctions.h"

extern analogStorage brakePipeStorage;
extern analogStorage reservoirStorage;

extern analogSensorInput brakePipeSensor;
extern analogSensorInput reservoirSensor;

extern gpsStorage gpsStorageFront;
extern gpsStorage gpsStorageRear;

extern gpsSensorInput gpsSensorFront;
extern gpsSensorInput gpsSensorRear;

extern imuStorage imuStorageFront;
extern imuStorage imuStorageRear;

extern imuSensorInput imuSensorFront;
extern imuSensorInput imuSensorRr;

int main()
{

	int s;
	initializeAnalogSensor(&brakePipeSensor, &brakePipeStorage, pressure, primary);
	initializeAnalogSensor(&reservoirSensor, &reservoirStorage, pressure, primary);

	s = 1;
	return 0;
}