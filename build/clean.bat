@echo off
setlocal EnableExtensions

call "%~dp0_env.bat"
if errorlevel 1 exit /b 1

set "PRESET=%~1"
if not defined PRESET set "PRESET=all"

if /i "%PRESET%"=="all" goto clean_all
goto clean_one

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
