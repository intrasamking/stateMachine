#include <stddef.h>
#include <stdio.h>     
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
	initializeIMUsensor(&imuSensorFrIn, &imuStorageFr, &imuSensorFrOut, primary);

	// Set Pressure Value
	double sensorInput = 85;
	setAnalogValue(&brakePipeSensorIn, sensorInput);

	// Validate Pressure Value
	analogSensorOutput sOut;
	sOut = analogSensorValidation(&brakePipeSensorIn);
	printf("Pressure Sensor \n");
	printf("%d - %lf \n", sOut.state, sOut.sensorVal);


	// Generic GPS Message to use for input
	gpsMessage gmsg;

	gmsg.latitude = 38;
	gmsg.longitude = -90; 
	gmsg.altitude = 100; 
	gmsg.quality = 4;
	gmsg.satellitesInView = 6;

	// Set GPS Value
	setGPSvalue(&gpsSensorFrIn, &gmsg);

	// Validate GPS Value
	gpsSensorOutput gOut;
	gOut = gpsSensorValidation(&gpsSensorFrIn);

	printf("GPS Sensor \n");
	printf("%d \n", gOut.state);

	// Generic IMU Message to use for Input
	imuMessage imsg;

	imsg.ax = 1;
	imsg.ay = 2;
	imsg.az = 3;
	imsg.gx = 1;
	imsg.gy = 10;
	imsg.gz = 12;

	// Set IMU Value
	setIMUvalue(&imuSensorFrIn, &imsg);

	// Validate IMU Value
	imuSensorOutput iOut;
	iOut = imuSensorValidation(&imuSensorFrIn);

	printf("IMU Sensor \n");
	printf("%d", iOut.state);

	return 0; 
}