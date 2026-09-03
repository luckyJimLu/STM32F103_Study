@echo off
setlocal EnableExtensions

call "%~dp0_env.bat"
if errorlevel 1 exit /b 1

set "PRESET=%~1"
if not defined PRESET set "PRESET=configured-debug"

if /i "%PRESET%"=="all" (
    python "%PROJECT_ROOT%\scripts\build_matrix.py"
    exit /b %ERRORLEVEL%
)
call :build_one "%PRESET%"
exit /b %ERRORLEVEL%

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
