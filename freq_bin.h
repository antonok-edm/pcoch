#ifndef FREQ_BIN_H
#define FREQ_BIN_H

#include <iostream>
#include <cmath>

class freq_bin {
	double freq;
	double k;
	double c;
	double vel;
	double q;
	double prev_vel;
	double n;		//amplitude normalizer
public:
	double pos;
	double amplitude;
	freq_bin(double f);
	void update(double signal);
	~freq_bin();
};

#endif
