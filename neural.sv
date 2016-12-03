module neural(
	input logic [31:0] x,
	output logic [31:0] result
);

	logic				sign_in;
	logic	[31:0]	fixed_pt_in;
	logic [31:0]	fixed_pt_out;

	spu_pre preprocessor (
		.x_float(x),
		.x_sign(sign_in), .x_fixpt(fixed_pt_in)
	);

	sigmoid_fixpt sigmoid(
		.x(fixed_pt_in), .sign(sign_in),
		.result(fixed_pt_out)
	);
	
	spu_post postprocessor (
		.x_fixed(fixed_pt_out),
		.x_float(result)
	);

endmodule
