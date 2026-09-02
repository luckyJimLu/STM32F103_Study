#!/bin/bash
# Launcher for STM32F103 Kconfig menuconfig
cd "$(dirname "$0")/.."

python3 scripts/menuconfig.py "$@"
if [ $? -ne 0 ]; then
    echo "[ERROR] Failed to run menuconfig. Please ensure Python 3 is installed."
fi
