#include "validateSensors.h"
#include <math.h>
#include <stdio.h>

//DW *bpStorage, brakePipeStorage;
//analogSensorInput *bpPressureIn, brakePipePressureIn;
//analogSensorOutput *bpPressureOut, brakePipePressureOut;
//
//DW *resStorage, reservoirStorage;
//analogSensorInput *resPressureIn, reservoirPressureIn;
//analogSensorOutput *resPressureOut, reservoirPressureOut;
//
//gpsStorage *gpsStore1, gpsStorage1;
//gpsSensorInput *gpsIn1, gpsSensorIn1;
//gpsSensorOutput *gpsOut1, gpsSensorOut1;

struct analogSensorInput {
	sensor_types sensor_type;
	sensor_names sensor_name;
	states currentState;
	double sensorValue;
} ;

struct DW {
	double previous_signal;
	int previous_validity;
	int temporalCounter;
	int logSignals;
} ;

struct analogSensorOutput {
	sensor_types sensor_type;
	sensor_names sensor_name;
	double sensorValue;
	int failure;
} ;

analogIn *init()
{
	return malloc(sizeof(analogIn));
}

analogOut *initOut()
{
	return malloc(sizeof(analogOut));
}

analogStorage *initSt()
{
	return malloc(sizeof(analogStorage));
}

//sensorPointers initialize_sensors(analogIn inputSensor, analogOut outputSensor, analogStorage storageSensor)
//{
//	//int bp_init;
//	//int res_init;
//	//int gps_init;
//
//
//	//DW brakePipeStorage = { .temporalCounter = 0 };
//	//DW *bpStorage = &brakePipeStorage;
//	//analogSensorInput *bpPressureIn, brakePipePressureIn = { .sensor_name = primary };
//	//bpPressureIn = &brakePipePressureIn;
//	//analogSensorOutput *bpPressureOut, brakePipePressureOut = { .sensor_name = primary };
//	//bpPressureOut = &brakePipePressureOut;
//
//	//DW *resStorage, reservoirStorage = { .temporalCounter = 0 };
//	//resStorage = &reservoirStorage;
//	//analogSensorInput *resPressureIn, reservoirPressureIn = { .sensor_name = primary };
//	//resPressureIn = &reservoirPressureIn;
//	//analogSensorOutput *resPressureOut, reservoirPressureOut = { .sensor_name = primary };
//	//resPressureOut = &reservoirPressureOut;
//
//	//gpsStorage *gpsStore1, gpsStorage1 = { .temporalCounter = 0 };
//	//gpsStore1 = &gpsStorage1;
//	//gpsSensorInput *gpsIn1, gpsSensorIn1 = { .sensor_name = primary };
//	//gpsIn1 = &gpsSensorIn1;
//	//gpsSensorOutput *gpsOut1, gpsSensorOutput1 = { .sensor_name = primary };
//	//gpsOut1 = &gpsSensorOutput1;
//
//	//bp_init = initialize_pressure_sensor(bpStorage, bpPressureIn, bpPressureOut);
//	//res_init = initialize_pressure_sensor(resStorage, resPressureIn, resPressureOut);
//	//gps_init = initialize_gps_sensor(gpsStore1, gpsIn1, gpsOut1);
//
//	//sensorPtrs.bpPresIn = bpPressureIn;
//	//sensorPtrs.bpPresOut = bpPressureOut;
//	//sensorPtrs.bpStore = bpStorage;
//	//sensorPtrs.resPresIn = resPressureIn;
//	//sensorPtrs.resPresOut = resPressureOut;
//	//sensorPtrs.resStore = resStorage;
//	//sensorPtrs.gpsIn1 = gpsIn1;
//	//sensorPtrs.gpsOut1 = gpsOut1;
//	//sensorPtrs.gpsStore = gpsStore1;

	//sensorPointers sensorPtrs;

	//sensorPtrs.inputSensor = initialize_pressure_sensorIn(primary, inputSensor);
	//sensorPtrs.outputSensor = initialize_pressure_sensorOut(sensorPtrs.inputSensor);
	//sensorPtrs.storage = initialize_pressure_sensorStore(sensorPtrs.inputSensor);

	//return sensorPtrs;
//}

