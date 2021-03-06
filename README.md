### LAYR

#### Description
LAYR implements the analysis and reconstruction of generic abstractions and addresses the problem of reliable reconstruction of deleted files.
The strengths of LAYR lie in the fact that new heuristics can be easily added, and the combination of different reconstruction approaches improves reconstruction results.

#### Build
Please use CMake for building LAYR: [cmake.org/runningcmake](https://cmake.org/runningcmake/)

#### Notes
- Currently LAYR can be used to analyze DOS/MBR and EXT3.
- There is no error handling implemented yet so please do not use LAYR with corrupted images.
- You can test LAYR with the provided example test images.
- LAYR was tested under 64bit Windows 10 (`MinGW 7.3.0 64-bit`)