all: pcoch.o freq_bin.o signal.o
	g++ -Wall -g -o pcoch pcoch.o freq_bin.o signal.o -lsndfile
pcoch.o: pcoch.cc
	g++ -Wall -g -c pcoch.cc
freq_bin.o: freq_bin.cc freq_bin.h
	g++ -Wall -g -c freq_bin.cc
signal.o: signal.cc signal.h
	g++ -Wall -g -c signal.cc
clean:
	rm -f pcoch *.o
