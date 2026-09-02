#!/bin/bash
# Format all C/C++/Header files in project using clang-format
cd "$(dirname "$0")/../.."

if ! command -v clang-format &> /dev/null; then
    echo "[ERROR] clang-format not found in PATH."
    exit 1
fi

echo "[INFO] Formatting C/C++ files in project..."
find app bsp -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i -style=file:tools/format/.clang-format {} +

echo "[SUCCESS] Code formatting completed!"
