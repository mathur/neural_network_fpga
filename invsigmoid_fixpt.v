module invsigmoid_fixpt
          (
           x,
           sign,
           result
          );



  input   [31:0] x;  // ufix32_En22
  input   sign;
  output  [31:0] result;  // ufix32_En31

  reg [31:0] result_1;
  reg [31:0] invsigmoid_fixpt_approx;
  reg [32:0] invsigmoid_fixpt_b1;
  reg [32:0] invsigmoid_fixpt_b1_0;
  reg [64:0] invsigmoid_fixpt_tmp;
  reg [31:0] invsigmoid_fixpt_tmp_0;
  reg [41:0] invsigmoid_fixpt_tmp_1;
  reg [55:0] invsigmoid_fixpt_div_temp;
  reg [40:0] invsigmoid_fixpt_div_temp_0;
  reg [32:0] invsigmoid_fixpt_add_cast;
  reg [32:0] invsigmoid_fixpt_add_temp;
  reg [39:0] invsigmoid_fixpt_add_cast_0;
  reg [63:0] invsigmoid_fixpt_mul_temp;
  reg [64:0] invsigmoid_fixpt_cast;
  reg [64:0] invsigmoid_fixpt_cast_0;
  reg [31:0] invsigmoid_fixpt_add_cast_1;
  reg [39:0] invsigmoid_fixpt_add_cast_2;
  reg [39:0] invsigmoid_fixpt_add_temp_0;
  reg [32:0] invsigmoid_fixpt_add_cast_3;
  reg [32:0] invsigmoid_fixpt_add_cast_4;
  reg [55:0] invsigmoid_fixpt_cast_1;
  reg signed [32:0] invsigmoid_fixpt_cast_2;
  reg signed [34:0] invsigmoid_fixpt_sub_cast;
  reg signed [34:0] invsigmoid_fixpt_sub_temp;
  reg signed [67:0] invsigmoid_fixpt_mul_temp_0;
  reg signed [66:0] invsigmoid_fixpt_cast_3;


  always @(x, sign) begin
    invsigmoid_fixpt_add_cast = {1'b0, x};
    invsigmoid_fixpt_add_temp = 33'h000400000 + invsigmoid_fixpt_add_cast;
    invsigmoid_fixpt_add_cast_0 = {7'b0, invsigmoid_fixpt_add_temp};
    invsigmoid_fixpt_mul_temp = x * x;
    invsigmoid_fixpt_cast = {invsigmoid_fixpt_mul_temp, 1'b0};
    invsigmoid_fixpt_cast_0 = invsigmoid_fixpt_cast >>> 8'd1;
    invsigmoid_fixpt_add_cast_1 = invsigmoid_fixpt_cast_0[61:30];
    invsigmoid_fixpt_add_cast_2 = {1'b0, {invsigmoid_fixpt_add_cast_1, 7'b0000000}};
    invsigmoid_fixpt_add_temp_0 = invsigmoid_fixpt_add_cast_0 + invsigmoid_fixpt_add_cast_2;
    invsigmoid_fixpt_approx = invsigmoid_fixpt_add_temp_0[37:6];
    invsigmoid_fixpt_add_cast_3 = {1'b0, invsigmoid_fixpt_approx};
    invsigmoid_fixpt_b1 = 33'h000010000 + invsigmoid_fixpt_add_cast_3;
    invsigmoid_fixpt_add_cast_4 = {1'b0, invsigmoid_fixpt_approx};
    invsigmoid_fixpt_b1_0 = 33'h000010000 + invsigmoid_fixpt_add_cast_4;
    invsigmoid_fixpt_tmp = 65'h1FFFFFFFFFFFFFFFF;
    if (sign) begin
      invsigmoid_fixpt_tmp = 65'h00000000000000000;
    end
    else if (invsigmoid_fixpt_b1_0 == 33'h000000000) begin
    end
    else begin
      invsigmoid_fixpt_cast_1 = {invsigmoid_fixpt_approx, 24'b000000000000000000000000};
      if (invsigmoid_fixpt_b1_0 == 31'sd0) begin
        invsigmoid_fixpt_div_temp = 56'hFFFFFFFFFFFFFF;
      end
      else begin
        invsigmoid_fixpt_div_temp = invsigmoid_fixpt_cast_1 / invsigmoid_fixpt_b1_0;
      end
      invsigmoid_fixpt_tmp = {9'b0, invsigmoid_fixpt_div_temp};
    end
    if (sign) begin
      if (invsigmoid_fixpt_b1 == 33'h000000000) begin
        invsigmoid_fixpt_tmp_1 = 42'h3FFFFFFFFFF;
      end
      else begin
        if (invsigmoid_fixpt_b1 == 31'sd0) begin
          invsigmoid_fixpt_div_temp_0 = 41'h1FFFFFFFFFF;
        end
        else begin
          invsigmoid_fixpt_div_temp_0 = 41'h10000000000 / invsigmoid_fixpt_b1;
        end
        invsigmoid_fixpt_tmp_1 = {1'b0, invsigmoid_fixpt_div_temp_0};
      end
    end
    else begin
      invsigmoid_fixpt_tmp_1 = 42'h00000000000;
    end
    if (sign) begin
      invsigmoid_fixpt_tmp_0 = {invsigmoid_fixpt_tmp_1[24:0], 7'b0000000};
    end
    else begin
      invsigmoid_fixpt_tmp_0 = {invsigmoid_fixpt_tmp[24:0], 7'b0000000};
    end
    invsigmoid_fixpt_cast_2 = {1'b0, invsigmoid_fixpt_tmp_0};
    invsigmoid_fixpt_sub_cast = {3'b0, invsigmoid_fixpt_tmp_0};
    invsigmoid_fixpt_sub_temp = 35'sh080000000 - invsigmoid_fixpt_sub_cast;
    invsigmoid_fixpt_mul_temp_0 = invsigmoid_fixpt_cast_2 * invsigmoid_fixpt_sub_temp;
    invsigmoid_fixpt_cast_3 = invsigmoid_fixpt_mul_temp_0[66:0];
    result_1 = invsigmoid_fixpt_cast_3[62:31];
  end



  assign result = result_1;

endmodule  // invsigmoid_fixpt

