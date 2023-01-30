#include "validateSensors.h"
#include <math.h>
#include <stdio.h>


void validate_pressure_state(DW* sensorValidateStorage, analogSensorInput* pressureInput, analogSensorOutput* pressureOutput)
{
	int validity;
	stateEvents currentEvent;
	states nextState;

	currentEvent = E_doNothing;
	nextState = S_NOTACTIVE;


	sensorValidateStorage->previous_signal = pressureInput->sensorValue;
	pressureInput->sensorValue = get_pressure_value();

	validity = validate_pressure_reading(pressureInput);

	if (validity != sensorValidateStorage->previous_validity)
	{
		switch (pressureInput->currentState)
		{
		case S_NOTACTIVE:
			currentEvent = E_goActive;
			nextState = S_ACTIVE;
			break;
		case S_BUFFERING:
			currentEvent = E_goActive;
			nextState = S_ACTIVE;
			break;
			//case S_ACTIVE:
		default:
			currentEvent = E_goBuffer;
			nextState = S_BUFFERING;
			break;
		}
	}
	else
	{
		switch (pressureInput->currentState)
		{
		case S_ACTIVE:
			currentEvent = E_doNothing;
			nextState = S_ACTIVE;
			break;
		case S_BUFFERING:
			if (sensorValidateStorage->temporalCounter > 20)
			{
				currentEvent = E_goPassive;
				nextState = S_NOTACTIVE;
				pressureOutput->sensorValue = -1;
				pressureOutput->failure = 1;
				sensorValidateStorage->temporalCounter = 0;
			}
			else
			{
				currentEvent = E_doNothing;
				nextState = S_BUFFERING;
				pressureOutput->sensorValue = sensorValidateStorage->previous_signal;
				pressureOutput->failure = 1;
				sensorValidateStorage->temporalCounter++;
			}
			break;
		default:
			currentEvent = E_doNothing;
			nextState = S_NOTACTIVE;
		}

	}

	if ((pressureInput->currentState = S_BUFFERING) && (nextState != S_BUFFERING))
	{
		sensorValidateStorage->temporalCounter = 0;
	}

	switch (nextState)
	{
	case S_ACTIVE:
		pressureInput->currentState = S_ACTIVE;
		sensorValidateStorage->logSignals = 1;
		pressureOutput->sensorValue = pressureInput->sensorValue;
		pressureOutput->failure = 0;
		break;
	case S_BUFFERING:
		pressureInput->currentState = S_BUFFERING;
		sensorValidateStorage->logSignals = 1;
		pressureOutput->sensorValue = sensorValidateStorage->previous_signal;
		pressureOutput->failure = 1;
		sensorValidateStorage->temporalCounter++;
		break;
		//case S_NOTACTIVE:
	default:
		pressureInput->currentState = S_NOTACTIVE;
		sensorValidateStorage->logSignals = 0;
		pressureOutput->sensorValue = -1;
		pressureOutput->failure = 1;
		break;
	}

	sensorValidateStorage->previous_validity = validity;
	switch (pressureInput->sensor_type)
	{
	case pressure:
		printf("Brakepipe \n");
		break;
	case temperature:
		printf("Reservoir \n");
		break;
	default:
		printf("Wrong \n");
		break;
	}

	printf("%d \n", nextState);
	if (sensorValidateStorage->logSignals)
	{
		//Send signals to tablet
	}
}

void validate_gps_state(gpsSensorBuffer* gps1Buffer, gpsSensorInput* gps1SensorIn, gpsSensorOutput* gps1SensorOut)
{
	int validity;
	stateEvents currentEvent;
	states nextState;

	currentEvent = E_doNothing;
	nextState = S_NOTACTIVE;

	gps1Buffer->previous_lat = gps1SensorIn->latitude;
	gps1Buffer->previous_long = gps1SensorIn->longitude;
	gps1Buffer->previous_alt = gps1SensorIn->altitude;
	
	get_gps_value(gps1SensorIn);
	
	validity = validate_gps_reading(gps1SensorIn);

	if (validity != gps1Buffer->previous_validity)
	{
		switch (gps1SensorIn->currentState)
		{

		}
	}
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

void get_gps_value(gpsSensorInput* gpsIn)
{

	gpsIn->latitude = 38.0;
	gpsIn->longitude = -90.0;
	gpsIn->altitude = 200;

	int qual;
	int sats;

	printf("Enter Quality (1-5): \n");
	scanf_s("%d", &qual);

	printf("Enter Satellites in View (1-13): \n");
	scanf_s("%d", &sats);

	gpsIn->quality = qual;
	gpsIn->satellitesInView = sats;
	//gpsIn->quality = 3;
	//gpsIn->satellitesInView = 5;

}

int validate_pressure_reading(analogSensorInput* pressureInput)
{
	double sensorReading;
	int validity;
	sensorReading = pressureInput->sensorValue;

	if ((fabs(sensorReading) < 160) && (fabs(sensorReading) > 0))
	{
		validity = 1;
	}
	else
	{
		validity = 0;
	}

	return validity;
}

int validate_gps_reading(gpsSensorInput* gpsInput)
{
	int SIV;
	int validity;
	SIV = gpsInput->satellitesInView;
	if (SIV >= 4)
	{
		validity = 1;
	}
	else
	{
		validity = 0;
	}

	return validity;
}

int validate_imu_reading(imuSensorInput* imuInput)
{
	int validity;

	if ((fabs(imuInput->ax) > 78.48) || (fabs(imuInput->ay) > 78.48) || (fabs(imuInput->az) > 78.48))
	{
		validity = 0;
	}
	else if ((fabs(imuInput->ax) > 245) || (fabs(imuInput->ay) > 245) || (fabs(imuInput->az) > 245))
	{
		validity = 0;
	}
	else
	{
		validity = 1;
	}

	return validity;
}