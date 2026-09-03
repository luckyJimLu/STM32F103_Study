# Product board profiles

Each product owns its MCU selection, clock source, memory limits, board pinout,
linker settings and reproducible system configurations. Application and BSP
code must use `product_config.h` instead of testing MCU package macros directly.

The committed `configs/*_defconfig` files are build inputs. The root `.config`
is a developer-local menuconfig selection and is intentionally not committed.
