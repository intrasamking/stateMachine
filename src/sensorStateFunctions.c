#include <stdio.h>
#include "sensorStateFunctions.h"

analogSensorInput brakePipeSensorIn;
analogStorage brakePipeStorage;
analogSensorOutput brakePipeSensorOut;

analogSensorInput reservoirSensorIn;
analogStorage reservoirStorage;
analogSensorOutput reservoirSensorOut;

gpsStorage gpsStorageFr;
gpsStorage gpsStorageRr;

gpsSensorInput gpsSensorFrIn;
gpsSensorInput gpsSensorRrIn;

gpsSensorOutput gpsSensorFrOut;
gpsSensorOutput gpsSensorRrOut;

imuStorage imuStorageFr;
imuStorage imuStorageRr;

imuSensorInput imuSensorFrIn;
imuSensorInput imuSensorRrIn;

imuSensorOutput imuSensorFrOut;
imuSensorOutput imuSensorRrOut;

analogSensorOutput analogSensorValidation(analogSensorInput *sensorInput)
{
	enum validityStates validity;
	validity = notValid;
	sensorInput->sensor_store->previous_signal = sensorInput->sensorValue;

	if (sensorInput->sensor_type == pressure)
		validity = validatePressureReading(sensorInput);
	else if (sensorInput->sensor_type == temperature)
	{
		validity = validateTemperatureReading(sensorInput);
	}

	sensorStates nextState = S_NOTACTIVE;

	if (validity != sensorInput->sensor_store->previous_validity)
	{
		switch (sensorInput->currentState)
		{
			case S_NOTACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					nextState = S_ACTIVE;
					break;
				}
			default:
				{
					nextState = S_BUFFERING;
					break;
				}
		}
	}
	else
	{
		switch (sensorInput->currentState)
		{
			case S_ACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					if (sensorInput->sensor_store->temporalCounter > 20)
					{
						nextState = S_NOTACTIVE;
						sensorInput->sensor_store->temporalCounter = 0;
						break;
					}
					else
					{
						nextState = S_BUFFERING;
						sensorInput->sensor_store->temporalCounter++;
						break;
					}
				}
			default:
				nextState = S_NOTACTIVE;
				break;
		}
	}

	switch (nextState)
	{
		case S_ACTIVE:
			{
				sensorInput->currentState = S_ACTIVE;
				sensorInput->sensor_store->logSignals = 1;
				sensorInput->sensor_out->sensorVal = sensorInput->sensorValue;
				sensorInput->sensor_out->failure = 0;
				break;
			}
		case S_BUFFERING:
			{
				sensorInput->currentState = S_BUFFERING;
				sensorInput->sensor_store->logSignals = 1;
				sensorInput->sensor_out->sensorVal = sensorInput->sensor_out->sensorVal;
				sensorInput->sensor_out->failure = 1;
				sensorInput->sensor_store->temporalCounter++;
				break;
			}
		default:
			{
				sensorInput->currentState = S_NOTACTIVE;
				sensorInput->sensor_store->logSignals = 0;
				sensorInput->sensor_out->sensorVal = -1000;
				sensorInput->sensor_out->failure = 1;
				break;
			}
	}

	sensorInput->sensor_store->previous_validity = validity;

	analogSensorOutput returnVal;
	returnVal = getAnalogValueOutput(sensorInput-> sensor_out);
	return returnVal;

}

