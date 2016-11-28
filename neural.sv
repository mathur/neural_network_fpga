module neural(
	input logic [31:0] x,
	output logic [31:0] result,
	output logic [31:0] y
);

	sigmoid_fixpt sigmoid(
	.x_1(x),
	.result(result)
	);
	
	assign y = 1 - x;

endmodule