//states validate_pressure_state(analogStorage sensorValidateStorage, analogIn pressureInput, analogOut pressureOutput)
//{
//	int validity;
//	stateEvents currentEvent;
//	states nextState;
//
//	currentEvent = E_doNothing;
//	nextState = S_NOTACTIVE;
//
//	if (get_analog_value(pressureInput) == 0)
//	{
//		return S_NOTCONNECTED;
//	}
//
//	sensorValidateStorage->previous_signal = pressureInput->sensorValue;
//
//	validity = validate_pressure_reading(pressureInput);
//
//	if (validity != sensorValidateStorage->previous_validity)
//	{
//		switch (pressureInput->currentState)
//		{
//		case S_NOTACTIVE:
//			currentEvent = E_goActive;
//			nextState = S_ACTIVE;
//			break;
//		case S_BUFFERING:
//			currentEvent = E_goActive;
//			nextState = S_ACTIVE;
//			break;
//			//case S_ACTIVE:
//		default:
//			currentEvent = E_goBuffer;
//			nextState = S_BUFFERING;
//			break;
//		}
//	}
//	else
//	{
//		switch (pressureInput->currentState)
//		{
//		case S_ACTIVE:
//			currentEvent = E_doNothing;
//			nextState = S_ACTIVE;
//			break;
//		case S_BUFFERING:
//			if (sensorValidateStorage->temporalCounter > 20)
//			{
//				currentEvent = E_goPassive;
//				//nextState = S_NOTACTIVE;
//				//pressureOutput->sensorValue = -1;
//				//pressureOutput->failure = 1;
//				sensorValidateStorage->temporalCounter = 0;
//			}
//			else
//			{
//				currentEvent = E_doNothing;
//				nextState = S_BUFFERING;
//				//pressureOutput->sensorValue = sensorValidateStorage->previous_signal;
//				//pressureOutput->failure = 1;
//				sensorValidateStorage->temporalCounter++;
//			}
//			break;
//		default:
//			currentEvent = E_doNothing;
//			nextState = S_NOTACTIVE;
//		}
//
//	}
//
//	if ((pressureInput->currentState = S_BUFFERING) && (nextState != S_BUFFERING))
//	{
//		sensorValidateStorage->temporalCounter = 0;
//	}
//
//	switch (nextState)
//	{
//	case S_ACTIVE:
//		pressureInput->currentState = S_ACTIVE;
//		sensorValidateStorage->logSignals = 1;
//		pressureOutput->sensorValue = pressureInput->sensorValue;
//		pressureOutput->failure = 0;
//		break;
//	case S_BUFFERING:
//		pressureInput->currentState = S_BUFFERING;
//		sensorValidateStorage->logSignals = 1;
//		pressureOutput->sensorValue = sensorValidateStorage->previous_signal;
//		pressureOutput->failure = 1;
//		sensorValidateStorage->temporalCounter++;
//		break;
//		//case S_NOTACTIVE:
//	default:
//		pressureInput->currentState = S_NOTACTIVE;
//		sensorValidateStorage->logSignals = 0;
//		pressureOutput->sensorValue = -1;
//		pressureOutput->failure = 1;
//		break;
//	}
//
//	sensorValidateStorage->previous_validity = validity;
//	switch (pressureInput->sensor_type)
//	{
//	case pressure:
//		printf("Brakepipe \n");
//		break;
//	case temperature:
//		printf("Reservoir \n");
//		break;
//	default:
//		printf("Wrong \n");
//		break;
//	}
//
//	printf("%d \n", nextState);
//	if (sensorValidateStorage->logSignals)
//	{
//		//Send signals to tablet
//	}
//
//	states returnVal;
//	returnVal = pressureInput->currentState;
//	return returnVal;
//}

