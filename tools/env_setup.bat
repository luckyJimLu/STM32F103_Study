@echo off
REM ==============================================================================
REM env_setup.bat - Temporary Environment Setup for STM32F103 Tools
REM ==============================================================================

set "TOOLS_ROOT=%~dp0"

echo [INFO] Setting up local toolchain paths from %TOOLS_ROOT%...

if exist "%TOOLS_ROOT%toolchain\bin" (
    set "PATH=%TOOLS_ROOT%toolchain\bin;%PATH%"
    echo [OK] Added toolchain\bin to PATH
)

if exist "%TOOLS_ROOT%ninja" (
    set "PATH=%TOOLS_ROOT%ninja;%PATH%"
    echo [OK] Added ninja to PATH
)

if exist "%TOOLS_ROOT%cmake\bin" (
    set "PATH=%TOOLS_ROOT%cmake\bin;%PATH%"
    echo [OK] Added cmake\bin to PATH
)

if exist "%TOOLS_ROOT%openocd\bin" (
    set "PATH=%TOOLS_ROOT%openocd\bin;%PATH%"
    echo [OK] Added openocd\bin to PATH
)

if exist "C:\Program Files\SEGGER\JLink" (
    set "PATH=C:\Program Files\SEGGER\JLink;%PATH%"
    echo [OK] Added SEGGER J-Link to PATH
) else if exist "C:\Program Files (x86)\SEGGER\JLink" (
    set "PATH=C:\Program Files (x86)\SEGGER\JLink;%PATH%"
    echo [OK] Added SEGGER J-Link to PATH
)

echo.
echo [INFO] Environment ready. You can now run 'arm-none-eabi-gcc -v', 'cmake', 'ninja', 'JLink.exe'.
