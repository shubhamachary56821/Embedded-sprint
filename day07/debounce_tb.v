`timescale 1ns/1ps
module debounce_tb;
    reg clk = 0, rst = 1, btn = 0;
    wire out;
    debounce #(.STABLE_CYCLES(4)) dut (.clk(clk), .rst(rst), .btn_in(btn), .btn_out(out));
    always #5 clk = ~clk;

    integer errors = 0;
    task expect(input e, input [255:0] msg);
        begin
            if (out !== e) begin
                $display("FAIL t=%0t: out=%b expected=%b (%0s)", $time, out, e, msg);
                errors = errors + 1;
            end
        end
    endtask

    initial begin
        $dumpfile("debounce.vcd");
        $dumpvars(0, debounce_tb);
        #22 rst = 0;
        // bouncing press: toggles faster than STABLE_CYCLES
        btn = 1; repeat (2) @(posedge clk);
        btn = 0; repeat (1) @(posedge clk);
        btn = 1; repeat (2) @(posedge clk);
        btn = 0; repeat (2) @(posedge clk);
        #1 expect(0, "bounces must be ignored");
        // clean press held long enough
        btn = 1; repeat (10) @(posedge clk); #1 expect(1, "stable press accepted");
        // bouncing release
        btn = 0; repeat (1) @(posedge clk);
        btn = 1; repeat (1) @(posedge clk);
        #1 expect(1, "release bounce ignored");
        btn = 0; repeat (10) @(posedge clk); #1 expect(0, "stable release accepted");
        if (errors == 0) $display("PASS: debounce");
        else             $display("FAILED: %0d errors", errors);
        $finish;
    end
endmodule