//states validate_gps_state(gpsStorage *gpsBuffer, gpsSensorInput *gpsSensorIn, gpsSensorOutput *gpsSensorOut)
//{
//	int validity;
//	stateEvents currentEvent;
//	states nextState;
//
//	currentEvent = E_doNothing;
//	nextState = S_NOTACTIVE;
//		
//	validity = validate_gps_reading(gpsSensorIn);
//
//	if (validity != gpsBuffer->previous_validity)
//	{
//		switch (gpsSensorIn->currentState)
//		{
//		case S_NOTACTIVE:
//			nextState = S_ACTIVE;
//			break;
//		case S_BUFFERING:
//			nextState = S_ACTIVE;
//			break;
//		//case S_ACTIVE:
//		default:
//			nextState = S_BUFFERING;
//			break;
//		}
//	}
//	else
//	{
//		switch (gpsSensorIn->currentState)
//		{
//		case S_ACTIVE:
//			nextState = S_ACTIVE;
//			break;
//		case S_BUFFERING:
//			if (gpsBuffer->temporalCounter > 20)
//			{
//				nextState = S_NOTACTIVE;
//				gpsBuffer->temporalCounter = 0;
//			}
//			else
//			{
//				nextState = S_BUFFERING;
//				gpsBuffer->temporalCounter++;
//			}
//			break;
//		default:
//			nextState = S_NOTACTIVE;
//			break;
//		}
//
//	}
//
//	if ((gpsSensorIn->currentState = S_BUFFERING) && (nextState != S_BUFFERING))
//	{
//		gpsBuffer->temporalCounter = 0;
//	}
//
//	switch (nextState)
//	{
//	case S_ACTIVE:
//		gpsSensorIn->currentState = S_ACTIVE;
//		gpsBuffer->logSignals = 1;
//		gpsSensorOut->latitude = gpsSensorIn->latitude;
//		gpsSensorOut->longitude = gpsSensorIn->longitude;
//		gpsSensorOut->altitude = gpsSensorIn->altitude;
//		gpsSensorOut->failure = 0;
//
//		gpsBuffer->previousLat = gpsSensorIn->latitude;
//		gpsBuffer->previousLong = gpsSensorIn->longitude;
//		gpsBuffer->previousAlt = gpsSensorIn->altitude;
//
//		break;
//	case S_BUFFERING:
//		gpsSensorIn->currentState = S_BUFFERING;
//		gpsBuffer->logSignals = 1;
//		gpsSensorOut->latitude = gpsBuffer->previousLat;
//		gpsSensorOut->longitude = gpsBuffer->previousLong;
//		gpsSensorOut->altitude = gpsBuffer->previousAlt;
//		gpsSensorOut->failure = 1;
//		gpsBuffer->temporalCounter++;
//		break;
//		//case S_NOTACTIVE:
//	default:
//		gpsSensorIn->currentState = S_NOTACTIVE;
//		gpsBuffer->logSignals = 0;
//		gpsSensorOut->latitude = 0;
//		gpsSensorOut->longitude = 0;
//		gpsSensorOut->altitude = 0;
//		gpsSensorOut->failure = 1;
//
//		gpsBuffer->previousLat = gpsSensorIn->latitude;
//		gpsBuffer->previousLong = gpsSensorIn->longitude;
//		gpsBuffer->previousAlt = gpsSensorIn->altitude;
//
//		break;
//
//	}
//	gpsBuffer->previous_validity = validity;
//
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
//
//	states returnVal;
//	returnVal = gpsSensorIn->currentState;
//	return returnVal;
//
//}

void set_analog_value(analogIn *pressureInput, double analogVal)
{
	pressureInput->sensorValue = analogVal;
	return;
}

//void set_gps_value(double latVal, double longVal, double altVal, int qual, int sats, gpsSensorInput *gpsIn)
//{
//	gpsIn->latitude = latVal;
//	gpsIn->longitude = longVal;
//	gpsIn->altitude = altVal;
//	gpsIn->quality = qual;
//	gpsIn->satellitesInView = sats;
//
//}

//void set_accelerometer_value(double ax, double ay, double az, double gx, double gy, double gz, imuSensorInput* imuIn)
//{
//	imuIn->ax = ax;
//	imuIn->ay = ay;
//	imuIn->az = az;
//	imuIn->gx = gx;
//	imuIn->gy = gy;
//	imuIn->gz = gz;
//
//}

double get_analog_value(analogIn pressureInput)
{
	if (pressureInput->sensorValue < -900)
	{
		return pressureInput->sensorValue;
	}
	else
	{
		return 1;
	}
}

int validate_pressure_reading(analogIn *pressureInput)
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

//int validate_gps_reading(gpsSensorInput* gpsInput)
//{
//	int SIV;
//	int validity;
//	SIV = gpsInput->satellitesInView;
//	if (SIV >= 4)
//	{
//		validity = 1;
//	}
//	else
//	{
//		validity = 0;
//	}
//
//	return validity;
//}

