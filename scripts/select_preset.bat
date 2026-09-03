@echo off
setlocal EnableExtensions
set "BOARD="
set "SYSTEM="
set "BUILD_VERSION="

if "%~1"=="" (
    echo [ERROR] The output variable name is required.
    exit /b 1
)

echo.
echo Select Board:
echo   1. BluePill ^(STM32F103C8T6^)
echo   2. ALIENTEK Elite ^(STM32F103ZET6^)

:select_board
set "BOARD_CHOICE="
set /p "BOARD_CHOICE=Enter board number [1-2]: "
if errorlevel 1 (
    echo [ERROR] Input was cancelled.
    exit /b 1
)
if "%BOARD_CHOICE%"=="1" set "BOARD=bluepill"
if "%BOARD_CHOICE%"=="2" set "BOARD=atk-elite"
if not defined BOARD (
    echo [ERROR] Invalid board number. Enter 1 or 2.
    goto select_board
)

echo.
echo Select System:
echo   1. Bare Metal
echo   2. RT-Thread
echo   3. FreeRTOS

:select_system
set "SYSTEM_CHOICE="
set /p "SYSTEM_CHOICE=Enter system number [1-3]: "
if errorlevel 1 (
    echo [ERROR] Input was cancelled.
    exit /b 1
)
if "%SYSTEM_CHOICE%"=="1" set "SYSTEM=baremetal"
if "%SYSTEM_CHOICE%"=="2" set "SYSTEM=rtthread"
if "%SYSTEM_CHOICE%"=="3" set "SYSTEM=freertos"
if not defined SYSTEM (
    echo [ERROR] Invalid system number. Enter 1, 2, or 3.
    goto select_system
)

echo.
echo Select Build Version:
echo   1. Debug
echo   2. Release

:select_version
set "VERSION_CHOICE="
set /p "VERSION_CHOICE=Enter build version number [1-2]: "
if errorlevel 1 (
    echo [ERROR] Input was cancelled.
    exit /b 1
)
if "%VERSION_CHOICE%"=="1" set "BUILD_VERSION=debug"
if "%VERSION_CHOICE%"=="2" set "BUILD_VERSION=release"
if not defined BUILD_VERSION (
    echo [ERROR] Invalid build version number. Enter 1 or 2.
    goto select_version
)

set "SELECTED_PRESET=%BOARD%-%SYSTEM%-%BUILD_VERSION%"
echo.
echo [INFO] Selected preset: %SELECTED_PRESET%
endlocal & set "%~1=%SELECTED_PRESET%"
exit /b 0
