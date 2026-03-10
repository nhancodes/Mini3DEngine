## Build
Only 32-bits is not supported.
Default preset use Ninja Multi-Config. You either need to set ninja.exe in PATH or have -DCMAKE_MAKE_PROGRAM=<path/to/ninja.exe>

#### Generate CMake Cache with default preset
```
cmake --preset windows_default
```

#### Build project
```
cmake --build --preset Release
```
or 
```
cmake --build --preset Debug
```

#### Install
There is no install script yet.   

## Different compilers

### MSVC (on Windows)
---
Execute vcvarsall.bat (x64) for cl enviroments:  

### Clang (on Windows or Linux)
---
```
  -DCMAKE_C_COMPILER=<path/to/clang++.exe>
  -DMAKE_CXX_COMPILER=<path/to/bin/clang++.exe>
  -DMAKE_RC_COMPILER=<path/to/windows-sdk/rc.exe>
  -DCMAKE_MT=<path/to/windows-sdk/mt.ex>
```
you can use either clang++ or clang-cl

### GCC (on Linux)
---
Not yet supported

