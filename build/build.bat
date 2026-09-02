@echo off
setlocal EnableExtensions

call "%~dp0_env.bat"
if errorlevel 1 exit /b 1

set "PRESET=%~1"
if not defined PRESET set "PRESET=baremetal-debug"

if /i "%PRESET%"=="all" goto build_all
call :build_one "%PRESET%"
exit /b %ERRORLEVEL%

:build_all
call :build_one "baremetal-debug"
if errorlevel 1 exit /b 1
call :build_one "baremetal-release"
if errorlevel 1 exit /b 1
call :build_one "rtt-debug"
if errorlevel 1 exit /b 1
call :build_one "freertos-debug"
if errorlevel 1 exit /b 1
echo.
echo [SUCCESS] All presets built successfully.
exit /b 0

:build_one
set "CURRENT_PRESET=%~1"
echo.
echo [INFO] Configuring preset: %CURRENT_PRESET%
"%CMAKE_EXE%" --preset "%CURRENT_PRESET%"
if errorlevel 1 (
    echo [ERROR] Configure failed for preset: %CURRENT_PRESET%
    exit /b 1
)

echo [INFO] Building preset: %CURRENT_PRESET%
"%CMAKE_EXE%" --build --preset "%CURRENT_PRESET%" --parallel
if errorlevel 1 (
    echo [ERROR] Build failed for preset: %CURRENT_PRESET%
    exit /b 1
)

echo [SUCCESS] Build completed: build\out\%CURRENT_PRESET%
exit /b 0
