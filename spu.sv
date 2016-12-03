module spu (
    input   logic [31:0] x_float,
    output  logic [31:0] y_float
);

    spu_pre preprocessor (
        .x_float,
        .x_sign, .x_fixpt
    );

    logic [31:0] x_fixpt;
    logic        x_sign;

    sigmoid_fixpt sigmoid(
        .x(x_fixpt), .sign(x_sign),
        .result(y_fixpt)
    );

    logic [31:0] y_fixpt;

    spu_post postprocessor (
        .x_fixed(y_fixpt),
        .x_float(y_float)
    );

endmodule
