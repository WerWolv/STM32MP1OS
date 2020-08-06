TOPDIR ?= $(CURDIR)

CROSS_COMPILER_PATH := /home/werwolv/Development/buildroot/output/host/bin
PREFIX 				:= arm-linux-

ARM_GCC 		:= $(CROSS_COMPILER_PATH)/$(PREFIX)gcc
ARM_G++ 		:= $(CROSS_COMPILER_PATH)/$(PREFIX)g++
ARM_OBJCOPY 	:= $(CROSS_COMPILER_PATH)/$(PREFIX)objcopy
ARM_LD 			:= $(CROSS_COMPILER_PATH)/$(PREFIX)ld


TOPDIR ?= $(CURDIR)

BUILD			:=	build
SOURCES_TOP		:=	source
SOURCES			+=  $(foreach dir,$(SOURCES_TOP),$(shell find $(dir) -type d 2>/dev/null))
INCLUDES		:=	include

ARCH		:=	-fPIE

null      	:=
SPACE     	:=  $(null) $(null)

DEFINES 	+= -DCORE_CA7 -DSTM32MP157Cxx

COMMONFLAGS	:=  -g -O3 -ffunction-sections -fPIE \
				$(ARCH) $(DEFINES) 				 \
				$(INCLUDE)

CFLAGS		:=	$(COMMONFLAGS)

CPPFLAGS	:=  $(COMMONFLAGS) -std=gnu++2a -fno-exceptions

ASFLAGS		:=	-g $(ARCH)
LDFLAGS		:=	-g -nostdlib -nostartfiles -T $(TOPDIR)/linker.ld


ifneq ($(BUILD),$(notdir $(CURDIR)))

export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))


export OFILES 		:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE		:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
						$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
						-I$(CURDIR)/$(BUILD)


.PHONY: $(BUILD) clean all

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@ $(BUILD)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	rm -fr $(BUILD) $(TOPDIR)/fsbl.stm32

else

.PHONY:	all

DEPENDS	:=	$(OFILES:.o=.d)

all: $(TOPDIR)/fsbl.stm32

$(TOPDIR)/fsbl.stm32: fsbl.bin
	python3 $(TOPDIR)/fix_header.py $< $@

fsbl.bin: fsbl.elf
	$(ARM_OBJCOPY) -S -O binary $< $@

fsbl.elf: $(OFILES)

%.o: %.cpp
	@mkdir -p $(@D)
	$(ARM_G++) -MMD -MP -MF $*.d $(CPPFLAGS) -c $< -o $@

%.o: %.c
	@mkdir -p $(@D)
	$(ARM_GCC) -MMD -MP -MF $*.d $(CFLAGS) -c $< -o $@

%.o: %.s
	@mkdir -p $(@D)
	$(ARM_GCC) -MMD -MP -MF $*.d -x assembler-with-cpp $(ASFLAGS) -c $< -o $@

%.elf:
	$(ARM_LD) $(LDFLAGS) $(OFILES) -o $@

-include $(DEPENDS)

endif