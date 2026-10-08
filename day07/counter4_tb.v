`timescale 1ns/1ps
module counter4_tb;
    reg clk = 0, rst = 1, en = 0;
    wire [3:0] count;
    counter4 dut (.clk(clk), .rst(rst), .en(en), .count(count));

    always #5 clk = ~clk;                 // 100 MHz clock

    integer errors = 0;
    task check(input [3:0] expected);
        begin
            if (count !== expected) begin
                $display("FAIL t=%0t: count=%0d expected=%0d", $time, count, expected);
                errors = errors + 1;
            end
        end
    endtask

    initial begin
        $dumpfile("counter4.vcd");
        $dumpvars(0, counter4_tb);
        #12 rst = 0; en = 1;
        repeat (3) @(posedge clk); #1 check(4'd3);     // counted 3 times
        en = 0;
        repeat (2) @(posedge clk); #1 check(4'd3);     // enable off: holds
        en = 1;
        repeat (13) @(posedge clk); #1 check(4'd0);    // 3 + 13 = 16 wraps to 0
        rst = 1; @(posedge clk); #1 check(4'd0);       // reset
        if (errors == 0) $display("PASS: counter4");
        else             $display("FAILED: %0d errors", errors);
        $finish;
    end
endmodule