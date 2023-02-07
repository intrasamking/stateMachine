#include <stddef.h>
#include <stdio.h>     
#include "initializeSensors.h"
#include "validateSensors.h"                  

struct gpsMsg {
	double latVal;
	double longVal;
	double altVal;
	int qualVal;
	int satVal;
};

double get_pressure_value();
void get_gps_value(struct gpsMsg *);

int main(void)
{

	struct gpsMsg gpsInputMsg = { .latVal = 0 };
	struct gpsMsg *gpsInputPtr;
	gpsInputPtr = &gpsInputMsg;

	int s;

	sensorPointers sensorAddrs;
	sensorAddrs = initialize_sensors();

	s = 1;
	double pressureIn;
	states nextState;
	analogSensorInput *testVal;
	testVal = sensorAddrs.bpPresIn;

	while (s = 1)
	{
		pressureIn = get_pressure_value();
		set_pressure_value(pressureIn,testVal);
		nextState = validate_pressure_state(sensorAddrs.bpStore, sensorAddrs.bpPresIn, sensorAddrs.bpPresOut);

		switch (nextState)
		{
		case S_ACTIVE:
			printf("Active \n");
			break;
		case S_BUFFERING:
			printf("Buffering \n");
			break;
		default:
			printf("Not Active \n");
			break;
		}
	}

	return 0;

}

double get_pressure_value()
{
	double pressureVal;

	printf("Enter pressure: ");
	if (scanf_s("%lf", &pressureVal) == 1)
	{
		return pressureVal;
	}
	else
	{
		pressureVal = 171;
		return pressureVal;
	}
}

void get_gps_value(struct gpsMsg *gpsIn)
{

	gpsIn->latVal = 38.0;
	gpsIn->longVal = -90.0;
	gpsIn->altVal = 200;

	int qual;
	int sats;

	printf("Enter Quality (1-5): \n");
	scanf_s("%d", &qual);

	printf("Enter Satellites in View (1-13): \n");
	scanf_s("%d", &sats);

	gpsIn->qualVal = qual;
	gpsIn->satVal = sats;
	//gpsIn->quality = 3;
	//gpsIn->satellitesInView = 5;

}