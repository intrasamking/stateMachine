#ifndef RTW_HEADER_validate_h_
#define RTW_HEADER_validate_h_

#include "initializeSensors.h"

extern states validate_pressure_state(DW *, analogSensorInput *, analogSensorOutput *);
extern states validate_gps_state(gpsStorage *, gpsSensorInput *, gpsSensorOutput *);
extern states validate_imu_state(imuStorage *, imuSensorInput *, imuSensorOutput *);

extern void set_pressure_value(double pressureVal, analogSensorInput *);
extern void set_gps_value(double latVal, double longVal, double altVal, int qual, int sats, gpsSensorInput *);
extern void set_accelerometer_value(double ax, double ay, double az, double gx, double gy, double gz, imuSensorInput *);

extern int validate_pressure_reading(analogSensorInput *);
extern int validate_gps_reading(gpsSensorInput *);
extern int validate_imu_reading(imuSensorInput *);


#endif