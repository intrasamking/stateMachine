#include <stddef.h>
#include <stdio.h>            

#include "brakeStatusManager.h"

void regenBrakeState(BMS_status* bmsInfo, regenBrakeStatus* regenSysStatus)
{
	regen_states nextState;
	nextState = RGN_NOTAVAILABLE;

	regen_states currentState;
	currentState = regenSysStatus->regen_status;

	double SOC = bmsInfo->stateOfCharge;

	switch (currentState)
	{
	case RGN_AVAILABLE:
		if (SOC <= 0.9)
		{
			nextState = RGN_AVAILABLE;
		}
		else
		{
			nextState = RGN_NOTAVAILABLE;
		}
		break;
	default:
		if (SOC <= 0.9)
		{
			nextState = RGN_AVAILABLE;
		}
		else
		{
			nextState = RGN_NOTAVAILABLE;
		}
		break;
	}

	regenSysStatus->previous_regen_status = currentState;
	regenSysStatus->regen_status = nextState;
}

void airBrakeState(analogSensorOutput* pressureOutput, airBrakeStatus* airSysStatus)
{
	double currentPressure;
	currentPressure = pressureOutput->sensorValue;

	air_states currentState;
	air_states nextState;

	currentState = airSysStatus->airbrake_status;
	nextState = AIR_NOTAVAILABLE;

	switch (currentState)
	{
	case AIR_OVERCHARGED:
	{
		if (currentPressure <= 95)
		{
			nextState = AIR_AVAILABLE;
		}
		else
		{
			nextState = AIR_OVERCHARGED;
		}
	}
	case AIR_AVAILABLE:
	{
		if (currentPressure > 95)
		{
			nextState = AIR_OVERCHARGED;
		}
		else
		{
			nextState = AIR_REDUCED;
		}
	}
	case AIR_REDUCED:
	{
		if (currentPressure > 80)
		{
			nextState = AIR_AVAILABLE;
		}
		else
		{
			nextState = AIR_NOTAVAILABLE;
		}
	}
	//case AIR_NOTAVAILABLE:
	default:
	{
		if (currentPressure >= 60)
		{
			nextState = AIR_REDUCED;
		}
	}
	}

	airSysStatus->previous_airbrake_status = currentState;
	airSysStatus->airbrake_status = nextState;
}

void emergencyBrakeState(analogSensorOutput* pressureOutput, emergencyBrakeStatus* embSysStatus)
{
	double currentPressure;
	currentPressure = pressureOutput->sensorValue;

	emergency_states currentState;
	emergency_states nextState;

	currentState = embSysStatus->emergencyBrake_status;
	nextState = EMB_NOTAVAILABLE;

	switch (currentState)
	{
	case EMB_AVAILABLE:
	{
		if (currentPressure >= 60)
		{
			nextState = EMB_AVAILABLE;
		}
		else
		{
			nextState = EMB_NOTAVAILABLE;
		}
		break;
	default:
		if (currentPressure >= 60)
		{
			nextState = EMB_AVAILABLE;
		}
		else
		{
			nextState = EMB_NOTAVAILABLE;
		}
		break;
	}
	}

	embSysStatus->previous_emergencyBrake_status = currentState;
	embSysStatus->emergencyBrake_status = nextState;
}

