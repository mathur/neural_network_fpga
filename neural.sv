module neural(
	input  [31:0] x,
	input	        CLOCK_50,
	input  [3:0]  KEY,
	input  [7:0]  SW,
	output [7:0]  LEDG,
	output [12:0] DRAM_ADDR,
	output [1:0]  DRAM_BA,
	output        DRAM_CAS_N,
	output		  DRAM_CKE,
	output		  DRAM_CS_N,
	output [3:0]  DRAM_DQM,
	output		  DRAM_RAS_N,
	output		  DRAM_WE_N,
	output		  DRAM_CLK,
	output [31:0] result,
	inout  [31:0] DRAM_DQ
);

    logic [ 31:0] to_sw_port;   // data
    logic [ 31:0] to_hw_port;
	// enum logic [6:0] {SEND, RECIEVE} state, next_state;

	spu spu_proc(
		.x_float(to_hw_port),
		.y_float(to_sw_port)
	);
	
	neural_soc m_neural_soc(
		.clk_clk(CLOCK_50),
		.reset_reset_n(KEY[0]), 
		.led_wire_export(LEDG),
		.sdram_wire_addr(DRAM_ADDR),     //  sdram_wire.addr
		.sdram_wire_ba(DRAM_BA),      	//  .ba
		.sdram_wire_cas_n(DRAM_CAS_N),   //  .cas_n
		.sdram_wire_cke(DRAM_CKE),     	//  .cke
		.sdram_wire_cs_n(DRAM_CS_N),     //  .cs_n
		.sdram_wire_dq(DRAM_DQ),      	//  .dq
		.sdram_wire_dqm(DRAM_DQM),     	//  .dqm
		.sdram_wire_ras_n(DRAM_RAS_N),   //  .ras_n
		.sdram_wire_we_n(DRAM_WE_N),     //  .we_n
		.sdram_clk_clk(DRAM_CLK),			//  clock out to SDRAM from other PLL port
		.switch_wire_export(SW[7:0]),
		.to_hw_port_export(to_hw_port),
		.to_sw_port_export(to_sw_port),
		.key_wire_export(KEY[3:0])
	);

endmodule
