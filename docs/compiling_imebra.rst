.. _compiling-imebra-label:

Compiling Imebra
================

This section explains how to compile Imebra from the source distribution.
You can download the source distribution from https://imebra.com, or you can create a source distribution
by following the instructions at :ref:`build-distribution-label`

The result of the Imebra compilation is a shared library for your operating system of choice.

The Imebra Source Distribution includes:

- the source code for the library
- the source code for the tests
- pre-built documentation


Compiling the C++ version of Imebra
-----------------------------------

Prerequisites
.............

In order to build the library from the Imebra Source Distribution you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- a modern C++ compiler (GCC, clang, Visual Studio, etc)
- CMake version 2.8 or newer (https://cmake.org/)



Building Imebra
...............

The root folder of the source distributions contains a CMakeLists file, which contains the information
needed by CMake to generate a solution file for your platform (a make file, a VisualStudio solution, etc).

To generate the Imebra shared library, execute the following steps:

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's distributrion root folder as parameter
4. execute cmake with the --build option, and on Windows optionally specify the build configuration
5. run the tests with ctest -V .

For instance:

::

    md artifacts
    cd artifacts
    cmake imebra_location
    cmake --build .
    ctest -V .

The first CMake command will generate a solution file for the your platform: this will be a 
make file on Linux, a VisualStudio solution of Windows, an XCode project on Mac.

The second CMake command with the --build option will launch make, VisualStudio or the build
chain defined on your machine.

The CTest command will launch the test application.


Windows specific instructions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

On Windows cmake will, by default, generate a 32 bit solution for the most recent Visual Studio compiler installed on
the system.

Additionally, when specifying the --build option it is possible to specify the debug or relase configuration via
the option "--config Debug" or "--config Release"

It is possible to build a 64 bit version of the library by explicitly specifying a 64 bit generator when launching cmake.

The cmake generators available on Windows include:

- Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
- Visual Studio 10 2010 [arch] = Generates Visual Studio 2010 project files.
                                 Optional [arch] can be "Win64" or "IA64".
- Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
- Visual Studio 8 2005 [arch]  = Generates Visual Studio 2005 project files.
                                 Optional [arch] can be "Win64".

To generate the 64 bit version of the library just specify the proper generator and architecture.
For instance the following script will compile a Release 64 bit version of imebra using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_release
    cd artifacts_64bit_release
    cmake -G "Visual Studio 14 2015 Win64" imebra_location
    cmake --build . --config Release

The following example will compile a Debug 64 bit version of imebra using Visual Studio 14 (2015):

::

    mkdir artifacts_64bit_debug
    cd artifacts_64bit_debug
    cmake -G "Visual Studio 14 2015 Win64" imebra_location
    cmake --build . --config Debug

To generate the 32 bit version of the library, just omit the architecture after the name of the cmake generator:

::

    mkdir artifacts_32bit_debug
    cd artifacts_32bit_debug
    cmake -G "Visual Studio 14 2015" imebra_location
    cmake --build . --config Debug


OS-X/iOS specific instructions
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

On Mac, CMake will generate a build for OS-X. In order to generate a build for iOS you have to add one of
the following arguments to cmake::

    -DIOS=IPHONE

or::

    -DIOS=SIMULATOR

The first flag forces CMake to generate a library for iPhone (real hardware), while the second forces CMake
to generate a library for the iPhone simulator.

To generate a library for OS-X, type the following (replace imebra_location with the path to Imebra):

::

    mkdir imebra_for_osx
    cd imebra_for_osx
    cmake imebra_location
    cmake --build .

To generate a library for iPhone, type the following (replace imebra_location with the path to Imebra):

::

    mkdir imebra_for_ios
    cd imebra_for_ios
    cmake imebra_location -DIOS=IPHONE
    cmake --build .

.. warning:: iOS applications based on Imebra need to be linked also with libiconv.a or libiconv.tbd.

To generate a library for the iPhone simulator, type the following (replace imebra_location with the path to Imebra):

::

    mkdir imebra_for_ios
    cd imebra_for_ios
    cmake imebra_location -DIOS=SIMULATOR
    cmake --build .

.. warning:: iOS applications based on Imebra need to be linked also with libiconv.a or libiconv.tbd.

To generate a project that can be opened with XCode append the argument -G xcode (replace imebra_location with the path to Imebra):

::

    mkdir xcode_project
    cd xcode_project
    cmake imebra_location -G xcode


Using Imebra with Swift
'''''''''''''''''''''''
Imebra can be imported into a Swift project.

After compiling the library for OS-X or iOS, import the library's Objective-C header into your Swift project (import /wrappers/objectivec/include/imebraobjc/imebra_swift.h)
and link with imebra and iconv.

For instance, the following command line instruction launches the swift compiler and instructs it to load the imebra header and link with Imebra and iconv::

    swiftc -import-objc-header imebra_location/wrappers/objectivec/include/imebraobjc/imebra_swift.h myCode.swift -Lbuild_imebra_location -liconv -lc++ -limebra -o myCodeApp


Compiling the Android version of Imebra
---------------------------------------

Prerequisites
.............

In order to build the Android version of Imebra you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- Android Studio
- Android SDK
- Android NDK

Building Imebra
...............

The Android version of the library needs both the Java source code (located in the wrappers/javaWrapper folder) and the C++ source code (located in the library folder)

To generate the Imebra Jar library:

- Launch Android Studio
- Open the gradle project in the wrappers/javaWrapper folder
- Build the project


.. _compiling-imebra-java-linux:

Compiling the Java version of Imebra for Linux
----------------------------------------------

Prerequisites
.............

In order to build the Java version of Imebra you need:

- the source distribution of Imebra, available here: https://imebra.com/get-it/
- a modern C++ compiler (GCC or clang)
- CMake version 2.8 or newer (https://cmake.org/)
- the Java JDK
- the Java JNI headers

Building Imebra
...............

The Java version of the library needs both the Java source code (located in the wrappers/javaWrapper folder) and the C++ source code (located in the library folder).

The C++ code will be compiled into a dynamic library, while the java code can be added directly to your app or can be compiled into a Jar.


Compiling the C++ code
,,,,,,,,,,,,,,,,,,,,,,

To generate the native Imebra dynamic library (libimebrajni):

1. Create a folder that will contain the result of the compilation (artifacts)
2. cd into the created artifacts folder
3. execute cmake with the path to the Imebra's "wrappers/javaWrapper" folder as parameter
4. execute cmake with the --build option

For instance:

::

    md artifacts
    cd artifacts
    cmake imebra_location/wrapper/javaWrappers
    cmake --build .

The first CMake command will generate a solution file for the your platform, the second CMake command with the --build option will launch make.


Compiling the Java code
,,,,,,,,,,,,,,,,,,,,,,,

The Java code is in the source distribution folder "wrappers/javaWrapper/src". Compile it with the java compiler (javac) and pack it into a Jar
or add it directly to your Java application.


Loading the native library
..........................

Before your application can call any method on any Imebra class it must load the native dynamic library.

In your application startup code add:

::

    System.loadLibrary("imebrajni");


When you launch the application, specify the folder containing the native dynamic library by setting the "java.library.path" property.


Compiling the Python version of Imebra
--------------------------------------

Prerequisites
.............

In order to build Imebra for Python you need:

- Python installed
- setuptools

Building Imebra
...............

The root folder of the source distribution contains the setup.py file necessary to build and install Imebra for Python.

In order to build and install Imebra for Python:

- cd into the root folder of the Imebra Source Distribution
- run the setup.py file with the install option (requires administrator privileges):

::

    cd imebra
    python setup.py install

To remove the Python version of Imebra from your system:

::

    pip uninstall imebra



