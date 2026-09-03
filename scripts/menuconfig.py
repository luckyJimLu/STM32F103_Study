#!/usr/bin/env python3
"""Kconfig frontend and deterministic build configuration generator."""

from __future__ import annotations

import argparse
import os
from pathlib import Path
import subprocess
import sys


PROJECT_ROOT = Path(__file__).resolve().parent.parent
KCONFIG_PATH = PROJECT_ROOT / "Kconfig"
DEFAULT_DOTCONFIG = PROJECT_ROOT / ".config"
DEFAULT_OUTPUT_DIR = PROJECT_ROOT / "build" / "generated"


def ensure_dependencies(gui: bool) -> None:
    try:
        __import__("kconfiglib")
        __import__("guiconfig" if gui else "menuconfig")
    except ImportError:
        packages = ["kconfiglib"]
        if os.name == "nt" and not gui:
            packages.append("windows-curses")
        print(">> [INFO] Installing required Kconfig frontend packages...")
        subprocess.check_call([sys.executable, "-m", "pip", "install", *packages])


def write_outputs(kconf, output_dir: Path) -> None:
    import kconfiglib

    output_dir.mkdir(parents=True, exist_ok=True)
    autoconf_path = output_dir / "autoconf.h"
    cmake_path = output_dir / "kconfig.cmake"
    kconf.write_autoconf(str(autoconf_path))

    lines = ["# Automatically generated. DO NOT EDIT.", ""]
    for sym in kconf.unique_defined_syms:
        name = f"CONFIG_{sym.name}"
        if sym.str_value == "y":
            lines.append(f'set({name} ON CACHE INTERNAL "Kconfig option" FORCE)')
        elif sym.str_value == "n":
            lines.append(f'set({name} OFF CACHE INTERNAL "Kconfig option" FORCE)')
        elif sym.type in (kconfiglib.INT, kconfiglib.HEX):
            lines.append(
                f'set({name} {sym.str_value} CACHE INTERNAL "Kconfig option" FORCE)'
            )
        elif sym.type == kconfiglib.STRING:
            escaped = sym.str_value.replace("\\", "\\\\").replace('"', '\\"')
            lines.append(
                f'set({name} "{escaped}" CACHE INTERNAL "Kconfig option" FORCE)'
            )

    cmake_path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f">> Generated: {autoconf_path}")
    print(f">> Generated: {cmake_path}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--gui", action="store_true", help="use the graphical frontend")
    parser.add_argument("--sync", action="store_true", help="generate outputs without opening a UI")
    parser.add_argument("--config", type=Path, default=DEFAULT_DOTCONFIG)
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.gui and args.sync:
        raise SystemExit("--gui and --sync are mutually exclusive")

    ensure_dependencies(args.gui)
    import kconfiglib

    config_path = args.config.resolve()
    output_dir = args.output_dir.resolve()
    os.chdir(PROJECT_ROOT)
    os.environ["KCONFIG_CONFIG"] = str(config_path)

    kconf = kconfiglib.Kconfig(str(KCONFIG_PATH), warn_to_stderr=True)
    if config_path.exists():
        kconf.load_config(str(config_path))
    elif args.sync:
        raise SystemExit(f"configuration file does not exist: {config_path}")

    if not args.sync:
        if args.gui:
            import guiconfig

            guiconfig.menuconfig(kconf)
        else:
            import menuconfig

            menuconfig.menuconfig(kconf)
        config_path.parent.mkdir(parents=True, exist_ok=True)
        kconf.write_config(str(config_path))
        print(f">> Saved configuration: {config_path}")

    write_outputs(kconf, output_dir)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
