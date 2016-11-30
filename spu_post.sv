module spu_post(
	input		logic	[31:0]	x_fixed,
	output	logic	[31:0]	x_float
);

	assign x_float[31] = 1'b0;

	always_comb begin
		if(x_fixed[31] == 1'b1) begin
			x_float[30:23] = 127;
			x_float[22: 0] = x_fixed[30:8];
		end else if (x_fixed[30] == 1'b1) begin
			x_float[30:23] = 126;
			x_float[22: 0] = x_fixed[29:7];
		end else if (x_fixed[29] == 1'b1) begin
			x_float[30:23] = 125;
			x_float[22: 0] = x_fixed[28:6];
		end else if (x_fixed[28] == 1'b1) begin
			x_float[30:23] = 124;
			x_float[22: 0] = x_fixed[27:5];
		end else if (x_fixed[27] == 1'b1) begin
			x_float[30:23] = 123;
			x_float[22: 0] = x_fixed[26:4];
		end else if (x_fixed[26] == 1'b1) begin
			x_float[30:23] = 122;
			x_float[22: 0] = x_fixed[25:3];
		end else if (x_fixed[25] == 1'b1) begin
			x_float[30:23] = 121;
			x_float[22: 0] = x_fixed[24:2];
		end else if (x_fixed[24] == 1'b1) begin
			x_float[30:23] = 120;
			x_float[22: 0] = x_fixed[23:1];
		end else if (x_fixed[23] == 1'b1) begin
			x_float[30:23] = 119;
			x_float[22: 0] = x_fixed[22:0];
		end else if (x_fixed[22] == 1'b1) begin
			x_float[30:23] = 118;
			x_float[22: 0] = {x_fixed[21:0], 1'b0};
		end else if (x_fixed[21] == 1'b1) begin
			x_float[30:23] = 117;
			x_float[22: 0] = {x_fixed[20:0], 2'b0};
		end else if (x_fixed[20] == 1'b1) begin
			x_float[30:23] = 116;
			x_float[22: 0] = {x_fixed[19:0], 3'b0};
		end else if (x_fixed[19] == 1'b1) begin
			x_float[30:23] = 115;
			x_float[22: 0] = {x_fixed[18:0], 4'b0};
		end else if (x_fixed[18] == 1'b1) begin
			x_float[30:23] = 114;
			x_float[22: 0] = {x_fixed[17:0], 5'b0};
		end else if (x_fixed[17] == 1'b1) begin
			x_float[30:23] = 113;
			x_float[22: 0] = {x_fixed[16:0], 6'b0};
		end else if (x_fixed[16] == 1'b1) begin
			x_float[30:23] = 112;
			x_float[22: 0] = {x_fixed[15:0], 7'b0};
		end else if (x_fixed[15] == 1'b1) begin
			x_float[30:23] = 111;
			x_float[22: 0] = {x_fixed[14:0], 8'b0};
		end else if (x_fixed[14] == 1'b1) begin
			x_float[30:23] = 110;
			x_float[22: 0] = {x_fixed[13:0], 9'b0};
		end else if (x_fixed[13] == 1'b1) begin
			x_float[30:23] = 109;
			x_float[22: 0] = {x_fixed[12:0], 10'b0};
		end else if (x_fixed[12] == 1'b1) begin
			x_float[30:23] = 108;
			x_float[22: 0] = {x_fixed[11:0], 11'b0};
		end else if (x_fixed[11] == 1'b1) begin
			x_float[30:23] = 107;
			x_float[22: 0] = {x_fixed[10:0], 12'b0};
		end else if (x_fixed[10] == 1'b1) begin
			x_float[30:23] = 106;
			x_float[22: 0] = {x_fixed[ 9:0], 13'b0};
		end else if (x_fixed[9] == 1'b1) begin
			x_float[30:23] = 105;
			x_float[22: 0] = {x_fixed[ 8:0], 14'b0};
		end else if (x_fixed[8] == 1'b1) begin
			x_float[30:23] = 104;
			x_float[22: 0] = {x_fixed[ 7:0], 15'b0};
		end else if (x_fixed[7] == 1'b1) begin
			x_float[30:23] = 103;
			x_float[22: 0] = {x_fixed[ 6:0], 16'b0};
		end else if (x_fixed[6] == 1'b1) begin
			x_float[30:23] = 102;
			x_float[22: 0] = {x_fixed[ 5:0], 17'b0};
		end else if (x_fixed[5] == 1'b1) begin
			x_float[30:23] = 101;
			x_float[22: 0] = {x_fixed[ 4:0], 18'b0};
		end else if (x_fixed[4] == 1'b1) begin
			x_float[30:23] = 100;
			x_float[22: 0] = {x_fixed[ 3:0], 19'b0};
		end else if (x_fixed[3] == 1'b1) begin
			x_float[30:23] = 99;
			x_float[22: 0] = {x_fixed[ 2:0], 20'b0};
		end else if (x_fixed[2] == 1'b1) begin
			x_float[30:23] = 98;
			x_float[22: 0] = {x_fixed[ 1:0], 21'b0};
		end else if (x_fixed[1] == 1'b1) begin
			x_float[30:23] = 97;
			x_float[22: 0] = {x_fixed[0], 22'b0};
		end else if (x_fixed[0] == 1'b1) begin
			x_float[30:23] = 96;
			x_float[22:0]  = 0;
		end else begin
			x_float[30:23] = 0;
			x_float[22:0]  = 0;
		end
	end

endmodule
