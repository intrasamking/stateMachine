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

	s = 1;
	double sensorInput = 0;
	int intInput = 0;
	while (s == 1)
	{
		//printf("Input Target Percentage: ");
		//scanf_s("%lf", &sensorInput);

		//// Set Pressure Value
		//setAnalogValue(&brakePipeSensorIn, sensorInput);

		//// Validate Pressure Value
		//analogSensorOutput sOut;
		//sOut = analogSensorValidation(&brakePipeSensorIn);
		//printf("Pressure Sensor \n");
		//printf("%d - %lf \n", sOut.state, sOut.sensorVal);


		//printf("Input GPS Satellites: ");
		//scanf_s("%d", &intInput);

		//// Generic GPS Message to use for input

		////setGPSvalue(&gpsSensorFrIn, &gmsg);

		//gpsMessage gmsg;

		//gmsg.latitude = 38;
		//gmsg.longitude = -90; 
		//gmsg.altitude = 100; 
		//gmsg.quality = 4;
		//gmsg.satellitesInView = intInput;

		//// Set GPS Value
		//setGPSvalue(&gpsSensorFrIn, &gmsg);

		//// Validate GPS Value
		//gpsSensorOutput gOut;
		//gOut = gpsSensorValidation(&gpsSensorFrIn);

		//printf("GPS Sensor State \n");
		//printf("%d \n", gOut.state);

		printf("Input Imu Acceleration: ");
		scanf_s("%lf", &sensorInput);
 
		// Generic IMU Message to use for Input
		imuMessage imsg;

		//imsg.ax = 1;
		imsg.ax = 1;
		imsg.ay = sensorInput;
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
		printf("%d \n", iOut.state);
	}
	return 0; 
}