@echo off
rem Local, process-only build environment. This file must be called by other scripts.

for %%I in ("%~dp0..") do set "PROJECT_ROOT=%%~fI"
set "TOOLS_ROOT=%PROJECT_ROOT%\tools"
set "CMAKE_EXE=%TOOLS_ROOT%\cmake\bin\cmake.exe"
set "NINJA_EXE=%TOOLS_ROOT%\ninja\ninja.exe"
set "ARM_GCC_EXE=%TOOLS_ROOT%\toolchain\bin\arm-none-eabi-gcc.exe"

if not exist "%CMAKE_EXE%" (
    echo [ERROR] CMake was not found: "%CMAKE_EXE%"
    exit /b 1
)

if not exist "%NINJA_EXE%" (
    echo [ERROR] Ninja was not found: "%NINJA_EXE%"
    exit /b 1
)

if not exist "%ARM_GCC_EXE%" (
    echo [ERROR] GNU Arm compiler was not found: "%ARM_GCC_EXE%"
    exit /b 1
)

set "PATH=%TOOLS_ROOT%\cmake\bin;%TOOLS_ROOT%\ninja;%TOOLS_ROOT%\toolchain\bin;%PATH%"
if exist "C:\Program Files\SEGGER\JLink" (
    set "PATH=C:\Program Files\SEGGER\JLink;%PATH%"
) else if exist "C:\Program Files (x86)\SEGGER\JLink" (
    set "PATH=C:\Program Files (x86)\SEGGER\JLink;%PATH%"
)
exit /b 0
