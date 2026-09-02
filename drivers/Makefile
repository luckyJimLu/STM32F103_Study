# ==============================================================================
# drivers/Makefile
# ==============================================================================

TOPDIR ?= ..
include $(TOPDIR)/Make.defs
include Make.defs

OBJS = $(addprefix $(BUILD_DIR)/, $(CSRCS:.c=.o)) $(addprefix $(BUILD_DIR)/, $(ASRCS:.s=.o))

all: $(OBJS)

.PHONY: all
