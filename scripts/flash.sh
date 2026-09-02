#!/bin/bash
# Flash script for STM32F103 using OpenOCD and ST-Link

ELF_FILE="build/baremetal-debug/STM32F103_Study.elf"
if [ ! -f "$ELF_FILE" ]; then
    ELF_FILE="build/STM32F103_Study.elf"
fi

if [ ! -f "$ELF_FILE" ]; then
    echo "[ERROR] ELF file not found. Please build the project first."
    exit 1
fi

echo "[INFO] Flashing $ELF_FILE to target STM32F103..."
openocd -f scripts/openocd_stlink.cfg -c "program $ELF_FILE verify reset exit"

if [ $? -eq 0 ]; then
    echo "[SUCCESS] Flashing completed successfully!"
else
    echo "[ERROR] Flashing failed. Check your ST-Link connection."
fi
