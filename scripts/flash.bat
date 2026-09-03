@echo off
setlocal EnableExtensions
REM Flash script for STM32F103 using OpenOCD and ST-Link

for %%I in ("%~dp0..") do set "PROJECT_ROOT=%%~fI"
set "PRESET=%~1"
if not defined PRESET set "PRESET=configured-debug"
set "ELF_FILE=%PROJECT_ROOT%\build\out\%PRESET%\STM32F103_Study.elf"

if not exist "%ELF_FILE%" (
    echo [ERROR] ELF file not found. Please build the project first.
    exit /b 1
)

echo [INFO] Flashing %ELF_FILE% to target STM32F103...
openocd -f "%PROJECT_ROOT%\scripts\openocd_stlink.cfg" -c "program %ELF_FILE% verify reset exit"

if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Flashing completed successfully!
) else (
    echo [ERROR] Flashing failed. Check your ST-Link connection and drivers.
)
