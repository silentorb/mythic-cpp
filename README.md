# Mythic Game Engine
Created by Christopher W. Johnson

### Installation Instructions

* Clone repository into an existing mythic folder (resulting in mythic/mythic).
* Set CMake "Build Output Path" to ../bin
* Clone the mythic-dependencies repo into the parent mythic folder.
* Compile and install the mythic-dependencies.  (That will create a dependencies folder in the root mythic folder.)

### Compiling for MSVC
    cd ../build/msvc
    cmake -G "Visual Studio 14 2015" ../../mythic

### Compiling for iOS

  cd ../build
    cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake-tools/toolchains/ios.cmake -G Xcode ../mythic

### Compiling for Android

This involves 3 commands:
1. Generating the Android makefiles
2. Building the source
3. Deploying the apk and launching the debugger


    cd ../build/android
    Start-Process cmake -ArgumentList "cmake -G ""MinGW Makefiles"" -DANDROID_NDK=E:\Programs\crystax-ndk-10.3.1 -DCMAKE_BUILD_TYPE=Debug -DANDROID_ABI=armeabi-v7a ../../mythic" -NoNewWindow
    ./build
    ./debug

### Generating Graph Viz

    cmake -DGRAPHVIZ=1 -G "Visual Studio 14 2015" ../../mythic
    e:/Programs/graphviz/bin/dot -O -T pdf mythic.dot

     