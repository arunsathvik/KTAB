#KUtils




This directory contains some very basic utility functions
used in KTAB. It is intended for class and functions
which are generally useful, but which do not reflect
any KTAB-specific functionality. There are few comments
because it is all pretty simple and standard.

One common class in KTAB is a simple Matrix of doubles.
It only supports very basic operations, such as +, *, -,
and inverse. It is designed for simplicity, not high performance.

The actors in KTAB models may often need to do optimizing
or satisficing. We therefore provide two very basic maximization
routines. Both are plain-vanilla implementations designed for
simplicity and transparency, not performance: 
first make it right, then make it fast.

For vector-valued domains, there is a simple hill-climbing method.
It is purely first order and does not require or estimate any
slope information. It just steps each coordinate up or down,
singly or in pairs. 

For more general domains, there is a simple genetic search
algorithm.

A simple interface to C++11 standard pseudo-random number generators is provided.


## Build Instructions ##

To build the kutils library and examples, you must
obtain and install [CMake](www.cmake.org).

You must have a working C++11 development environment.
On Windows, the KTAB build has been verified with Visual Studio 12 2013 Win64 (Community edition) using the default native compilers.
On Linux, the build has been verified with KDevelop 3 and plain Unix makefiles, using both g++ 4.8 and clang++ 3.4. Please note that at no point in the build process of any part of KTAB is it necessary to modify your PATH under either Windows or Linux (if you follow these instructions).

The first step is to start CMake; we recommend using the GUI version, not the command-line version.
In the CMake GUI, you should answer "Where is the source code"
with the location of the CMake source file CMakeLists.txt,
not the C++ source files.

Hence, if your KTAB source is checked out into /home/KTAB,
the CMakeLists.txt file would be in /home/KTAB/KTAB/kutils/CMakeLists.txt


In the CMake GUI, you  should answer "Where to build the binaries"
with /home/KTAB/KTAB/kutils/build.

Hit the "Configure" button. The first time you configure the system,
CMake should immediately ask if it should create the build directory;
answer "Yes".

The first time you configure the system, CMake should ask what generator to use for this project and offer a drop-down list of the IDE's for your platform. These are IDE's which CMake can support, which are not necessarily those installed  on your system. Select one of the installed options (you will probably need to  use the same generator for kmodel).

Hit "Finish".

CMake should display some notifications in the lower window, but there should be no errors.
The upper window may have some items marked in red; hitting "Configure" again should resolve them.

If more difficult errors occur, you will probably need to consult the CMake documentation to diagnose the problem.

After all problems are resolved, there are no error messages, and no items in the upper window are red, hit "Generate" to generate the build files for your chosen IDE. They will appear
in the build directory, like /home/KTAB/KTAB/kutils/build/kutils.sln for Windows and Visual Studio
or /home/KTAB/KTAB/kutils/build/Makefile for Linux and make.

Open the kutils project with your IDE; it should display two targets: kutils and demoutils. The former is the library of utility functions; the latter is a simple command-line demonstration
of some of the utility functions.

The INSTALL  target for kutils will install it into  C:/local for Windows and /usr/local for Linux.
 In fact, the CMake files of KTAB expect all the libraries to be in C:/local for Windows: fltk, kmodel, sqlite, tinyxml, kutil. Under Linux, the kutils, kmodel files will be installed to /usr/local. There is no need to modify your PATH under either Linux or Windows.

The demonstration program provides a help menu, as follows:


	home\KTAB\KTAB\kutils\Debug>demoutils.exe --help
	
	  Start time: Wed Oct 14 15:02:18 2015
	
	Usage: specify one or more of these options
	--help            print this message and exit
	--matrix          demo matrix functions
	--pMult           asynchronous parallel matrix multiply (very slow)
	--gopt            demo genetic optimization
	--vhc <n>         demo vector hill-climbing
	                  0: maximizing a simple quadratic
	                  1: Nash bargaining between two agents in 1D
	                  2: Nash bargaining between two agents in 4D, with scalar capabiities
	                  3: Nash bargaining between two agents in 4D, with vector capabilities
	--ghc             demo general hill-climbing to maximize a function of bit-vectors
	--vimcp <n>       demo VI and MCP
	                  0: the MCP minimize a quadratic subject to box constraints
	                  1: linear VI with ellipsoidal constraints
	                  2: Anti-Lemke linear VI
	--thread          demo several thread operations
	--seed <n>        set a 64bit seed
	                  0 means truly random
	                  default: 15455440707583219804
                  
The VI option refers to variational inequalities, and MCP refers
to mixed complementarity problems (which are a particular kind of VI).


## Contributing and License Information ##



If you are interested in contributing code, ideas, or
data to KTAB, please contact ktab@kapsarc.org


KTAB is released under The MIT License (Expat).
For details, see the following URLs:

- [http://opensource.org/](http://opensource.org/)
- [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT)
 

----------

Copyright KAPSARC. Open source MIT License.

----------

