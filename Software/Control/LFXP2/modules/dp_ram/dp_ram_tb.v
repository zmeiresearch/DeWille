`timescale 1ns/1ns

`define TEST_VECTOR_SIZE    1000
`define TEST_VECTOR_FILE    "dp_ram.tv"
`define RAM_WIDTH           8
`define RAM_SIZE            16
`define RAM_PRELOAD_FILE    "dp_ram.hex"

module dp_ram_test();
    

    // testnench data
    reg [256:0] waveform_file; 
    reg [79:0]  test_vector[`TEST_VECTOR_SIZE:0];
    reg [31:0]  test_step;
    reg [7:0]   test_number;
    reg [7:0]   test_cycle;
    reg [31:0]  error_count;

    reg wb_ack_expected;
    reg [`RAM_WIDTH-1:0] wb_dat_s2m_expected;

    // module interface
    reg wb_clk;
    reg wb_rst;
    reg [$clog2(`RAM_SIZE)-1:0] wb_addr;  // REG_SIZExWIDTH registers
    reg [`RAM_WIDTH-1:0] wb_dat_m2s;
    reg wb_we;
    reg wb_cyc;
    reg wb_stb;

    wire wb_ack;
    wire [`RAM_WIDTH-1:0] wb_dat_s2m;


    dp_ram #(
        .SIZE(`RAM_SIZE),
        .WIDTH(`RAM_WIDTH),
        .MEMFILE(`RAM_PRELOAD_FILE),
        .VERBOSE(1)
    ) dut (
    // Wishbone slave interface
        .wb_clk_in(wb_clk),
        .wb_rst_in(wb_rst),
        .wb_adr_in(wb_addr),
        .wb_dat_in(wb_dat_m2s),
        .wb_we_in(wb_we),
        .wb_cyc_in(wb_cyc),
        .wb_stb_in(wb_stb),
        .wb_ack_o(wb_ack),
        .wb_dat_o(wb_dat_s2m)
    );

    always  // clock - always running
    begin
        wb_clk = 0; #5; wb_clk = 1; #5; // 10 ns clock
    end

    initial begin   // load testvector
        $readmemh(`TEST_VECTOR_FILE, test_vector);
        error_count = 0;
        $display("Test vectors loaded from: %s ", `TEST_VECTOR_FILE);
        //test_step = 0;
        //for (test_step=0;test_step<10;test_step++) 
        //    $display("%d:%h", test_step, test_vector[test_step]);
        test_step = 0;
        end
		
    initial begin
        if ($value$plusargs("Waveout=%s", waveform_file)) begin
            // dump everything for inspection
            $dumpfile(waveform_file);
            $dumpvars(0, dp_ram_test);
            end
        end


    always @(posedge wb_clk) begin
        test_number = test_vector[test_step][79:72];
        test_cycle = test_vector[test_step][71:64];
        //    $display("Inconsistent test vector file: Expected: %h got %h", 
        //        test_step, test_vector[test_step][48:40]);

        wb_rst = test_vector[test_step][56];
        wb_addr = test_vector[test_step][55:48];
        wb_dat_m2s = test_vector[test_step][47:40];
        wb_we = test_vector[test_step][32];
        wb_cyc = test_vector[test_step][24];
        wb_stb = test_vector[test_step][16];

        wb_ack_expected = test_vector[test_step][8];
        wb_dat_s2m_expected = test_vector[test_step][7:0];
        end

    always @(negedge wb_clk) begin
        if (wb_ack_expected !== wb_ack) begin
            $display("Test: %d, cycle %d, Error: wb_ack: Expected: %b, got: %b", 
                test_number, test_cycle, wb_ack_expected, wb_ack);
            error_count = error_count + 1;
            end
       
        if (wb_dat_s2m_expected !== wb_dat_s2m) begin
            $display("Test: %d, cycle %d, Error: wb_s2m: Expected: %h, got: %h", 
                test_number, test_cycle, wb_dat_s2m_expected, wb_dat_s2m);
            error_count = error_count + 1;
            end
 
        test_step = test_step + 1;

        if (test_vector[test_step][79:72] === 8'bxxxxxxxx) begin
            $display("%d tests completed with %d errors", test_step, error_count);
            $finish;
            end
        end

endmodule