//int validate_imu_reading(imuSensorInput* imuInput)
//{
//	int validity;
//
//	if ((fabs(imuInput->ax) > 78.48) || (fabs(imuInput->ay) > 78.48) || (fabs(imuInput->az) > 78.48))
//	{
//		validity = 0;
//	}
//	else if ((fabs(imuInput->ax) > 245) || (fabs(imuInput->ay) > 245) || (fabs(imuInput->az) > 245))
//	{
//		validity = 0;
//	}
//	else
//	{
//		validity = 1;
//	}
//
//	return validity;
//}

void initialize_pressure_sensorIn(analogIn *inst, enum sensor_name sName)
{

	inst->sensor_type = pressure;
	inst->sensor_name = sName; 
	inst->currentState = S_NOTACTIVE;
	inst->sensorValue = -1000;

	//return inst;
}
//
//analogOut initialize_pressure_sensorOut(analogIn inMatch, analogOut inst)
//{
//	inst->sensor_type = inMatch->sensor_type;
//	inst->sensor_name = inMatch->sensor_name;
//	inst->failure = 1;
//	
//	return inst;
//}
//
//analogStorage initialize_pressure_sensorStore(analogIn inMatch, analogStorage inst)
//{
//	inst->previous_signal = 0;
//	inst->previous_validity = 0;
//	inst->logSignals = 0;
//
//	return inst;
//}

//int initialize_temperature_sensor(DW *pressureStorage, analogSensorInput *pressureSensorIn, analogSensorOutput *pressureSensorOut)
//{
//
//	pressureSensorIn->sensor_type = temperature;
//	pressureSensorIn->currentState = S_NOTACTIVE;
//	pressureSensorIn->sensorValue = -1000;
//
//	pressureSensorOut->sensor_name = primary;
//	pressureSensorOut->sensor_type = pressure;
//	pressureSensorOut->failure = 1;
//
//	pressureStorage->previous_signal = 0;
//	pressureStorage->previous_validity = 0;
//	pressureStorage->logSignals = 0;
//	return 1;
//
//
//}

//int initialize_gps_sensor(gpsStorage *gpsStore, gpsSensorInput *gpsSensorIn, gpsSensorOutput *gpsSensorOut)
//{
//	gpsSensorIn->currentState = S_NOTACTIVE;
//	gpsSensorIn->latitude = 0;
//	gpsSensorIn->longitude = 0;
//	gpsSensorIn->altitude = 0;
//	gpsSensorIn->quality = 0;
//	gpsSensorIn->satellitesInView = 0;
//	gpsSensorIn->validity = 0;
//
//	gpsSensorOut->latitude = 0;
//	gpsSensorOut->longitude = 0;
//	gpsSensorOut->altitude = 0;
//	gpsSensorOut->quality = 0;
//	gpsSensorOut->satellitesInView = 0;
//	gpsSensorOut->failure = 1;
//
//	gpsStore->previousAlt = 0;
//	gpsStore->previousLat = 0;
//	gpsStore->previousLong = 0;
//	gpsStore->previous_validity = 0;
//	gpsStore->logSignals = 0;
//
//	return 1;
//
//
//}

//int initialize_accelerometer_sensor(imuStorage *imuStore, imuSensorInput *imuSensorIn, imuSensorOutput *imuSensorOut)
//{
//	imuSensorIn->currentState = S_NOTACTIVE;
//	imuSensorIn->ax = 0;
//	imuSensorIn->ay = 0;
//	imuSensorIn->az = 0;
//	imuSensorIn->gx = 0;
//	imuSensorIn->gy = 0;
//	imuSensorIn->gz = 0;
//	imuSensorIn->validity = 0;
//
//	imuSensorOut->ax = 0;
//	imuSensorOut->ay = 0;
//	imuSensorOut->az = 0;
//	imuSensorOut->gx = 0;
//	imuSensorOut->gy = 0;
//	imuSensorOut->gz = 0;
//	imuSensorOut->failure = 0;
//
//	imuStore->previous_ax = 0;
//	imuStore->previous_ay = 0;
//	imuStore->previous_az = 0;
//	imuStore->previous_gx = 0;
//	imuStore->previous_gy = 0;
//	imuStore->previous_gz = 0;
//	imuStore->logSignals = 0;
//	imuStore->temporalCounter = 0;
//	imuStore->previous_validity = 0;
//
//	return 1;
//
//}
