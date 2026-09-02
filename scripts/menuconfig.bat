@echo off
REM Launcher for STM32F103 Kconfig menuconfig
cd /d "%~dp0\.."

python scripts/menuconfig.py %*
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERROR] Failed to run menuconfig. Please ensure Python 3 is installed.
    pause
)
