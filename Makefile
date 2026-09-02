# ==============================================================================
# Top-level Makefile for STM32F103 Project
# ==============================================================================

TARGET = STM32F103_Study
TOPDIR = $(CURDIR)

include $(TOPDIR)/Make.defs

# Gather source files and includes from all subsystems
CSRCS =
ASRCS =

include app/Make.defs
include bsp/Make.defs
include drivers/Make.defs
include middlewares/Make.defs
include third_party/Make.defs

# Convert include dirs into -I flags
INC_FLAGS = $(addprefix -I, $(INCDIRS))
CFLAGS   += $(INC_FLAGS)
CXXFLAGS += $(INC_FLAGS)
ASFLAGS  += $(INC_FLAGS)

# Object files
COBJS = $(addprefix $(BUILD_DIR)/, $(CSRCS:.c=.o))
AOBJS = $(addprefix $(BUILD_DIR)/, $(ASRCS:.s=.o))
ALL_OBJS = $(COBJS) $(AOBJS)

.PHONY: all menuconfig guiconfig clean flash info

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	@echo ">> Build completed successfully!"
	@$(SIZE) --format=berkeley $<

# Compile C source files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo ">> CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile ASM source files
$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo ">> AS $<"
	@$(AS) $(ASFLAGS) -c $< -o $@

# Link ELF
$(BUILD_DIR)/$(TARGET).elf: $(ALL_OBJS)
	@mkdir -p $(dir $@)
	@echo ">> Linking $@ ..."
	@$(CC) $(ALL_OBJS) $(LDFLAGS) -o $@

# Output HEX
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@$(OBJCOPY) -O ihex $< $@

# Output BIN
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@$(OBJCOPY) -O binary -S $< $@

# Visual Menu Configuration
menuconfig:
	@python scripts/menuconfig.py

guiconfig:
	@python scripts/menuconfig.py --gui

clean:
	@rm -rf $(BUILD_DIR)
	@echo ">> Cleaned build directory."

flash: $(BUILD_DIR)/$(TARGET).elf
	@openocd -f scripts/openocd_stlink.cfg -c "program $< verify reset exit"
