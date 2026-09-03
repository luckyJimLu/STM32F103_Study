#!/bin/bash
# ==============================================================================
# Flash script for STM32F103 using SEGGER J-Link Commander (JLinkExe)
# ==============================================================================

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PRESET="${1:-configured-debug}"
TARGET_DEVICE="${2:-${JLINK_DEVICE}}"

OUT_DIR="$PROJECT_ROOT/build/out/$PRESET"
HEX_FILE="$OUT_DIR/STM32F103_Study.hex"
BIN_FILE="$OUT_DIR/STM32F103_Study.bin"
ELF_FILE="$OUT_DIR/STM32F103_Study.elf"

if [ ! -f "$HEX_FILE" ] && [ ! -f "$BIN_FILE" ] && [ ! -f "$ELF_FILE" ]; then
    echo "[ERROR] Firmware not found in $OUT_DIR. Please build the project first."
    echo "        e.g. ./build/build.sh $PRESET (or scripts/build.bat)"
    exit 1
fi

# Detect target device
if [ -z "$TARGET_DEVICE" ]; then
    case "$PRESET" in
        *atk*|*elite*|*ze*)
            TARGET_DEVICE="STM32F103ZE"
            ;;
        *bluepill*|*c8*)
            TARGET_DEVICE="STM32F103C8"
            ;;
        *)
            if [ -f "$PROJECT_ROOT/build/generated/autoconf.h" ]; then
                if grep -q "CONFIG_PRODUCT_ATK_ELITE_F103ZE 1" "$PROJECT_ROOT/build/generated/autoconf.h"; then
                    TARGET_DEVICE="STM32F103ZE"
                elif grep -q "CONFIG_PRODUCT_BLUEPILL_F103C8 1" "$PROJECT_ROOT/build/generated/autoconf.h"; then
                    TARGET_DEVICE="STM32F103C8"
                fi
            fi
            ;;
    esac
fi

[ -z "$TARGET_DEVICE" ] && TARGET_DEVICE="STM32F103ZE"

# Find J-Link executable
JLINK_CMD=""
if [ -n "$JLINK_EXE" ] && command -v "$JLINK_EXE" >/dev/null 2>&1; then
    JLINK_CMD="$JLINK_EXE"
elif command -v JLinkExe >/dev/null 2>&1; then
    JLINK_CMD="JLinkExe"
elif command -v JLink.exe >/dev/null 2>&1; then
    JLINK_CMD="JLink.exe"
elif [ -f "/opt/SEGGER/JLink/JLinkExe" ]; then
    JLINK_CMD="/opt/SEGGER/JLink/JLinkExe"
elif [ -f "/Applications/SEGGER/JLink/JLinkExe" ]; then
    JLINK_CMD="/Applications/SEGGER/JLink/JLinkExe"
elif [ -f "C:/Program Files/SEGGER/JLink/JLink.exe" ]; then
    JLINK_CMD="C:/Program Files/SEGGER/JLink/JLink.exe"
fi

if [ -z "$JLINK_CMD" ]; then
    echo "[ERROR] SEGGER J-Link executable (JLinkExe / JLink.exe) not found!"
    echo "        Please install J-Link Software: https://www.segger.com/downloads/jlink/"
    exit 1
fi

if [ -f "$HEX_FILE" ]; then
    FLASH_FILE="$HEX_FILE"
    LOAD_CMD="loadfile \"$HEX_FILE\""
elif [ -f "$BIN_FILE" ]; then
    FLASH_FILE="$BIN_FILE"
    LOAD_CMD="loadfile \"$BIN_FILE\" 0x08000000"
else
    FLASH_FILE="$ELF_FILE"
    LOAD_CMD="loadfile \"$ELF_FILE\""
fi

JLINK_SCRIPT=$(mktemp /tmp/jlink_flash_XXXXXX.jlink 2>/dev/null || echo "$PROJECT_ROOT/build/jlink_flash_temp.jlink")

cat <<EOF > "$JLINK_SCRIPT"
r
h
$LOAD_CMD
r
g
qc
EOF

echo "=============================================================================="
echo "[INFO] Flashing STM32F103 with SEGGER J-Link"
echo "[INFO] Preset: $PRESET"
echo "[INFO] Target Device: $TARGET_DEVICE"
echo "[INFO] Firmware File: $FLASH_FILE"
echo "[INFO] J-Link Command: $JLINK_CMD"
echo "=============================================================================="

"$JLINK_CMD" -nogui 1 -ExitOnError 1 -device "$TARGET_DEVICE" -if SWD -speed 4000 -autoconnect 1 -CommanderScript "$JLINK_SCRIPT"
FLASH_RET=$?

rm -f "$JLINK_SCRIPT"

echo ""
if [ $FLASH_RET -eq 0 ]; then
    echo "[SUCCESS] Flashing and verification completed successfully! Target is running."
    exit 0
else
    echo "[ERROR] Flashing failed with error code $FLASH_RET."
    echo ""
    echo "[TROUBLESHOOTING GUIDE]"
    echo "1. Check hardware SWD connections:"
    echo "   - J-Link Pin 1 (VTref) -> 3.3V (VCC) [CRITICAL: Target must supply reference voltage!]"
    echo "   - J-Link Pin 7 (SWDIO) -> PA13"
    echo "   - J-Link Pin 9 (SWCLK) -> PA14"
    echo "   - J-Link Pin GND       -> GND"
    echo "2. Make sure the STM32 board is powered ON."
    echo "3. Ensure no other debugger or serial monitor has locked the J-Link probe."
    echo "4. If chip is locked/sleeping, hold RESET button, run script, then release RESET."
    exit $FLASH_RET
fi
