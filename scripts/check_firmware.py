#!/usr/bin/env python3
"""Validate an STM32 ELF's memory budget and system-selection symbols."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import subprocess


def run(*args: str) -> str:
    return subprocess.check_output(args, text=True, errors="replace")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--elf", required=True, type=Path)
    parser.add_argument("--size-tool", required=True)
    parser.add_argument("--nm-tool", required=True)
    parser.add_argument("--flash-bytes", required=True, type=int)
    parser.add_argument("--ram-bytes", required=True, type=int)
    parser.add_argument("--system", required=True, choices=("BAREMETAL", "RTTHREAD", "FREERTOS"))
    args = parser.parse_args()

    size_output = run(args.size_tool, "--format=berkeley", str(args.elf))
    rows = [line.split() for line in size_output.splitlines()]
    values = next((row for row in rows if len(row) >= 3 and row[0].isdigit()), None)
    if values is None:
        raise SystemExit("unable to parse arm-none-eabi-size output")
    text_size, data_size, bss_size = map(int, values[:3])
    flash_used = text_size + data_size
    ram_used = data_size + bss_size

    if flash_used > args.flash_bytes:
        raise SystemExit(f"Flash budget exceeded: {flash_used} > {args.flash_bytes}")
    if ram_used > args.ram_bytes:
        raise SystemExit(f"RAM budget exceeded: {ram_used} > {args.ram_bytes}")

    nm_output = run(args.nm_tool, "--defined-only", str(args.elf))
    symbols = set(re.findall(r"[0-9a-fA-F]+\s+\w\s+(\S+)", nm_output))
    required = {"Reset_Handler", "SysTick_Handler", "main"}
    missing = required - symbols
    if missing:
        raise SystemExit(f"required firmware symbols are missing: {sorted(missing)}")

    has_rtthread = "rt_system_scheduler_start" in symbols
    has_freertos = "vTaskStartScheduler" in symbols
    expected = {
        "BAREMETAL": (False, False),
        "RTTHREAD": (True, False),
        "FREERTOS": (False, True),
    }[args.system]
    if (has_rtthread, has_freertos) != expected:
        raise SystemExit(
            "unexpected RTOS symbol set: "
            f"rtthread={has_rtthread}, freertos={has_freertos}, system={args.system}"
        )

    print(
        f">> Verified {args.system}: Flash {flash_used}/{args.flash_bytes} bytes, "
        f"RAM {ram_used}/{args.ram_bytes} bytes"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
