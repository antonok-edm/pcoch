#include "signal.h"

signal::signal() : level(0) {}

sin_wave::sin_wave(double f) : frequency(f) {}
void sin_wave::update(int t) {
	this->level = sin((double) t/REFRESH_HZ * frequency * 2 / PI);
}

file_wave::file_wave(std::string path) {
	struct stat buf;
	if(stat(path.c_str(), &buf)) {
		std::cout << "The specified path does not exist.\n";
		exit(1);
	}
	info.format = 0;
	SNDFILE *audioFile = sf_open(path.c_str(), SFM_READ, &info);
	if(sf_error(audioFile)) {
		std::cout << "The specified path is not a valid audio file.\n";
		exit(1);
	}
	data = new double[info.frames*info.channels];	//TODO: handle multiple channels properly
	sf_readf_double(audioFile, data, info.frames);
	sf_close(audioFile);
}
void file_wave::update(int t) {	//t is time in microseconds
	//std::cout << t << " " << (int)(t*info.samplerate/1000000)*info.channels << '\n';
	//std::cout << t << " " << (int)(info.samplerate/100*t/10000)*info.channels << '\n';
	level = data[(int)(info.samplerate/100*t/10000)*info.channels]; //TODO: finish this properly
}
file_wave::~file_wave() {
	delete[] data;
}
