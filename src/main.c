#include <stddef.h>
#include <stdio.h>     
//#include "validateSensors.h"                  
#include "sensorStateFunctions.h"

extern analogSensorInput brakePipeSensorIn;
extern analogStorage brakePipeStorage;
extern analogSensorOutput brakePipeSensorOut;

extern analogSensorInput reservoirSensorIn;
extern analogStorage reservoirStorage;
extern analogSensorOutput reservoirSensorOut;

extern gpsStorage gpsStorageFr;
extern gpsStorage gpsStorageRr;

extern gpsSensorInput gpsSensorFrIn;
extern gpsSensorInput gpsSensorRrIn;

extern gpsSensorOutput gpsSensorFrOut;
extern gpsSensorOutput gpsSensorRrOut;

extern imuStorage imuStorageFr;
extern imuStorage imuStorageRr;

extern imuSensorInput imuSensorFrIn;
extern imuSensorInput imuSensorRrIn;

extern imuSensorOutput imuSensorFrOut;
extern imuSensorOutput imuSensorRrOut;

int main()
{

	int s;
	initializeAnalogSensor(&brakePipeSensorIn, &brakePipeStorage, &brakePipeSensorOut, pressure, primary);
	initializeAnalogSensor(&reservoirSensorIn, &reservoirStorage, &reservoirSensorOut, pressure, primary);
	initializeGPSsensor(&gpsSensorFrIn, &gpsStorageFr, &gpsSensorFrOut, primary);
	initializeGPSsensor(&gpsSensorRrIn, &gpsStorageRr, &gpsSensorRrOut, secondary);

	s = 1;
	return 0;
}