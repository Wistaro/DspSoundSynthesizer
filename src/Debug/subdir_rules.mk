################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/lib/bsl" --define=c5535 --display_error_number --diag_warning=225 --gen_func_subsections=off --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sound.obj: ../sound.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/lib/bsl" --define=c5535 --display_error_number --diag_warning=225 --gen_func_subsections=off --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="sound.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: ../uart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv6/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="C:/ti/ccsv6/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/c55xx_csl/inc" --include_path="C:/Users/Willliam/Documents/electronics/dsp/ezdsp5535_v1/lib/bsl" --define=c5535 --display_error_number --diag_warning=225 --gen_func_subsections=off --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="uart.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


