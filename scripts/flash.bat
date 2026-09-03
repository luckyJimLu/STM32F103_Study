@echo off
setlocal EnableExtensions EnableDelayedExpansion
REM ==============================================================================
REM Flash script for STM32F103 using SEGGER J-Link Commander (JLink.exe)
REM ==============================================================================

for %%I in ("%~dp0..") do set "PROJECT_ROOT=%%~fI"

set "PRESET=%~1"
if not defined PRESET set "PRESET=configured-debug"

set "TARGET_DEVICE=%~2"
if defined JLINK_DEVICE if not defined TARGET_DEVICE set "TARGET_DEVICE=%JLINK_DEVICE%"

set "OUT_DIR=%PROJECT_ROOT%\build\out\%PRESET%"
set "HEX_FILE=%OUT_DIR%\STM32F103_Study.hex"
set "BIN_FILE=%OUT_DIR%\STM32F103_Study.bin"
set "ELF_FILE=%OUT_DIR%\STM32F103_Study.elf"

if not exist "%HEX_FILE%" (
    if not exist "%BIN_FILE%" (
        if not exist "%ELF_FILE%" (
            echo [ERROR] Firmware not found in "%OUT_DIR%". Please build the project first.
            echo        e.g. build\build.bat %PRESET%
            exit /b 1
        )
    )
)

:: Automatically infer target device if not specified
if not defined TARGET_DEVICE (
    echo %PRESET% | findstr /I "atk elite ze" >nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        set "TARGET_DEVICE=STM32F103ZE"
    ) else (
        echo %PRESET% | findstr /I "bluepill c8" >nul 2>&1
        if !ERRORLEVEL! EQU 0 (
            set "TARGET_DEVICE=STM32F103C8"
        )
    )
)

if not defined TARGET_DEVICE (
    if exist "%PROJECT_ROOT%\build\generated\autoconf.h" (
        findstr /C:"CONFIG_PRODUCT_ATK_ELITE_F103ZE 1" "%PROJECT_ROOT%\build\generated\autoconf.h" >nul 2>&1
        if !ERRORLEVEL! EQU 0 set "TARGET_DEVICE=STM32F103ZE"
        findstr /C:"CONFIG_PRODUCT_BLUEPILL_F103C8 1" "%PROJECT_ROOT%\build\generated\autoconf.h" >nul 2>&1
        if !ERRORLEVEL! EQU 0 set "TARGET_DEVICE=STM32F103C8"
    )
)

:: Default fallback device
if not defined TARGET_DEVICE set "TARGET_DEVICE=STM32F103ZE"

:: Locate JLink.exe
set "JLINK_EXE="
if defined JLINK_DIR if exist "%JLINK_DIR%\JLink.exe" set "JLINK_EXE=%JLINK_DIR%\JLink.exe"
if not defined JLINK_EXE (
    where JLink.exe >nul 2>&1
    if !ERRORLEVEL! EQU 0 (
        for /f "delims=" %%i in ('where JLink.exe') do (
            if not defined JLINK_EXE set "JLINK_EXE=%%i"
        )
    )
)
if not defined JLINK_EXE if exist "C:\Program Files\SEGGER\JLink\JLink.exe" set "JLINK_EXE=C:\Program Files\SEGGER\JLink\JLink.exe"
if not defined JLINK_EXE if exist "C:\Program Files (x86)\SEGGER\JLink\JLink.exe" set "JLINK_EXE=C:\Program Files (x86)\SEGGER\JLink\JLink.exe"

if not defined JLINK_EXE (
    echo [ERROR] SEGGER JLink.exe was not found!
    echo         Please install SEGGER J-Link Software or add its installation directory to PATH.
    echo         Official download: https://www.segger.com/downloads/jlink/
    exit /b 1
)

:: Choose flash file: HEX preferred, then BIN, then ELF
set "FLASH_FILE=%HEX_FILE%"
set "LOAD_CMD_ARGS="
if not exist "%HEX_FILE%" (
    if exist "%BIN_FILE%" (
        set "FLASH_FILE=%BIN_FILE%"
        set "LOAD_CMD_ARGS= 0x08000000"
    ) else (
        set "FLASH_FILE=%ELF_FILE%"
    )
)

:: Convert backslashes to forward slashes for J-Link command script
set "FLASH_FILE_SLASH=%FLASH_FILE:\=/%"

set "JLINK_SCRIPT=%TEMP%\jlink_flash_%RANDOM%.jlink"

(
    echo r
    echo h
    echo loadfile "%FLASH_FILE_SLASH%"%LOAD_CMD_ARGS%
    echo r
    echo g
    echo qc
) > "%JLINK_SCRIPT%"

echo ==============================================================================
echo [INFO] Flashing STM32F103 with SEGGER J-Link
echo [INFO] Preset: %PRESET%
echo [INFO] Target Device: %TARGET_DEVICE%
echo [INFO] Firmware File: %FLASH_FILE%
echo [INFO] J-Link Executable: %JLINK_EXE%
echo ==============================================================================

"%JLINK_EXE%" -nogui 1 -ExitOnError 1 -device %TARGET_DEVICE% -if SWD -speed 4000 -autoconnect 1 -CommanderScript "%JLINK_SCRIPT%"
set "FLASH_RET=%ERRORLEVEL%"

if exist "%JLINK_SCRIPT%" del /f /q "%JLINK_SCRIPT%" >nul 2>&1

echo.
if %FLASH_RET% EQU 0 (
    echo [SUCCESS] Flashing and verification completed successfully. Target is running.
    exit /b 0
)

echo [ERROR] Flashing failed with error code %FLASH_RET%.
echo.
echo [TROUBLESHOOTING GUIDE]
echo 1. Check hardware SWD connections:
echo    - J-Link Pin 1 (VTref) -^> 3.3V (VCC) [CRITICAL: Target must supply reference voltage!]
echo    - J-Link Pin 7 (SWDIO) -^> PA13
echo    - J-Link Pin 9 (SWCLK) -^> PA14
echo    - J-Link Pin GND       -^> GND
echo 2. Make sure the STM32 board is powered ON (LED indicator is lit).
echo 3. Ensure no other debugger or serial monitor has locked the J-Link probe.
echo 4. If chip is locked/sleeping, press and hold RESET button, run script, then release RESET.
exit /b %FLASH_RET%
