###########################################################################
# SDC files for DE2-70 board
###########################################################################

# Clock in input pin (50 MHz)
create_clock -period 20 [get_ports clk]
#create_clock -period 20 [get_ports oSram_CLK]

# Create generated clocks based on PLLs
derive_pll_clocks -use_tan_name

derive_clock_uncertainty

# ** Input/Output Delays

# Use FPGA-centric constraints (general pins)
# Tsu 5 ns
#set_max_delay -from [all_inputs] -to [all_registers] 5
#set_min_delay -from [all_inputs] -to [all_registers] 0
# Tco 10 ns
#set_max_delay -from [all_registers] -to [all_outputs] 10
#set_min_delay -from [all_registers] -to [all_outputs] 0

# Use FPGA-centric constraints (SRAM pins)
# Tsu 2 ns
#set_max_delay -from [get_ports *ram*] -to [get_registers {*}] 2
# Tco 2 ns
#set_max_delay -from [get_registers *] -to [get_ports {*ram*}] 2

#set_input_delay -clock [get_clocks {*pll:pll_inst*clk_sram}] -max 2 [get_ports {*ram*}] 
#set_input_delay -clock [get_clocks {*pll:pll_inst*clk_sram}] -min 0 [get_ports {*ram*}]

#set_output_delay -clock [get_clocks {*pll:pll_inst*clk_sram}] -max 2 [get_ports {*ram*}] 
#set_output_delay -clock [get_clocks {*pll:pll_inst*clk_sram}] -min 0 [get_ports {*ram*}]

# ssram clk derived from clk1 of pll_inst
#set_min_delay 0 -from [get_clocks {*pll:pll_inst*clk_sram}] -to [get_ports {oSram_CLK}]
#set_max_delay 3 -from [get_clocks {*pll:pll_inst*clk_sram}] -to [get_ports {oSram_CLK}]

#set_multicycle_path -from [get_clocks {*pll:pll_inst*clk_sram}] -to [get_clocks {*pll:pll_inst*clk_int}] -setup -end 2