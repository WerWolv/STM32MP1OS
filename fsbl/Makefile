CROSS_COMPILER_PATH := /home/werwolv/Development/buildroot/output/host/bin
PREFIX := arm-linux-

ARM_GCC := $(CROSS_COMPILER_PATH)/$(PREFIX)gcc
ARM_G++ := $(CROSS_COMPILER_PATH)/$(PREFIX)g++
ARM_OBJCOPY := $(CROSS_COMPILER_PATH)/$(PREFIX)objcopy
ARM_LD := $(CROSS_COMPILER_PATH)/$(PREFIX)ld


SOURCE_DIR := source
BUILD_DIR := build

NULL :=
SPACE := $(NULL) $(NULL)

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/*.c) $(wildcard $(SOURCE_DIR)/*.s)
BUILD_FILES = $(filter %.o,$(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE_FILES)) $(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES)) $(patsubst $(SOURCE_DIR)/%.s,$(BUILD_DIR)/%.o,$(SOURCE_FILES)))

CFLAGS := -nolibc -fPIE
CPPFLAGS := $(CFLAGS) -nodefaultlibs -fno-exceptions
LDFLAGS := -nostartfiles -T $(CURDIR)/linker.ld -nolibc



.PHONY: all clean

all: fsbl.stm32

clean:
	@rm -rf fsbl.stm32
	@rm -rf fsbl.bin
	@rm -rf fsbl.elf
	@rm -rf $(BUILD_DIR)

fsbl.stm32: fsbl.bin
	python3 ./fix_header.py $< $@

fsbl.bin: fsbl.elf
	$(ARM_OBJCOPY) -S -O binary $< $@

fsbl.elf: $(BUILD_FILES)
	$(ARM_LD) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(@D)
	$(ARM_G++) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s
	@mkdir -p $(@D)
	$(ARM_GCC) $(CFLAGS) -c -o $@ $<

CFLAGS += -MMD
-include $(BUILD_FILES:.o=.d)