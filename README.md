# pcoch
A simulated physical model for approximate Fourier analysis of digital signals.
The calculations performed by each step of the analysis are done on every frequency bin at once and involve no trigonometric functions, which are ideal characteristics for future implementation as a GPU-based Fourier Transform algorithm.
Hence the name, short for `Parallel Cochlea`.

`pcoch` can also generate really cool looking graphics by displaying the oscillations of every frequency bin on top of each other.

# Principle
Frequency bins are modeled as physical springs with increasing resonant frequencies, each affected equally by the external force of a signal pressure.
The amplitude in each bin is calculated from the extreme positions of the spring during each oscillation.

# Building
Has a dependency on `libsndfile` for reading arbitrary audio signals from files.
Use `git clone` and `make`.

# Using
For now, you'll have to juggle some comment blocks around until I create a stable interface.

# Todo
 - Stabilize interface
 - Implement a spectrum class to store frequency bins
 - Improve accuracy to match output of conventional FFT implementations.
 - Look into feasibility of reverse transformation
