# MatrixLibrary

一个基于m4ri扩展的数学运算库，添加了伽罗瓦域gf2下的矩阵运算，仿射变换运算

## Build and Install

- Output: 
  - bin: `build/bin`
  - lib:`build/lib`

### Build Options

- `CMAKE_BUILD_TYPE=[Debug/Release]`
- `BUILD_TARGET=[iOS/win32/macOS]`
- `CMAKE_INSTALL_PREFIX=[PATH/TO/INSTALLED]`

### Build Example

#### iOS
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=iOS -DCMAKE_TOOLCHAIN_FILE=../iOS.toolchain.cmake -DIOS_ARCH='armv7;arm64'  -DCMAKE_BUILD_TYPE=Release ..
make
```
#### macOS
```bash
mkdir build
cd build
cmake -DBUILD_TARGET=macOS  -DCMAKE_BUILD_TYPE=Release ..
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
ndk-build NDK_PROJECT_PATH=./ NDK_APPLICATION_MK=./MatrixLibrary.mk
```

