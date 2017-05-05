#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sndfile.h>
#include "freq_bin.h"
#include "signal.h"

#define PI 3.14159265358979

#define REFRESH_HZ 100

void show(double signal, int width) {
	std::cout << '/';
	for(int i = 0; i < width-2; i++) {
		if(fabs(width/2*signal+width/2 - i) < .5) std::cout << '#';
		else if(i == width/2) std::cout << '|';
		else std::cout << ' ';
	}
	std::cout << '\\';
}

void compare(freq_bin **bins, int binc, int width) {
	std::cout << '/';
	for(int i = 0; i < width-2; i++) {
		char out = ' ';
		if(i == width/2) out = '|';
		for(int c = binc - 1; c >= 0; c--) {
			if(fabs(width/2*bins[c]->pos/4 + width/2 - i) < .5) out = 'A' + c;
		}
		std::cout << out;
	}
	std::cout << '\\';
}

void spec(freq_bin **bins, int binc, int width, int height) {
	std::string line;
	for(int y = height-1; y > 0; y--) {
		line = "";
		for(int x = 0; x < binc; x++) {
			if(x%(12*3) == 0) line = line + "|";
			if(height*bins[x]->amplitude/200 >= y) line = line + "#";
			else line = line + " ";
		}
		line = line + '\n';
		std::cout << line;
	}
	for(int x = 0; x < binc; x++) {
		std::cout << "-";
	}
	std::cout << '\n';
}

int main(int argc, char *argv[]) {
	//Create consecutive frequency bins on a logarithmic scale, starting at the frequency specified by the first argument
	double signal_freq = atof(argv[1]);
	int octaves = 3;
	int bins_per_note = 1;
	int binc = 12*octaves*bins_per_note+1;
	freq_bin *bins[binc];
	for(int i = 0; i < binc; i++) {
		bins[i] = new freq_bin(pow(2, (double)i/12/bins_per_note)*signal_freq);
	}

	//Create a signal based on a file specified by the first argument
	//file_wave signal(argv[1]);

	//or...

	//Create a sinusoidal signal with a specified frequency
	sin_wave signal(1);

	int t = 0;

	//Get terminal size
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int width = w.ws_col;
	int height = w.ws_row;

	while(true) {
		signal.update(t);

		for(int i = 0; i < binc; i++) {
			bins[i]->update(signal.level);
		}

		if(!(t%(1000/REFRESH_HZ))) {
			//Show the signals side by side
			show(signal.level, width/3);
			compare(bins, binc, 2*width/3);

			//or...

			//Show the frequency content of the signal as a spectrum
			//spec(bins, binc, width, height);
			std::cout << '\n';
		}
		t++;
		usleep(100000/REFRESH_HZ);
	}

	for(int i = 0; i < binc; i++) {
		delete[] bins[i];
	}
}
