#ifndef BRAKE_STATUS_h
#define BRAKE_STATUS_h

/**** State Definitions ****/
typedef enum {RGN_NOTAVAILABLE = 0, RGN_AVAILABLE = 1} regen_states;

typedef enum {AIR_NOTAVAILABLE = 0, AIR_REDUCED = 1, AIR_AVAILABLE = 2, AIR_OVERCHARGED = 3} air_states;

typedef enum { EMB_NOTAVAILABLE = 0, EMB_AVAILABLE = 1 } emergency_states;

typedef enum { temperature, pressure } sensor_types;

typedef enum { primary, secondary, tertiary } sensor_names;

typedef struct {
	double stateOfCharge;
	double maxDischarge;
	double maxCharge; 
} BMS_status;

typedef struct {
	regen_states regen_status;
	regen_states previous_regen_status;
} regenBrakeStatus;

typedef struct {
	air_states airbrake_status;
	air_states previous_airbrake_status;
} airBrakeStatus;

typedef struct {
	emergency_states emergencyBrake_status;
	emergency_states previous_emergencyBrake_status;
} emergencyBrakeStatus;

typedef struct {
	sensor_types sensor_type;
	sensor_names sensor_name;
	double sensorValue;
	int failure;
} analogSensorOutput;

extern analogSensorOutput * bpPressureOut, brakePipePressureOut; 
extern BMS_status* bmsPtr, bmsInfo;
extern regenBrakeStatus* regenSysPtr, regenSysStatus;
extern airBrakeStatus* airSysPtr, airSysStatus;
extern emergencyBrakeStatus* embSystPtr, embSysStatus;

void regenBrakeState(BMS_status*, regenBrakeStatus*);
void airBrakeState(analogSensorOutput*, airBrakeStatus*);
void emergencyBrakeState(analogSensorOutput*, emergencyBrakeStatus*);
 
#endif