#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sndfile.h>

#define PI 3.14159265358979

#ifndef REFRESH_HZ
#define REFRESH_HZ 100
#endif

class signal {
public:
	double level;
	signal();
	virtual void update(int t)=0;
};

class sin_wave : public signal {
public:
	double frequency;
	sin_wave(double f);
	void update(int t);
};

class file_wave : public signal {
	double* data;
	SF_INFO info;
public:
	file_wave(std::string path);
	void update(int t);
	~file_wave();
};

#endif
