# MatrixLibrary

一个基于m4ri扩展的数学运算库，添加了伽罗瓦域gf2下的矩阵运算，仿射变换运算

## Build and Install

- Output: 
  - bin: `build/bin`
  - lib:`build/lib`

### Build Options

- `CMAKE_BUILD_TYPE=(Debug/Release)`
- `BUILD_TARGET=(iOS/win32/macOS/Unix/Android)`
- `CMAKE_INSTALL_PREFIX=(PATH/TO/INSTALLED)`
- `RANDOM_FUNC=(default/aisino)`:
    - `default`= using rand() function
    - `aisino` = using the random function in aisino_rand lib
- iOS:
    - `IOS_PLATFORM`: OS (default) or SIMULATOR or SIMULATOR64 or TVOS or SIMULATOR_TVOS or WATCHOS
        - `OS` = Build for iPhoneOS.
        - `OS64` = Build for arm64 iPhoneOS.
        - `SIMULATOR` = Build for x86 i386 iPhone Simulator.
        - `SIMULATOR64` = Build for x86_64 iPhone Simulator.
        - `TVOS` = Build for AppleTVOS.
        - `SIMULATOR_TVOS` = Build for x86_64 AppleTV Simulator.
        - `WATCHOS` = Build for armv7k for WatchOS.
        - `SIMULATOR_WATCHOS` = Build for i386 for Watch Simulator.
    - `IOS_ARCH`: (armv7 armv7s arm64 i386 x86_64) If specified, will override the default architectures for the given IOS_PLATFORM
        - `OS` = armv7 armv7s arm64 arm64e
        - `OS64` = arm64 arm64e
        - `SIMULATOR` = i386
        - `SIMULATOR64` = x86_64
        - `TVOS` = arm64
        - `SIMULATOR_TVOS` = x86_64
        - `WATCHOS` = armv7k
        - `SIMULATOR_WATCHOS` = i386
    - `CMAKE_OSX_SYSROOT`: Path to the iOS SDK to use.  By default this is automatically determined from IOS_PLATFORM and xcodebuild, but can also be manually specified (although this should not be required).
    - `CMAKE_IOS_DEVELOPER_ROOT`: Path to the Developer directory for the iOS platform being compiled for.  By default this is automatically determined from CMAKE_OSX_SYSROOT, but can also be manually specified (although this should not be required).
    - `ENABLE_BITCODE`: (1|0) Enables or disables bitcode support. Default 1 (true)
    - `ENABLE_ARC`: (1|0) Enables or disables ARC support. Default 1 (true, ARC enabled by default)
    - `ENABLE_VISIBILITY`: (1|0) Enables or disables symbol visibility support. Default 0 (false, visibility hidden by default)
- `Android`:
    - `ANDROID_ABI=(arm64-v8a armeabi-v7a armeabi-v6 armeabi mips mips64 x86 x86_64)`

### Build Example

#### iOS
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=iOS -DCMAKE_TOOLCHAIN_FILE=../ios.toolchain.cmake -DIOS_ARCH='armv7;arm64'  -DCMAKE_BUILD_TYPE=Release ..
make
```
#### macOS
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=macOS  -DCMAKE_BUILD_TYPE=Release ..
make
```
#### Unix
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=Unix  -DCMAKE_BUILD_TYPE=Release ..
make
```
#### win32
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=win32  -DCMAKE_BUILD_TYPE=Release ..
make
```
#### Android
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=Android -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${NDK_ROOT}/build/cmake/android.toolchain.cmake -DANDROID_ABI='arm64-v8a' ..
make
```

