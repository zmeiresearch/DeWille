`timescale 1ns/1ns

module spi_slave_test();
	
	reg in_mosi, in_sck, in_cs_n;
	wire o_miso;
	wire [7:0] in_dbg_byte, o_dbg_byte;
	
	spi_slave dut(
		.in_mosi(in_mosi),
		.in_sck(in_sck),
		.in_cs_n(in_cs_n),
		.o_miso(o_miso),
		.in_dbg_byte(in_dbg_byte),
		.o_dbg_byte(o_dbg_byte));
		
	initial
	begin
        $dumpfile("spi_slave.vcd");
        $dumpvars(0, spi_slave_test);
		in_mosi = 1; in_cs_n = 1; in_sck  = 0;
		#10
		in_cs_n = 0;	// set CS low to initiate transfer
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 1st edge
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 2nd edge
		in_mosi = 0;
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 3rd edge
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 4th edge
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 5th edge
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 6th edge
		in_mosi = 1;
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 7th edge
		#5; in_sck = 1; #5; in_sck = 0; // 1st byte, 8th edge
		// At that point, o_dbg_byte should be 0xC3
		
		// Start second byte
		in_mosi = 0;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 1st edge
		in_mosi = 1;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 2nd edge
		in_mosi = 0;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 3rd edge
		in_mosi = 1;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 4th edge
		in_mosi = 1;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 5th edge
		in_mosi = 0;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 6th edge
		in_mosi = 1;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 7th edge
        in_mosi = 0;
		#5; in_sck = 1; #5; in_sck = 0; //  2nd byte, 8th edge
		// At that point o_dbg_byte should be 0x5A 
		$finish;
		
	end
	
endmodule
