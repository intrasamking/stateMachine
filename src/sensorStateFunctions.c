#include <stdio.h>
#include "sensorStateFunctions.h"

analogSensorInput brakePipeSensor;
analogStorage brakePipeStorage;

analogSensorInput reservoirSensor;
analogStorage reservoirStorage;

gpsStorage gpsStorageFront;
gpsStorage gpsStorageRear;

gpsSensorInput gpsSensorFront;
gpsSensorInput gpsSensorRear;

imuStorage imuStorageFront;
imuStorage imuStorageRear;

imuSensorInput imuSensorFront;
imuSensorInput imuSensorRr;

void initializeAnalogSensor(analogSensorInput * analogIn, analogStorage * analogStore, sensorTypes sType, sensorNames sName)
{
	initializeAnalogMemory(analogStore);

	analogIn->sensor_name = sName;
	analogIn->sensor_type = sType;
	analogIn->validity = notValid;
	analogIn->sensorValue = -1000;
	analogIn->currentState = S_NOTACTIVE;
	analogIn->sensor_store = analogStore;

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

void initializeGPSsensor(gpsSensorInput *gpsSensorIn, gpsStorage *gpsStore, sensorNames sName)
{
	initializeGPSmemory(gpsStore);

	gpsSensorIn->sensor_name = sName;
	gpsSensorIn->currentState = S_NOTACTIVE;
	gpsSensorIn->latitude = 0;
	gpsSensorIn->longitude = 0;
	gpsSensorIn->altitude = 0;
	gpsSensorIn->quality = 0;
	gpsSensorIn->satellitesInView = -1000;
	gpsSensorIn->validity = notValid;
	gpsSensorIn->gps_store = gpsStore;

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

void initializeIMUsensor(imuSensorInput * imuSensorIn, imuStorage * imuStore, sensorNames sName)
{

	initializeIMUmemory(imuStore);

	imuSensorIn->currentState = S_NOTACTIVE;
	imuSensorIn->ax = 0;
	imuSensorIn->ay = 0;
	imuSensorIn->az = 0;
	imuSensorIn->gx = 0;
	imuSensorIn->gy = 0;
	imuSensorIn->gz = 0;
	imuSensorIn->validity = notValid;
	imuSensorIn->imu_store = imuStore;

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

void setAnalogValue(analogSensorInput *analogIn, double sensorVal)
{
	analogIn->sensorValue = sensorVal;
}

void setGPSvalue(gpsSensorInput *gpsIn, double latVal, double longVal, double altVal, int qualVal, int SIV)
{
	gpsIn->latitude = latVal;
	gpsIn->longitude = longVal;
	gpsIn->altitude = altVal;
	gpsIn->quality = qualVal;
	gpsIn->satellitesInView = SIV;
}

void setIMUvalue(imuSensorInput *imuIn, double axVal, double ayVal, double azVal, double gxVal, double gyVal, double gzVal)
{
	imuIn->ax = axVal;
	imuIn->ay = ayVal;
	imuIn->az = azVal;
	imuIn->gx = gxVal;
	imuIn->gy = gyVal;
	imuIn->gz = gzVal;

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