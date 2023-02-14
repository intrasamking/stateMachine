#include <stddef.h>
#include <stdio.h>     
//#include "validateSensors.h"                  
#include "sensorStateFunctions.h"


//struct gpsMsg {
//	double latVal;
//	double longVal;
//	double altVal;
//	int qualVal;
//	int satVal;
//};
//
//double get_pressure_value();
//void get_gps_values(struct gpsMsg *);

int main()
{

	//struct gpsMsg gpsInputMsg = { .latVal = 0 };
	//struct gpsMsg *gpsInputPtr;
	//gpsInputPtr = &gpsInputMsg;

	int s;
	s = 1;
	analogIn *in = init();

	initialize_pressure_sensor(in, primary);
	set_analog_value(in, 50);
	printf("%f \n", get_analog_value(in));

	//sensorPointers sensorAddrs;

	//analogIn *inputPtr = init();
	//analogOut outputPtr = initOut();
	//analogStorage storagePtr = initSt();

	//initialize_pressure_sensorIn(inputPtr, primary);
	//printf("SensorValue \n");
	//printf("%f \n", get_analog_value(inputPtr));

	//outputPtr = intialize_pressure_sensorOut(inputPtr, outputPtr);
	//storagePtr = intialize_pressure_sensorStorage(inputPtr, storagePtr);

	//sensorAddrs = initialize_sensors(inputPtr, outputPtr, storagePtr);

	//double pressureIn;
	//states nextState;

	//while (s = 1)
	//{
	//	pressureIn = get_pressure_value();
	//	set_analog_value(pressureIn, sensorAddrs.bpPresIn);
	//	nextState = validate_pressure_state(sensorAddrs.bpStore, sensorAddrs.bpPresIn, sensorAddrs.bpPresOut);

	//	switch (nextState)
	//	{
	//	case S_ACTIVE:
	//		printf("Active \n");
	//		break;
	//	case S_BUFFERING:
	//		printf("Buffering \n");
	//		break;
	//	default:
	//		printf("Not Active \n");
	//		break;
	//	}
	//}

	return 0;

}

//double get_pressure_value()
//{
//	double pressureVal;
//
//	printf("Enter pressure: ");
//	if (scanf_s("%lf", &pressureVal) == 1)
//	{
//		return pressureVal;
//	}
//	else
//	{
//		pressureVal = 171;
//		return pressureVal;
//	}
//}
//
//void get_gps_values(struct gpsMsg *gpsIn)
//{
//
//	gpsIn->latVal = 38.0;
//	gpsIn->longVal = -90.0;
//	gpsIn->altVal = 200;
//
//	int qual;
//	int sats;
//
//	printf("Enter Quality (1-5): \n");
//	scanf_s("%d", &qual);
//
//	printf("Enter Satellites in View (1-13): \n");
//	scanf_s("%d", &sats);
//
//	gpsIn->qualVal = qual;
//	gpsIn->satVal = sats;
//	//gpsIn->quality = 3;
//	//gpsIn->satellitesInView = 5;
//
//}