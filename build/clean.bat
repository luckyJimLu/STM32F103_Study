@echo off
setlocal EnableExtensions

call "%~dp0_env.bat"
if errorlevel 1 exit /b 1

set "PRESET=%~1"
if not defined PRESET set "PRESET=all"

if /i "%PRESET%"=="all" goto clean_all
if /i "%PRESET%"=="baremetal-debug" goto clean_one
if /i "%PRESET%"=="baremetal-release" goto clean_one
if /i "%PRESET%"=="rtt-debug" goto clean_one
if /i "%PRESET%"=="freertos-debug" goto clean_one

echo [ERROR] Unknown preset: %PRESET%
echo [INFO] Valid values: all, baremetal-debug, baremetal-release, rtt-debug, freertos-debug
exit /b 2

:clean_all
set "CLEAN_TARGET=%PROJECT_ROOT%\build\out"
echo [INFO] Removing all build outputs: "%CLEAN_TARGET%"
"%CMAKE_EXE%" -E remove_directory "%CLEAN_TARGET%"
if errorlevel 1 exit /b 1
echo [SUCCESS] All build outputs were removed. Scripts and generated configuration were preserved.
exit /b 0

:clean_one
set "CLEAN_TARGET=%PROJECT_ROOT%\build\out\%PRESET%"
echo [INFO] Removing preset output: "%CLEAN_TARGET%"
"%CMAKE_EXE%" -E remove_directory "%CLEAN_TARGET%"
if errorlevel 1 exit /b 1
echo [SUCCESS] Build output removed: build\out\%PRESET%
exit /b 0
