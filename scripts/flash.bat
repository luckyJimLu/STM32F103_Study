@echo off
REM Flash script for STM32F103 using OpenOCD and ST-Link

set ELF_FILE=build/baremetal-debug/STM32F103_Study.elf
if not exist "%ELF_FILE%" (
    set ELF_FILE=build/STM32F103_Study.elf
)

if not exist "%ELF_FILE%" (
    echo [ERROR] ELF file not found. Please build the project first.
    exit /b 1
)

echo [INFO] Flashing %ELF_FILE% to target STM32F103...
openocd -f scripts/openocd_stlink.cfg -c "program %ELF_FILE% verify reset exit"

if %ERRORLEVEL% EQU 0 (
    echo [SUCCESS] Flashing completed successfully!
) else (
    echo [ERROR] Flashing failed. Check your ST-Link connection and drivers.
)
