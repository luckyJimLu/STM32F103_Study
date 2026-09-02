@echo off
REM Format all C/C++/Header files in project using clang-format
cd /d "%~dp0\..\.."

where clang-format >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] clang-format not found in PATH.
    pause
    exit /b 1
)

echo [INFO] Formatting C/C++ files in project...
for /R app %%f in (*.c *.h) do clang-format -i -style=file:tools/format/.clang-format "%%f"
for /R bsp %%f in (*.c *.h) do clang-format -i -style=file:tools/format/.clang-format "%%f"

echo [SUCCESS] Code formatting completed!
