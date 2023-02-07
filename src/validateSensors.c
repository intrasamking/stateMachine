#include "validateSensors.h"
#include <math.h>
#include <stdio.h>


states validate_pressure_state(DW *sensorValidateStorage, analogSensorInput *pressureInput, analogSensorOutput *pressureOutput)
{
	int validity;
	stateEvents currentEvent;
	states nextState;

	currentEvent = E_doNothing;
	nextState = S_NOTACTIVE;


	sensorValidateStorage->previous_signal = pressureInput->sensorValue;

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
				//nextState = S_NOTACTIVE;
				//pressureOutput->sensorValue = -1;
				//pressureOutput->failure = 1;
				sensorValidateStorage->temporalCounter = 0;
			}
			else
			{
				currentEvent = E_doNothing;
				nextState = S_BUFFERING;
				//pressureOutput->sensorValue = sensorValidateStorage->previous_signal;
				//pressureOutput->failure = 1;
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

	states returnVal;
	returnVal = pressureInput->currentState;
	return returnVal;
}

states validate_gps_state(gpsStorage *gpsBuffer, gpsSensorInput *gpsSensorIn, gpsSensorOutput *gpsSensorOut)
{
	int validity;
	stateEvents currentEvent;
	states nextState;

	currentEvent = E_doNothing;
	nextState = S_NOTACTIVE;
		
	validity = validate_gps_reading(gpsSensorIn);

	if (validity != gpsBuffer->previous_validity)
	{
		switch (gpsSensorIn->currentState)
		{
		case S_NOTACTIVE:
			nextState = S_ACTIVE;
			break;
		case S_BUFFERING:
			nextState = S_ACTIVE;
			break;
		//case S_ACTIVE:
		default:
			nextState = S_BUFFERING;
			break;
		}
	}
	else
	{
		switch (gpsSensorIn->currentState)
		{
		case S_ACTIVE:
			nextState = S_ACTIVE;
			break;
		case S_BUFFERING:
			if (gpsBuffer->temporalCounter > 20)
			{
				nextState = S_NOTACTIVE;
				gpsBuffer->temporalCounter = 0;
			}
			else
			{
				nextState = S_BUFFERING;
				gpsBuffer->temporalCounter++;
			}
			break;
		default:
			nextState = S_NOTACTIVE;
			break;
		}

	}

	if ((gpsSensorIn->currentState = S_BUFFERING) && (nextState != S_BUFFERING))
	{
		gpsBuffer->temporalCounter = 0;
	}

	switch (nextState)
	{
	case S_ACTIVE:
		gpsSensorIn->currentState = S_ACTIVE;
		gpsBuffer->logSignals = 1;
		gpsSensorOut->latitude = gpsSensorIn->latitude;
		gpsSensorOut->longitude = gpsSensorIn->longitude;
		gpsSensorOut->altitude = gpsSensorIn->altitude;
		gpsSensorOut->failure = 0;

		gpsBuffer->previousLat = gpsSensorIn->latitude;
		gpsBuffer->previousLong = gpsSensorIn->longitude;
		gpsBuffer->previousAlt = gpsSensorIn->altitude;

		break;
	case S_BUFFERING:
		gpsSensorIn->currentState = S_BUFFERING;
		gpsBuffer->logSignals = 1;
		gpsSensorOut->latitude = gpsBuffer->previousLat;
		gpsSensorOut->longitude = gpsBuffer->previousLong;
		gpsSensorOut->altitude = gpsBuffer->previousAlt;
		gpsSensorOut->failure = 1;
		gpsBuffer->temporalCounter++;
		break;
		//case S_NOTACTIVE:
	default:
		gpsSensorIn->currentState = S_NOTACTIVE;
		gpsBuffer->logSignals = 0;
		gpsSensorOut->latitude = 0;
		gpsSensorOut->longitude = 0;
		gpsSensorOut->altitude = 0;
		gpsSensorOut->failure = 1;

		gpsBuffer->previousLat = gpsSensorIn->latitude;
		gpsBuffer->previousLong = gpsSensorIn->longitude;
		gpsBuffer->previousAlt = gpsSensorIn->altitude;

		break;

	}
	gpsBuffer->previous_validity = validity;

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

	states returnVal;
	returnVal = gpsSensorIn->currentState;
	return returnVal;

}

void set_pressure_value(double pressureVal, analogSensorInput *pressureInput)
{
	pressureInput->sensorValue = pressureVal;

}

void set_gps_value(double latVal, double longVal, double altVal, int qual, int sats, gpsSensorInput *gpsIn)
{
	gpsIn->latitude = latVal;
	gpsIn->longitude = longVal;
	gpsIn->altitude = altVal;
	gpsIn->quality = qual;
	gpsIn->satellitesInView = sats;

}

void set_accelerometer_value(double ax, double ay, double az, double gx, double gy, double gz, imuSensorInput* imuIn)
{
	imuIn->ax = ax;
	imuIn->ay = ay;
	imuIn->az = az;
	imuIn->gx = gx;
	imuIn->gy = gy;
	imuIn->gz = gz;

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