gpsSensorOutput gpsSensorValidation(gpsSensorInput *gpsInput)
{
	enum validityStates validity;
	validity = notValid;

	gpsInput->gps_store->previousLat = gpsInput->latitude;
	gpsInput->gps_store->previousLong = gpsInput->longitude;
	gpsInput->gps_store->previousAlt = gpsInput->altitude;
	gpsInput->gps_store->previousVx = gpsInput->vx;
	gpsInput->gps_store->previousVy = gpsInput->vy;

	validity = validateGPSreading(gpsInput);

	sensorStates nextState = S_NOTACTIVE;

	if (validity != gpsInput->gps_store->previous_validity)
	{
		switch (gpsInput->currentState)
		{
			case S_NOTACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					nextState = S_ACTIVE;
					break;
				}
			default:
				{
					nextState = S_BUFFERING;
					break;
				}
		}
	}
	else
	{
		switch (gpsInput->currentState)
		{
			case S_ACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					if (gpsInput->gps_store->temporalCounter > 20)
					{
						nextState = S_NOTACTIVE;
						gpsInput->gps_store->temporalCounter = 0;
						break;
					}
					else
					{
						nextState = S_BUFFERING;
						gpsInput->gps_store->temporalCounter++;
						break;
					}
				}
			default:
				nextState = S_NOTACTIVE;
				break;
		}
	}

	switch (nextState)
	{
		case S_ACTIVE:
			{
				gpsInput->currentState = S_ACTIVE;
				gpsInput->gps_store->logSignals = 1;
				gpsInput->gps_out->latitude = gpsInput->latitude;
				gpsInput->gps_out->longitude = gpsInput->longitude;
				gpsInput->gps_out->altitude = gpsInput->altitude;
				gpsInput->gps_out->vx = gpsInput->vx;
				gpsInput->gps_out->vy = gpsInput->vy;
				gpsInput->gps_out->failure = 0;
				break;
			}
		case S_BUFFERING:
			{
				gpsInput->currentState = S_BUFFERING;
				gpsInput->gps_store->logSignals = 1;
				gpsInput->gps_out->latitude = gpsInput->gps_out->latitude;
				gpsInput->gps_out->longitude = gpsInput->gps_out->longitude;
				gpsInput->gps_out->altitude = gpsInput->gps_out->altitude;
				gpsInput->gps_out->vx = gpsInput->gps_out->vx;
				gpsInput->gps_out->vy = gpsInput->gps_out->vy;
				gpsInput->gps_out->failure = 1;
				gpsInput->gps_store->temporalCounter++;
				break;
			}
		default:
			{
				gpsInput->currentState = S_NOTACTIVE;
				gpsInput->gps_store->logSignals = 0;
				gpsInput->gps_out->latitude = 0;
				gpsInput->gps_out->longitude = 0;
				gpsInput->gps_out->altitude = 0;
				gpsInput->gps_out->vx = 0;
				gpsInput->gps_out->vy = 0;
				gpsInput->gps_out->failure = 1;
				break;
			}
	}

	gpsInput->gps_store->previous_validity = validity;

	gpsSensorOutput returnVal;
	returnVal = getGPSvalueOutput(gpsInput->gps_out);
	return returnVal;
}

imuSensorOutput imuSensorValidation(imuSensorInput *imuInput)
{
	enum validityStates validity;
	validity = notValid;
	
	imuInput->imu_store->previous_ax = imuInput->ax;
	imuInput->imu_store->previous_ay = imuInput->ay;
	imuInput->imu_store->previous_az = imuInput->az;
	imuInput->imu_store->previous_gx = imuInput->gx;
	imuInput->imu_store->previous_gy = imuInput->gy;
	imuInput->imu_store->previous_gz = imuInput->gz;

	validity = validateIMUreading(imuInput);

	sensorStates nextState = S_NOTACTIVE;

	if (validity != imuInput->imu_store->previous_validity)
	{
		switch (imuInput->currentState)
		{
			case S_NOTACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					nextState = S_ACTIVE;
					break;
				}
			default:
				{
					nextState = S_BUFFERING;
					break;
				}
		}
	}
	else
	{
		switch (imuInput->currentState)
		{
			case S_ACTIVE:
				{
					nextState = S_ACTIVE;
					break;
				}
			case S_BUFFERING:
				{
					if (imuInput->imu_store->temporalCounter > 20)
					{
						nextState = S_NOTACTIVE;
						imuInput->imu_store->temporalCounter = 0;
						break;
					}
					else
					{
						nextState = S_BUFFERING;
						imuInput->imu_store->temporalCounter++;
						break;
					}
				}
			default:
				nextState = S_NOTACTIVE;
				break;
		}
	}

	switch (nextState)
	{
		case S_ACTIVE:
			{
				imuInput->currentState = S_ACTIVE;
				imuInput->imu_store->logSignals = 1;
				imuInput->imu_out->ax = imuInput->ax;
				imuInput->imu_out->ay = imuInput->ay;
				imuInput->imu_out->az = imuInput->az;
				imuInput->imu_out->gx = imuInput->gx;
				imuInput->imu_out->gy = imuInput->gy;
				imuInput->imu_out->gz = imuInput->gz;
				imuInput->imu_out->failure = 0;
				break;
			}
		case S_BUFFERING:
			{
				imuInput->currentState = S_BUFFERING;
				imuInput->imu_store->logSignals = 1;
				imuInput->imu_out->ax = imuInput->imu_out->ax;
				imuInput->imu_out->ay = imuInput->imu_out->ay;
				imuInput->imu_out->az = imuInput->imu_out->az;
				imuInput->imu_out->gx = imuInput->imu_out->gx;
				imuInput->imu_out->gy = imuInput->imu_out->gy;
				imuInput->imu_out->gz = imuInput->imu_out->gz;
				imuInput->imu_out->failure = 1;
				imuInput->imu_store->temporalCounter++;
				break;
			}
		default:
			{
				imuInput->currentState = S_NOTACTIVE;
				imuInput->imu_store->logSignals = 0;
				imuInput->imu_out->ax = 0;
				imuInput->imu_out->ay = 0;
				imuInput->imu_out->az = 0;
				imuInput->imu_out->gx = 0;
				imuInput->imu_out->gy = 0;
				imuInput->imu_out->gz = 0;
				imuInput->imu_out->failure = 1;
				break;
			}
	}

	imuInput->imu_store->previous_validity = validity;

	imuSensorOutput returnVal;
	returnVal = getIMUvalueOutput(imuInput->imu_out);
	return returnVal;
}
void initializeAnalogSensor(analogSensorInput * analogIn, analogStorage * analogStore, analogSensorOutput *analogOut, sensorTypes sType, sensorNames sName)
{
	initializeAnalogMemory(analogStore);
	initializeAnalogOutput(analogOut);

	analogIn->sensor_name = sName;
	analogIn->sensor_type = sType;
	analogIn->validity = notValid;
	analogIn->sensorValue = -1000;
	analogIn->currentState = S_NOTACTIVE;
	analogIn->sensor_store = analogStore;
	analogIn->sensor_out = analogOut;
	return;

}

