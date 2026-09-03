#!/usr/bin/env python3
"""Configure and build every committed product/system preset."""

from __future__ import annotations

import json
from pathlib import Path
import subprocess
import sys


ROOT = Path(__file__).resolve().parent.parent


def cmake_command() -> str:
    bundled = ROOT / "tools" / "cmake" / "bin" / "cmake.exe"
    return str(bundled) if bundled.exists() else "cmake"


def main() -> int:
    document = json.loads((ROOT / "CMakePresets.json").read_text(encoding="utf-8"))
    presets = [
        entry["name"]
        for entry in document["buildPresets"]
        if entry["name"] != "configured-debug"
    ]
    cmake = cmake_command()
    for preset in presets:
        print(f"\n>> Configuring {preset}", flush=True)
        subprocess.run([cmake, "--preset", preset], cwd=ROOT, check=True)
        print(f">> Building {preset}", flush=True)
        subprocess.run(
            [cmake, "--build", "--preset", preset, "--parallel"],
            cwd=ROOT,
            check=True,
        )
    print(f"\n>> Build matrix passed: {len(presets)} firmware images")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except subprocess.CalledProcessError as error:
        print(f">> Build matrix failed with exit code {error.returncode}", file=sys.stderr)
        raise SystemExit(error.returncode)
