#include "freq_bin.h"
#define PI 3.14159265358979

#include <cstdlib>

freq_bin::freq_bin(double f) :
	freq(f/**2/PI*/),
	k(pow(freq/**2/PI*/, 2)/20000),		//Resonant frequency is sqrt(k/m). m=1, so freq = sqrt(k), or k = freq^2.
	c(.995),
	vel(0),
	q(.0001),
	prev_vel(0),
	n(freq/2),
	pos(0),
	amplitude(0) {}

void freq_bin::update(double signal) {
	prev_vel = vel;
	vel = c*vel - k*pos + q*signal;
	pos = pos + vel;
	//vel = vel * c;		//Decay the motion of the spring by multiplying velocity by a damping constant c.
	//vel = vel - k*pos;		//Affect the spring's velocity by the spring force F = ma = -kx. Since m = 1, a = -kx = x". Velocity is decreased by kx.
	//vel = vel + q*signal;		//Affect the spring's velocity by the signal pressure
	//pos = pos + vel;		//Now, change the position of the spring by adding velocity.
	if((prev_vel > 0 && vel < 0) || (prev_vel < 0 && vel > 0)) {	//If the position is at a local min or max, use it as the new amplitude
		amplitude = 30*fabs(pos)*n;				//Multiply the amplitude by a normalizer to correct for decreasing amplitudes at higher frequencies
	}
}

freq_bin::~freq_bin() {}
