`timescale 1ns/1ps
// Button debouncer: output follows input only after the input has been
// stable for STABLE_CYCLES clock cycles.
module debounce #(
    parameter STABLE_CYCLES = 4      // use a large value (e.g. 500000) on real hardware
)(
    input  wire clk,
    input  wire rst,
    input  wire btn_in,              // raw, bouncy
    output reg  btn_out              // clean
);
    localparam W = 32;
    reg [W-1:0] cnt;
    reg         last;

    always @(posedge clk) begin
        if (rst) begin
            cnt <= 0; last <= 0; btn_out <= 0;
        end else begin
            if (btn_in != last) begin          // input changed: restart count
                last <= btn_in;
                cnt  <= 0;
            end else if (cnt == STABLE_CYCLES - 1) begin
                btn_out <= last;               // stable long enough: accept
            end else begin
                cnt <= cnt + 1;
            end
        end
    end
endmodule