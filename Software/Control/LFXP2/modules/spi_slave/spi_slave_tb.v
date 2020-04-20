`timescale 1ns/1ns

`define TEST_VECTOR_SIZE 1000
`define TEST_VECTOR_FILE "spi_slave.tv"

module spi_slave_test();
    
    reg [256:0] waveform_file; 
    reg [47:0]  test_vector[`TEST_VECTOR_SIZE:0];
    reg         o_miso_expected;
    reg [7:0]   o_dbg_byte_expected;
    reg [31:0]  test_step;
    reg [31:0]  error_count;

    reg         in_mosi;
    reg         in_sck;
    reg         in_cs_n;
    wire        o_miso;
    reg [7:0]   in_dbg_byte;
    wire [7:0]  o_dbg_byte;
	
    spi_slave dut(
        .in_mosi(in_mosi),
        .in_sck(in_sck),
        .in_cs_n(in_cs_n),
        .o_miso(o_miso),
        .in_dbg_byte(in_dbg_byte),
        .o_dbg_byte(o_dbg_byte));

    always  // clock - always running
    begin
        in_sck = 0; #5; in_sck = 1; #5; // 10 ns clock
    end

    initial begin   // load testvector
        $readmemh(`TEST_VECTOR_FILE, test_vector);
        error_count = 0;
        test_step = 0;
        $display("Test vectors loaded from: $s ", `TEST_VECTOR_FILE);
        for (test_step=0;test_step<10;test_step++) 
            $display("%d:%h", test_step, test_vector[test_step]);
        test_step = 0;
    end
		
    initial begin
        if ($value$plusargs("Waveout=%s", waveform_file))
        begin
         // dump everything for inspection
            $dumpfile(waveform_file);
            $dumpvars(0, spi_slave_test);
        end
    end

    always @(posedge in_sck)
    begin
        #1  // apply input a little bit after the clock
        if (test_step !== test_vector[test_step][47:40])
            $display("Inconsistent test vector file: Expected: %h got %h", 
                test_step, test_vector[test_step][48:40]);

        in_cs_n = test_vector[test_step][32];
        in_mosi = test_vector[test_step][24];
        in_dbg_byte = test_vector[test_step][23:16];

        o_miso_expected = test_vector[test_step][8];
        o_dbg_byte_expected = test_vector[test_step][7:0];

    end

    always @(negedge in_sck)
    begin
        if (o_miso_expected !== o_miso)
        begin
            //$display("Error: o_miso on step %h: Expected: %b, got: %b", 
            //    test_step, o_miso_expected, o_miso);
            //error_count = error_count + 1;
        end
        if (o_dbg_byte !== o_dbg_byte_expected)
        begin
            $display("Error: o_dbg_byte on step %h: Expected: %h, got %h",
                test_step, o_dbg_byte_expected, o_dbg_byte);
            error_count = error_count + 1;
        end
        test_step = test_step + 1;

        if (test_vector[test_step][47:40] === 8'bxxxxxxxx)
        begin
            $display("%d tests completed with %d errors", test_step, error_count);
            $finish;
        end
    end

endmodule
