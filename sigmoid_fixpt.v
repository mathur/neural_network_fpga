module sigmoid_fixpt(x, sign, result);
    input   [31:0] x;
    input   sign;
    output  [31:0] result;

    reg [31:0] result_1;
    reg [31:0] sigmoid_fixpt_approx;
    reg [32:0] sigmoid_fixpt_b1;
    reg [32:0] sigmoid_fixpt_b1_0;
    reg [64:0] sigmoid_fixpt_tmp;
    reg [42:0] sigmoid_fixpt_tmp_0;
    reg [55:0] sigmoid_fixpt_div_temp;
    reg [39:0] sigmoid_fixpt_div_temp_0;
    reg [32:0] sigmoid_fixpt_add_cast;
    reg [32:0] sigmoid_fixpt_add_temp;
    reg [39:0] sigmoid_fixpt_add_cast_0;
    reg [63:0] sigmoid_fixpt_mul_temp;
    reg [64:0] sigmoid_fixpt_cast;
    reg [64:0] sigmoid_fixpt_cast_0;
    reg [31:0] sigmoid_fixpt_add_cast_1;
    reg [39:0] sigmoid_fixpt_add_cast_2;
    reg [39:0] sigmoid_fixpt_add_temp_0;
    reg [32:0] sigmoid_fixpt_add_cast_3;
    reg [32:0] sigmoid_fixpt_add_cast_4;
    reg [55:0] sigmoid_fixpt_cast_1;

    always @(x, sign) begin
        //This function computes the sigmoid of an input x
        sigmoid_fixpt_add_cast = {1'b0, x};
        sigmoid_fixpt_add_temp = 33'h000400000 + sigmoid_fixpt_add_cast;
        sigmoid_fixpt_add_cast_0 = {7'b0, sigmoid_fixpt_add_temp};
        sigmoid_fixpt_mul_temp = x * x;
        sigmoid_fixpt_cast = {sigmoid_fixpt_mul_temp, 1'b0};
        sigmoid_fixpt_cast_0 = sigmoid_fixpt_cast >>> 8'd1;
        sigmoid_fixpt_add_cast_1 = sigmoid_fixpt_cast_0[61:30];
        sigmoid_fixpt_add_cast_2 = {1'b0, {sigmoid_fixpt_add_cast_1, 7'b0000000}};
        sigmoid_fixpt_add_temp_0 = sigmoid_fixpt_add_cast_0 + sigmoid_fixpt_add_cast_2;
        sigmoid_fixpt_approx = sigmoid_fixpt_add_temp_0[38:7];
        sigmoid_fixpt_add_cast_3 = {1'b0, sigmoid_fixpt_approx};
        sigmoid_fixpt_b1 = 33'h000008000 + sigmoid_fixpt_add_cast_3;
        sigmoid_fixpt_add_cast_4 = {1'b0, sigmoid_fixpt_approx};
        sigmoid_fixpt_b1_0 = 33'h000008000 + sigmoid_fixpt_add_cast_4;
        sigmoid_fixpt_tmp = 65'h1FFFFFFFFFFFFFFFF;

        if (sign) begin
            sigmoid_fixpt_tmp = 65'h00000000000000000;
        end else if (sigmoid_fixpt_b1_0 == 33'h000000000) begin
        end else begin
            sigmoid_fixpt_cast_1 = {sigmoid_fixpt_approx, 24'b000000000000000000000000};
            if (sigmoid_fixpt_b1_0 == 31'sd0) begin
                sigmoid_fixpt_div_temp = 56'hFFFFFFFFFFFFFF;
            end else begin
                sigmoid_fixpt_div_temp = sigmoid_fixpt_cast_1 / sigmoid_fixpt_b1_0;
            end
            sigmoid_fixpt_tmp = {9'b0, sigmoid_fixpt_div_temp};
        end
        if (sign) begin
            if (sigmoid_fixpt_b1 == 33'h000000000) begin
                sigmoid_fixpt_tmp_0 = 43'h7FFFFFFFFFF;
            end else begin
                if (sigmoid_fixpt_b1 == 31'sd0) begin
                    sigmoid_fixpt_div_temp_0 = 40'hFFFFFFFFFF;
                end else begin
                    sigmoid_fixpt_div_temp_0 = 40'h8000000000 / sigmoid_fixpt_b1;
                end
                sigmoid_fixpt_tmp_0 = {3'b0, sigmoid_fixpt_div_temp_0};
            end
        end else begin
            sigmoid_fixpt_tmp_0 = 43'h00000000000;
        end
        if (sign) begin
            result_1 = {sigmoid_fixpt_tmp_0[24:0], 7'b0000000};
        end else begin
            result_1 = {sigmoid_fixpt_tmp[24:0], 7'b0000000};
        end
    end

    assign result = result_1;

endmodule  // sigmoid_fixpt

