module double_adder (
    input   logic           clk,    // Clock
    input   logic           clk_en, // Clock Enable
    input   logic           rst_n,  // Asynchronous reset active low

    input   logic           compute,
    input   logic   [63:0]  a,
    input   logic   [63:0]  b,
    output  logic   [63:0]  z,
    output  logic           complete
);

    enum    logic   [3:0] { halted, unpack, special_cases,
                            align, add_0, add_1,
                            normalize_1, normalize_2,
                            round, pack, return_z } state, next_state;

    logic   [52:0]  a_mantissa;
    logic   [52:0]  b_mantissa;
    logic   [52:0]  z_mantissa;

    logic   [12:0]  a_exponent;
    logic   [12:0]  b_exponent;
    logic   [12:0]  z_exponent;

    logic           a_sign;
    logic           b_sign;
    logic           z_sign;

    logic           gaurd;
    logic           round_bit;
    logic           sticky;

    logic   [56:0]  sum;

    logic   jump_return;

    always_ff @(posedge Clk or negedge rst_n) begin : state_assignment
        if(~rst_n) begin
             state <= halted;
        end else if(clk_en) begin
             state <= next_state;
        end
    end

    always_comb begin : next_state_assignment
        // default
        next_state = state;

        unique case (state)
            halted: begin
                if (compute == 1'b1) begin
                    next_state <= unpack;
                end
            end

            unpack: begin
                next_state <= special_cases;
            end

            special_cases: begin
                if (jump_return == 1'b1) begin
                    next_state <= return_z;
                end else begin
                    next_state <= align;
                end
            end

            align: begin
                if ($signed(a_e) == $signed(b_e)) begin
                    next_state <= add_0;
                end
            end

            add_0: begin
                next_state <= add_1;
            end

            add_1: begin
                next_state <= normalize_1;
            end

            normalize_1: begin
                if (z_mantissa[52] != 0 || $signed(z_exponent) < -1022 || $signed(z_exponent) == -1022) begin
                    next_state <= normalize_2;
                end
            end

            normalize_2: begin
                if ($signed(z_exponent > -1022) || ($signed(z_exponent == -1022))) begin
                    next_state <= round;
                end
            end

            round: begin
                next_state <= pack;
            end

            pack: begin
                next_state <= return_z;
            end

            return_z: begin

            end
        endcase // state
    end

    always_comb begin : state_operations
        // default
        complete    = 1'b0;
        jump_return = 1'b0;

        unique case (state)
            halted: begin

            end

            unpack: begin
                a_mantissa <= {a[51:0], 3'd0};
                b_mantissa <= {b[51:0], 3'd0};
                a_exponent <= a[62:52] - 1023;
                b_exponent <= b[62:52] - 1023;
                a_sign <= a[63];
                b_sign <= b[63];
            end

            special_cases: begin
                //if a is NaN or b is NaN return NaN
                if ((a_exponent == 1024 && a_mantissa != 0) || (b_exponent == 1024 && b_mantissa != 0)) begin
                  z[63] <= 1;
                  z[62:52] <= 2047;
                  z[51] <= 1;
                  z[50:0] <= 0;
                  jump_return <= 1'b1;
                //if a is inf return inf
                end else if (a_exponent == 1024) begin
                  z[63] <= a_sign;
                  z[62:52] <= 2047;
                  z[51:0] <= 0;
                  jump_return <= 1'b1;
                //if b is inf return inf
                end else if (b_exponent == 1024) begin
                  z[63] <= b_sign;
                  z[62:52] <= 2047;
                  z[51:0] <= 0;
                  jump_return <= 1'b1;
                //if a is zero return b
                end else if ((($signed(a_exponent) == -1023) && (a_mantissa == 0)) && (($signed(b_exponent) == -1023) && (b_mantissa == 0))) begin
                  z[63] <= a_sign & b_sign;
                  z[62:52] <= b_exponent[10:0] + 1023;
                  z[51:0] <= b_mantissa[55:3];
                  jump_return <= 1'b1;
                //if a is zero return b
                end else if (($signed(a_exponent) == -1023) && (a_mantissa == 0)) begin
                  z[63] <= b_sign;
                  z[62:52] <= b_exponent[10:0] + 1023;
                  z[51:0] <= b_mantissa[55:3];
                  jump_return <= 1'b1;
                //if b is zero return a
                end else if (($signed(b_exponent) == -1023) && (b_mantissa == 0)) begin
                  z[63] <= a_sign;
                  z[62:52] <= a_exponent[10:0] + 1023;
                  z[51:0] <= a_mantissa[55:3];
                  jump_return <= 1'b1;
                end else begin
                  //Denormalised Number
                  if ($signed(a_exponent) == -1023) begin
                    a_exponent <= -1022;
                  end else begin
                    a_mantissa[55] <= 1;
                  end
                  //Denormalised Number
                  if ($signed(b_exponent) == -1023) begin
                    b_exponent <= -1022;
                  end else begin
                    b_mantissa[55] <= 1;
                  end
                end
            end

            align: begin
                if ($signed(a_exponent) > $signed(b_exponent)) begin
                  b_exponent <= b_exponent + 1;
                  b_mantissa <= b_mantissa >> 1;
                  b_mantissa[0] <= b_mantissa[0] | b_mantissa[1];
                end else if ($signed(a_exponent) < $signed(b_exponent)) begin
                  a_exponent <= a_exponent + 1;
                  a_mantissa <= a_mantissa >> 1;
                  a_mantissa[0] <= a_mantissa[0] | a_mantissa[1];
                end
            end

            add_0: begin
                z_exponent <= a_exponent;
                if (a_sign == b_sign) begin
                  sum <= {1'd0, a_mantissa} + b_mantissa;
                  z_sign <= a_sign;
                end else begin
                  if (a_mantissa > b_mantissa) begin
                    sum <= {1'd0, a_mantissa} - b_mantissa;
                    z_sign <= a_sign;
                  end else begin
                    sum <= {1'd0, b_mantissa} - a_mantissa;
                    z_sign <= b_sign;
                  end
                end
            end

            add_1: begin
                if (sum[56]) begin
                  z_mantissa <= sum[56:4];
                  guard <= sum[3];
                  round_bit <= sum[2];
                  sticky <= sum[1] | sum[0];
                  z_exponent <= z_exponent + 1;
                end else begin
                  z_mantissa <= sum[55:3];
                  guard <= sum[2];
                  round_bit <= sum[1];
                  sticky <= sum[0];
                end
            end

            normalize_1: begin
                if (z_mantissa[52] == 0 && $signed(z_exponent) > -1022) begin
                  z_exponent <= z_exponent - 1;
                  z_mantissa <= z_mantissa << 1;
                  z_mantissa[0] <= guard;
                  guard <= round_bit;
                  round_bit <= 0;
                end
            end

            normalize_2: begin
                if ($signed(z_exponent) < -1022) begin
                  z_exponent <= z_exponent + 1;
                  z_mantissa <= z_mantissa >> 1;
                  guard <= z_mantissa[0];
                  round_bit <= guard;
                  sticky <= sticky | round_bit;
                end
            end

            round: begin
                if (guard && (round_bit | sticky | z_mantissa[0])) begin
                  z_mantissa <= z_mantissa + 1;
                  if (z_mantissa == 53'h1fffffffffffff) begin
                    z_exponent <= z_exponent + 1;
                  end
                end
            end

            pack: begin
                z[51:0] <= z_mantissa[51:0];
                z[62:52] <= z_exponent[10:0] + 1023;
                z[63] <= z_sign;
                if ($signed(z_exponent) == -1022 && z_mantissa[52] == 0) begin
                    z[62:52] <= 0;
                end
                //if overflow occurs, return inf
                if ($signed(z_exponent) > 1023) begin
                  z[51:0] <= 0;
                  z[62:52] <= 2047;
                  z[63] <= z_sign;
                end
            end

            return_z: begin
                complete <= 1'b1;
            end
        endcase // state
    end

endmodule // double_adder