transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/neural_network_fpga {C:/neural_network_fpga/sigmoid_fixpt.v}
vlog -sv -work work +incdir+C:/neural_network_fpga {C:/neural_network_fpga/spu_pre.sv}
vlog -sv -work work +incdir+C:/neural_network_fpga {C:/neural_network_fpga/neural.sv}
vlog -sv -work work +incdir+C:/neural_network_fpga {C:/neural_network_fpga/spu_post.sv}
vlib neural_soc
vmap neural_soc neural_soc

