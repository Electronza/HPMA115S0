// HPMA115S0 dust sensor PM2.5 and PM10
// ---------------------
//
// By T.Costachioiu (blog@electronza.com)
// March 2019
//
// Documentation:
// Honeywell HPMA115S0 datasheet
// https://sensing.honeywell.com/HPMA115S0-particulate-matter-sensors

#ifndef hpma115s0_h
#define hpma115s0_h

#include "Arduino.h"

class HPMA115S0 {
	public:
		HPMA115S0(Stream& serial);
		bool read(float *p25, float *p10);
		bool stop_measurement();
		bool start_measurement();
		bool stop_autosend();
		bool enable_autosend();
	private:
		Stream& hpmport;
};

#endif
