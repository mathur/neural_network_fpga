# Legal Notice: (C)2016 Altera Corporation. All rights reserved.  Your
# use of Altera Corporation's design tools, logic functions and other
# software and tools, and its AMPP partner logic functions, and any
# output files any of the foregoing (including device programming or
# simulation files), and any associated documentation or information are
# expressly subject to the terms and conditions of the Altera Program
# License Subscription Agreement or other applicable license agreement,
# including, without limitation, that your use is for the sole purpose
# of programming logic devices manufactured by Altera and sold by Altera
# or its authorized distributors.  Please refer to the applicable
# agreement for further details.

#**************************************************************
# Timequest JTAG clock definition
#   Uncommenting the following lines will define the JTAG
#   clock in TimeQuest Timing Analyzer
#**************************************************************

#create_clock -period 10MHz {altera_reserved_tck}
#set_clock_groups -asynchronous -group {altera_reserved_tck}

#**************************************************************
# Set TCL Path Variables 
#**************************************************************

set 	neural_soc_nios2_gen2_0_cpu 	neural_soc_nios2_gen2_0_cpu:*
set 	neural_soc_nios2_gen2_0_cpu_oci 	neural_soc_nios2_gen2_0_cpu_nios2_oci:the_neural_soc_nios2_gen2_0_cpu_nios2_oci
set 	neural_soc_nios2_gen2_0_cpu_oci_break 	neural_soc_nios2_gen2_0_cpu_nios2_oci_break:the_neural_soc_nios2_gen2_0_cpu_nios2_oci_break
set 	neural_soc_nios2_gen2_0_cpu_ocimem 	neural_soc_nios2_gen2_0_cpu_nios2_ocimem:the_neural_soc_nios2_gen2_0_cpu_nios2_ocimem
set 	neural_soc_nios2_gen2_0_cpu_oci_debug 	neural_soc_nios2_gen2_0_cpu_nios2_oci_debug:the_neural_soc_nios2_gen2_0_cpu_nios2_oci_debug
set 	neural_soc_nios2_gen2_0_cpu_wrapper 	neural_soc_nios2_gen2_0_cpu_debug_slave_wrapper:the_neural_soc_nios2_gen2_0_cpu_debug_slave_wrapper
set 	neural_soc_nios2_gen2_0_cpu_jtag_tck 	neural_soc_nios2_gen2_0_cpu_debug_slave_tck:the_neural_soc_nios2_gen2_0_cpu_debug_slave_tck
set 	neural_soc_nios2_gen2_0_cpu_jtag_sysclk 	neural_soc_nios2_gen2_0_cpu_debug_slave_sysclk:the_neural_soc_nios2_gen2_0_cpu_debug_slave_sysclk
set 	neural_soc_nios2_gen2_0_cpu_oci_path 	 [format "%s|%s" $neural_soc_nios2_gen2_0_cpu $neural_soc_nios2_gen2_0_cpu_oci]
set 	neural_soc_nios2_gen2_0_cpu_oci_break_path 	 [format "%s|%s" $neural_soc_nios2_gen2_0_cpu_oci_path $neural_soc_nios2_gen2_0_cpu_oci_break]
set 	neural_soc_nios2_gen2_0_cpu_ocimem_path 	 [format "%s|%s" $neural_soc_nios2_gen2_0_cpu_oci_path $neural_soc_nios2_gen2_0_cpu_ocimem]
set 	neural_soc_nios2_gen2_0_cpu_oci_debug_path 	 [format "%s|%s" $neural_soc_nios2_gen2_0_cpu_oci_path $neural_soc_nios2_gen2_0_cpu_oci_debug]
set 	neural_soc_nios2_gen2_0_cpu_jtag_tck_path 	 [format "%s|%s|%s" $neural_soc_nios2_gen2_0_cpu_oci_path $neural_soc_nios2_gen2_0_cpu_wrapper $neural_soc_nios2_gen2_0_cpu_jtag_tck]
set 	neural_soc_nios2_gen2_0_cpu_jtag_sysclk_path 	 [format "%s|%s|%s" $neural_soc_nios2_gen2_0_cpu_oci_path $neural_soc_nios2_gen2_0_cpu_wrapper $neural_soc_nios2_gen2_0_cpu_jtag_sysclk]
set 	neural_soc_nios2_gen2_0_cpu_jtag_sr 	 [format "%s|*sr" $neural_soc_nios2_gen2_0_cpu_jtag_tck_path]

#**************************************************************
# Set False Paths
#**************************************************************

set_false_path -from [get_keepers *$neural_soc_nios2_gen2_0_cpu_oci_break_path|break_readreg*] -to [get_keepers *$neural_soc_nios2_gen2_0_cpu_jtag_sr*]
set_false_path -from [get_keepers *$neural_soc_nios2_gen2_0_cpu_oci_debug_path|*resetlatch]     -to [get_keepers *$neural_soc_nios2_gen2_0_cpu_jtag_sr[33]]
set_false_path -from [get_keepers *$neural_soc_nios2_gen2_0_cpu_oci_debug_path|monitor_ready]  -to [get_keepers *$neural_soc_nios2_gen2_0_cpu_jtag_sr[0]]
set_false_path -from [get_keepers *$neural_soc_nios2_gen2_0_cpu_oci_debug_path|monitor_error]  -to [get_keepers *$neural_soc_nios2_gen2_0_cpu_jtag_sr[34]]
set_false_path -from [get_keepers *$neural_soc_nios2_gen2_0_cpu_ocimem_path|*MonDReg*] -to [get_keepers *$neural_soc_nios2_gen2_0_cpu_jtag_sr*]
set_false_path -from *$neural_soc_nios2_gen2_0_cpu_jtag_sr*    -to *$neural_soc_nios2_gen2_0_cpu_jtag_sysclk_path|*jdo*
set_false_path -from sld_hub:*|irf_reg* -to *$neural_soc_nios2_gen2_0_cpu_jtag_sysclk_path|ir*
set_false_path -from sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1] -to *$neural_soc_nios2_gen2_0_cpu_oci_debug_path|monitor_go
