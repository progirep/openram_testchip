# SPDX-FileCopyrightText: 2020 Efabless Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# SPDX-License-Identifier: Apache-2.0

# Base Configurations. Don't Touch
# section begin

set ::env(PDK) "sky130A"
set ::env(STD_CELL_LIBRARY) "sky130_fd_sc_hd"

# YOU ARE NOT ALLOWED TO CHANGE ANY VARIABLES DEFINED IN THE FIXED WRAPPER CFGS 
source $::env(CARAVEL_ROOT)/openlane/user_project_wrapper/fixed_wrapper_cfgs.tcl

# YOU CAN CHANGE ANY VARIABLES DEFINED IN THE DEFAULT WRAPPER CFGS BY OVERRIDING THEM IN THIS CONFIG.TCL
source $::env(CARAVEL_ROOT)/openlane/user_project_wrapper/default_wrapper_cfgs.tcl

set script_dir [file dirname [file normalize [info script]]]

set ::env(DESIGN_NAME) user_project_wrapper
#section end

# User Configurations

## Source Verilog Files
set ::env(VERILOG_FILES) "\
	$::env(CARAVEL_ROOT)/verilog/rtl/defines.v \
	$script_dir/../../verilog/rtl/user_project_wrapper.v"


## Clock configurations
set ::env(CLOCK_PORT) "user_clock2"
set ::env(CLOCK_NET) "CONTROL_LOGIC.clk"

set ::env(CLOCK_PERIOD) "10"

## Internal Macros
### Macro PDN Connections
# set ::env(FP_PDN_MACRO_HOOKS) "\
#	prj vccd1 vssd1 \
#	SRAM1 vccd1 vssd1 \	
#	SRAM12 vccd1 vssd1"



### Macro Placement
set ::env(MACRO_PLACEMENT_CFG) $script_dir/macro.cfg

### Black-box verilog and views
set ::env(VERILOG_FILES_BLACKBOX) "\
	$::env(CARAVEL_ROOT)/verilog/rtl/defines.v \
	$script_dir/../../verilog/rtl/user_project.v \
	$script_dir/../../verilog/rtl/monitor.v \
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/verilog/sky130_sram_2kbyte_1rw1r_32x512_8.v \
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/verilog/sky130_sram_1kbyte_1rw1r_32x256_8.v"

set ::env(EXTRA_LEFS) "\
	$script_dir/../../lef/user_project.lef \
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/lef/sky130_sram_2kbyte_1rw1r_32x512_8.lef \ 
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/lef/sky130_sram_1kbyte_1rw1r_32x256_8.lef"

set ::env(EXTRA_GDS_FILES) "\
	$script_dir/../../gds/user_project.gds \
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/gds/sky130_sram_2kbyte_1rw1r_32x512_8.gds \
        $::env(PDK_ROOT)/sky130A/libs.ref/sky130_sram_macros/gds/sky130_sram_1kbyte_1rw1r_32x256_8.gds"


# set ::env(GLB_RT_MAXLAYER) 5
set ::env(RT_MAX_LAYER) {met4}

# disable pdn check nodes becuase it hangs with multiple power domains.
# any issue with pdn connections will be flagged with LVS so it is not a critical check.
set ::env(FP_PDN_CHECK_NODES) 0

# The following is because there are no std cells in the example wrapper project.
set ::env(SYNTH_TOP_LEVEL) 1
set ::env(PL_RANDOM_GLB_PLACEMENT) 1

set ::env(PL_RESIZER_DESIGN_OPTIMIZATIONS) 0
set ::env(PL_RESIZER_TIMING_OPTIMIZATIONS) 0
set ::env(PL_RESIZER_BUFFER_INPUT_PORTS) 0
set ::env(PL_RESIZER_BUFFER_OUTPUT_PORTS) 0

# set ::env(MACRO_PLACE_HALO) 4
# set ::env(MACRO_PLACE_CHANNEL) "100 100"


# set ::env(GLB_RT_OBS) "li1 1600.00 1850.00 2240.0 2264.0,  \
#	               		met1 1600.00 1850.00 2240.0 2264.0, \
#	               		met2 1600.00 1850.00 2240.0 2264.0, \
#	              		met3 1600.00 1850.00 2240.0 2264.0, \
#	              		met4 1600.00 1850.00 2240.0 2264.0, \
#		       			met5 0 0 2920 3520 "


# set ::env(GLB_RT_ALLOW_CONGESTION) "1"

#Reduction in the routing capacity of the edges between the cells in the global routing graph. Values range from 0 to 1.
#1 = most reduction, 0 = least reduction 
set ::env(GLB_RT_LAYER_ADJUSTMENTS) 0.8,0.8,0.7,0,0,0

# Not too many iterations
set ::env(DRT_OPT_ITERS) 30

# per layer adjustment
# 0 -> 1: 1 means don't use the layer                                                        
# l2 is met1                                                                                 

set ::env(FP_PDN_ENABLE_RAILS) 0

set ::env(SYNTH_USE_PG_PINS_DEFINES) "USE_POWER_PINS"

# set ::env(VDD_NETS) "vccd1 vccd2 vdda1 vdda2"
# set ::env(GND_NETS) "vssd1 vssd2 vssa1 vssa2"

# 16 GB of RAM aren't enough for magic DRC. KLayout DRC only works with some changes to scripts
set ::env(RUN_MAGIC_DRC) 0

set ::env(DIODE_INSERTION_STRATEGY) 0
set ::env(FILL_INSERTION) 0
set ::env(TAP_DECAP_INSERTION) 0
set ::env(CLOCK_TREE_SYNTH) 0