void initializeAnalogMemory(analogStorage *storeIn)
{
	storeIn->previous_signal = 0;
	storeIn->previous_validity = notValid;
	storeIn->temporalCounter = 0;
	storeIn->logSignals = 0;

	return;
}

void initializeAnalogOutput(analogSensorOutput *analogOut)
{
	analogOut->sensorVal = -1000;
	analogOut->state = S_NOTACTIVE;
	analogOut->failure = 1;
}


void initializeGPSsensor(gpsSensorInput *gpsSensorIn, gpsStorage *gpsStore, gpsSensorOutput *gpsOut, sensorNames sName)
{
	initializeGPSmemory(gpsStore);
	initializeGPSoutput(gpsOut);

	gpsSensorIn->sensor_name = sName;
	gpsSensorIn->currentState = S_NOTACTIVE;
	gpsSensorIn->latitude = 0;
	gpsSensorIn->longitude = 0;
	gpsSensorIn->altitude = 0;
	gpsSensorIn->quality = 0;
	gpsSensorIn->satellitesInView = -1000;
	gpsSensorIn->validity = notValid;
	gpsSensorIn->gps_store = gpsStore;
	gpsSensorIn->gps_out = gpsOut;
	return;
}

void initalizeGPSmemory(gpsStorage *gpsStore)
{
	gpsStore->previousLat = 0;
	gpsStore->previousLong = 0;
	gpsStore->previousAlt = 0;
	gpsStore->previous_validity = notValid;
	gpsStore->temporalCounter = 0;
	gpsStore->logSignals = 0;

	return;
}

void initializeGPSoutput(gpsSensorOutput *gpsOut)
{
	gpsOut->latitude = 0;
	gpsOut->longitude = 0;
	gpsOut->altitude = 0;
	gpsOut->state = notValid;
	gpsOut->vx = 0;
	gpsOut->vy = 0;
	gpsOut->failure = 1;
}

void initializeIMUsensor(imuSensorInput * imuSensorIn, imuStorage * imuStore, imuSensorOutput *imuOut, sensorNames sName)
{

	initializeIMUmemory(imuStore);
	initializeIMUoutput(imuOut);

	imuSensorIn->currentState = S_NOTACTIVE;
	imuSensorIn->ax = 0;
	imuSensorIn->ay = 0;
	imuSensorIn->az = 0;
	imuSensorIn->gx = 0;
	imuSensorIn->gy = 0;
	imuSensorIn->gz = 0;
	imuSensorIn->validity = notValid;
	imuSensorIn->imu_store = imuStore;
	imuSensorIn->imu_out = imuOut;
	return;

}

