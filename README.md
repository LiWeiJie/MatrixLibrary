# MatrixLibrary

## Build and install



Just like:

```
$ cmake [params] PATH/TO/MatrixLibrary
$ make
$ make install
```

### Params

#### BUILD_TARGET

##### iOS

`-DBUILD_TARGET=iOS`

必备软件：`cmake`、`gcc(clang)`

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=ios.toolchain.cmake -DIOS_ARCH='armv7;arm64'  ..
make
```

编译出的库在 `build/lib` 目录。



##### macOS

`-DBUILD_TARGET=macOS`

##### win32

`-DBUILD_TARGET=win32`

##### Android

`-DDBUILD_TARGET=Android`