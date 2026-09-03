# Convenience wrapper. CMakePresets.json is the only build definition.

PRESET ?= configured-debug
ifeq ($(OS),Windows_NT)
PYTHON ?= python
CMAKE ?= tools/cmake/bin/cmake.exe
FLASH_COMMAND = scripts/flash.bat $(PRESET)
else
PYTHON ?= python3
CMAKE ?= cmake
FLASH_COMMAND = ./scripts/flash.sh $(PRESET)
endif

.PHONY: all build matrix menuconfig guiconfig flash clean

all: build

build:
	$(CMAKE) --preset $(PRESET)
	$(CMAKE) --build --preset $(PRESET) --parallel

matrix:
	$(PYTHON) scripts/build_matrix.py

menuconfig:
	$(PYTHON) scripts/menuconfig.py

guiconfig:
	$(PYTHON) scripts/menuconfig.py --gui

flash:
	$(FLASH_COMMAND)

clean:
	$(CMAKE) -E remove_directory build/out