void initializeIMUmemory(imuStorage *imuStore)
{
	imuStore->previous_ax = 0;
	imuStore->previous_ay = 0;
	imuStore->previous_az = 0;
	imuStore->previous_gx = 0;
	imuStore->previous_gy = 0;
	imuStore->previous_gz = 0;
	imuStore->logSignals = 0;
	imuStore->temporalCounter = 0;
	imuStore->previous_validity = notValid;

	return;
}

void initializeIMUoutput(imuSensorOutput *imuOut)
{
	imuOut->ax = 0;
	imuOut->ay = 0;
	imuOut->az = 0;
	imuOut->gx = 0;
	imuOut->gy = 0;
	imuOut->gz = 0;
	imuOut->failure = 1;
}

void setAnalogValue(analogSensorInput *analogIn, double sensorVal)
{
	analogIn->sensorValue = sensorVal;
}

void setGPSvalue(gpsSensorInput *gpsIn, gpsMessage *gpsMsg)
{
	gpsIn->latitude = gpsMsg->latitude;
	gpsIn->longitude = gpsMsg->longitude;
	gpsIn->altitude = gpsMsg->altitude;
	gpsIn->quality = gpsMsg->quality;
	gpsIn->satellitesInView = gpsMsg->satellitesInView;
}

void setIMUvalue(imuSensorInput *imuIn, imuMessage *imuMsg)
{
	imuIn->ax = imuMsg->ax;
	imuIn->ay = imuMsg->ay;
	imuIn->az = imuMsg->az;
	imuIn->gx = imuMsg->gx;
	imuIn->gy = imuMsg->gy;
	imuIn->gz = imuMsg->gz;
	return;
}

analogSensorOutput getAnalogValueOutput(analogSensorOutput *analogOut)
{
	analogSensorOutput returnVal;
	returnVal.failure = analogOut->failure;
	returnVal.sensorVal = analogOut->sensorVal;
	returnVal.state = analogOut->state;

	return returnVal;
}

gpsSensorOutput getGPSvalueOutput(gpsSensorOutput *gpsOut)
{
	gpsSensorOutput returnVal;
	returnVal.latitude = gpsOut->latitude;
	returnVal.longitude = gpsOut->longitude;
	returnVal.altitude = gpsOut->altitude;
	returnVal.state = gpsOut->state;
	returnVal.vx = gpsOut->vx;
	returnVal.vy = gpsOut->vy;

	return returnVal;
}

imuSensorOutput getIMUvalueOutput(imuSensorOutput *imuOut)
{
	imuSensorOutput returnVal;

	returnVal.ax = imuOut->ax;
	returnVal.ay = imuOut->ay;
	returnVal.az = imuOut->az;
	returnVal.gx = imuOut->gx;
	returnVal.gy = imuOut->gy;
	returnVal.gz = imuOut->gz;

	return returnVal;
}

enum validityStates validatePressureReading(analogSensorInput *analogIn)
{
	double sensorVal = analogIn->sensorValue;

	if (sensorVal == -1000)
	{
		return noConnect;
	}
	else if ((sensorVal < 160) && (sensorVal > 0))
	{
		return Valid;
	}
	else
	{
		return notValid;
	}
}

enum validityStates validateGPSreading(gpsSensorInput *gpsIn)
{
	int SIV = gpsIn->satellitesInView;

	if (SIV == -1000)
	{
		return noConnect;
	}
	else if (SIV >= 4)
	{
		return Valid;
	}
	else
	{
		return notValid;
	}
}

enum validityStates validateIMUreading(imuSensorInput *imuIn)
{
	
	double ax = imuIn->ax;
	double ay = imuIn->ay;
	double az = imuIn->az;
	double gx = imuIn->gx;
	double gy = imuIn->gy;
	double gz = imuIn->gz;

	if ((ax == -1000) || (ay == -1000) || (az == -1000))
	{
		return noConnect;
	}
	else if ((fabs(ax) > 78.48) || (fabs(ay) > 78.48) || (fabs(az) > 78.48))
	{
		return notValid;
	}
	else if ((fabs(gx) > 245) || (fabs(gy) > 245) || (fabs(gz) > 245))
	{
		return notValid;
	}
	else
	{
		return Valid;
	}
}