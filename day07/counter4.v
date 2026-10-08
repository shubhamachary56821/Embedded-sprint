`timescale 1ns/1ps
// 4-bit up counter with synchronous reset and enable
module counter4 (
    input  wire       clk,
    input  wire       rst,     // active-high, synchronous
    input  wire       en,
    output reg  [3:0] count
);
    always @(posedge clk) begin
        if (rst)
            count <= 4'd0;
        else if (en)
            count <= count + 4'd1;   // wraps 15 -> 0
    end
endmodule