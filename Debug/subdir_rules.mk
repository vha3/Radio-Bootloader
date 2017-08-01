################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
LCD1x9.obj: ../LCD1x9.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="LCD1x9.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cc430radio.obj: ../cc430radio.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="cc430radio.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pmm.obj: ../pmm.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="pmm.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rf1a.obj: ../rf1a.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="rf1a.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

wiring_analog.obj: ../wiring_analog.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="wiring_analog.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

wiring_digital.obj: ../wiring_digital.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="/Applications/ccsv7/ccs_base/msp430/include" --include_path="/Applications/ccsv7/tools/compiler/ti-cgt-msp430_16.9.3.LTS/include" --advice:power=all -g --define=__CC430F5137__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU15 --silicon_errata=CPU18 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="wiring_digital.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


