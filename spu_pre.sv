module spu_pre(
	input  logic	[31:0]	x_float,
	output logic 				x_sign,
	output logic	[31:0]	x_fixpt
);

	logic 			[31:0]	mantissa;

	logic signed	[8:0]		bitshift;
	logic signed	[8:0]		exponent;

	always_comb
	begin
		// sign bit
		x_sign = x_float[31];

		mantissa = {1'b1, x_float[22:0], 8'b0};

		exponent = {1'b0, x_float[30:23]};
		bitshift = 136 - exponent; // 10 - (exponent - 127 + 1)
		
		if(bitshift < 0) begin
			x_fixpt = 32'b1111_1111_1111_1111_1111_1111_1111_1111;
		end else if (bitshift >= 32) begin
			x_fixpt = 32'b0000_0000_0000_0000_0000_0000_0000_0000;
		end else begin
			unique case(bitshift[4:0])
				5'b00000: x_fixpt = mantissa >> 0;
				5'b00001: x_fixpt = mantissa >> 1;
				5'b00010: x_fixpt = mantissa >> 2;
				5'b00011: x_fixpt = mantissa >> 3;
				
				5'b00100: x_fixpt = mantissa >> 4;
				5'b00101: x_fixpt = mantissa >> 5;
				5'b00110: x_fixpt = mantissa >> 6;
				5'b00111: x_fixpt = mantissa >> 7;

				5'b01000: x_fixpt = mantissa >> 8;
				5'b01001: x_fixpt = mantissa >> 9;
				5'b01010: x_fixpt = mantissa >> 10;
				5'b01011: x_fixpt = mantissa >> 11;
				
				5'b01100: x_fixpt = mantissa >> 12;
				5'b01101: x_fixpt = mantissa >> 13;
				5'b01110: x_fixpt = mantissa >> 14;
				5'b01111: x_fixpt = mantissa >> 15;
				
				5'b10000: x_fixpt = mantissa >> 16;
				5'b10001: x_fixpt = mantissa >> 17;
				5'b10010: x_fixpt = mantissa >> 18;
				5'b10011: x_fixpt = mantissa >> 19;
				
				5'b10100: x_fixpt = mantissa >> 20;
				5'b10101: x_fixpt = mantissa >> 21;
				5'b10110: x_fixpt = mantissa >> 22;
				5'b10111: x_fixpt = mantissa >> 23;
				
				5'b11000: x_fixpt = mantissa >> 24;
				5'b11001: x_fixpt = mantissa >> 25;
				5'b11010: x_fixpt = mantissa >> 26;
				5'b11011: x_fixpt = mantissa >> 27;
				
				5'b11100: x_fixpt = mantissa >> 28;
				5'b11101: x_fixpt = mantissa >> 29;
				5'b11110: x_fixpt = mantissa >> 30;
				5'b11111: x_fixpt = mantissa >> 31;
			endcase
		end
	end

endmodule
