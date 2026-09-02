#!/bin/bash
# ==============================================================================
# env_setup.sh - Temporary Environment Setup for STM32F103 Tools (Linux/macOS)
# ==============================================================================

TOOLS_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "[INFO] Setting up local toolchain paths from $TOOLS_ROOT..."

if [ -d "$TOOLS_ROOT/toolchain/bin" ]; then
    export PATH="$TOOLS_ROOT/toolchain/bin:$PATH"
    echo "[OK] Added toolchain/bin to PATH"
fi

if [ -d "$TOOLS_ROOT/ninja" ]; then
    export PATH="$TOOLS_ROOT/ninja:$PATH"
    echo "[OK] Added ninja to PATH"
fi

if [ -d "$TOOLS_ROOT/cmake/bin" ]; then
    export PATH="$TOOLS_ROOT/cmake/bin:$PATH"
    echo "[OK] Added cmake/bin to PATH"
fi

if [ -d "$TOOLS_ROOT/openocd/bin" ]; then
    export PATH="$TOOLS_ROOT/openocd/bin:$PATH"
    echo "[OK] Added openocd/bin to PATH"
fi

echo "[INFO] Environment ready."
