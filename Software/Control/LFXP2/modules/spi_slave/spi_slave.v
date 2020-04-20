// vim:set shiftwidth=4 softtabstop=4 expandtab:
//==============================================================================
// DeWille Lattice FXP2 firmware
//
// Copyright 2020 Ivan Vasilev, Zmei Research Ltd.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//==============================================================================

`default_nettype	none

module spi_slave(
    //in_clk, in_rst,
	// Wishbone master interface
	//in_wb_cyc,
	//in_wb_stb,
	//in_wb_we,
	//in_wb_addr,
	//in_wb_data,
	//in_wb_sel,
	//o_wb_stall,
	//o_wb_ack,
	//o_wb_data,
	// SPI slave interface
	in_mosi,
	in_sck,
	in_cs_n,
	o_miso,
	in_dbg_byte,
	o_dbg_byte
	);
	
	localparam spi_transfer_size = 8;

	//input wire 	in_clk, in_rst;
	//input wire 	in_wb_cyc, in_wb_stb, in_wb_we;
	input wire	in_mosi, in_sck, in_cs_n;
	output wire o_miso;

	input wire [7:0] in_dbg_byte;
	output reg [7:0] o_dbg_byte;
	
	reg [7:0]	shift_reg;
	reg [3:0]	bit_count;

	always @ (posedge in_cs_n)
		bit_count <= 0;

	always @ (posedge in_sck )
	begin
		if (!in_cs_n)
			if (bit_count < spi_transfer_size-1)
				begin
					bit_count <= bit_count + 1;
					shift_reg[7:1] <= shift_reg[6:0];
					shift_reg[0] <= in_mosi;
				end
			else if (bit_count == spi_transfer_size-1)
				begin
					o_dbg_byte <= { shift_reg[6:0], in_mosi };
					bit_count = 0;
				end
	end

endmodule
