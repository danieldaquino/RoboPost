################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update

GEN_OPTS += C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/configPkg/compiler.opt
GEN_OPTS__FLAG := @"C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/configPkg/compiler.opt"
GEN_CMDS += C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/configPkg/linker.cmd
GEN_CMDS__FLAG := -Wl,-T"C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/configPkg/linker.cmd"

ORDERED_OBJS += \
"./CC3220S_LAUNCHXL.o" \
"./main_tirtos.o" \
"./pwmled.o" \
-Wl,-T"../CC3220S_LAUNCHXL_TIRTOS.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-l:"ti/display/lib/display.am4g" \
-l:"ti/drivers/lib/drivers_cc32xx.am4g" \
-l:"third_party/fatfs/lib/fatfs.am4g" \
-l:"ti/dpl/lib/dpl_cc32xx.am4g" \
-l:"ti/devices/cc32xx/driverlib/gcc/Release/driverlib.a" \
-lgcc \
-lm \
-lnosys \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
pwmled_CC3220S_LAUNCHXL_tirtos_gcc.out \

EXE_OUTPUTS__QUOTED += \
"pwmled_CC3220S_LAUNCHXL_tirtos_gcc.out" \

BIN_OUTPUTS += \
pwmled_CC3220S_LAUNCHXL_tirtos_gcc.bin \

BIN_OUTPUTS__QUOTED += \
"pwmled_CC3220S_LAUNCHXL_tirtos_gcc.bin" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "pwmled_CC3220S_LAUNCHXL_tirtos_gcc.out" secondary-outputs

dependents:
	-cd C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug && $(MAKE) clean all

# Tool invocations
pwmled_CC3220S_LAUNCHXL_tirtos_gcc.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS) C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/libtirtos_builds_CC3220S_LAUNCHXL_release_gcc.a
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc.exe" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -march=armv7e-m -mthumb -Wl,-Map,"pwmled_CC3220S_LAUNCHXL_tirtos_gcc.map" -nostartfiles -static -Wl,--gc-sections -L"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/source" -L"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages" -L"C:/ti/simplelink_cc32xx_sdk_1_60_00_04/kernel/tirtos/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/thumb/v7e-m" -march=armv7e-m -mthumb --specs=nano.specs -o"pwmled_CC3220S_LAUNCHXL_tirtos_gcc.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

pwmled_CC3220S_LAUNCHXL_tirtos_gcc.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/ti/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-objcopy.exe" -O binary $(EXE_OUTPUTS__QUOTED) "pwmled_CC3220S_LAUNCHXL_tirtos_gcc.bin"
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "CC3220S_LAUNCHXL.o" "main_tirtos.o" "pwmled.o" 
	-$(RM) "CC3220S_LAUNCHXL.d" "main_tirtos.d" "pwmled.d" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:
C:/Users/timyu/workspace_v7/tirtos_builds_CC3220S_LAUNCHXL_release_gcc/Debug/libtirtos_builds_CC3220S_LAUNCHXL_release_gcc.a:

-include ../makefile.targets

