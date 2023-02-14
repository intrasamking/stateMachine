#include "sensorStateFunctions.h"

struct analogSensorInput {
	sensorTypes sensor_type;
	sensorNames sensor_name;
	sensorStates currentState;
	double sensorValue;
};

analogIn *init()
{
	return malloc(sizeof(analogIn));
}

void initialize_pressure_sensor(analogIn *inst, enum sensorName sName)
{
	inst->sensor_type = pressure;
	inst->sensor_name = sName;
	inst->currentState = S_NOTACTIVE;
	inst->sensorValue = -1000;

	return;
}

void set_analog_value(analogIn *inst, double analogVal)
{
	inst->sensorValue = analogVal;
}

double get_analog_value(analogIn *inst)
{
	return inst->sensorValue;
}

int validate_pressure_reading(analogIn *inst)
{
	double sensorReading;
	int validity;
	sensorReading = inst->sensorValue;

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