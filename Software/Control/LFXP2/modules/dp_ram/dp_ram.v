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

module dp_ram #(
    parameter SIZE = 16,            // Size in bytes
    parameter WIDTH = 8,            // Data word width. 
    parameter MEMFILE = "",         // file to preload contents with
    parameter VERBOSE = 0           // Verbose output for simulation
    //parameter SEL_WIDTH = (WIDTH/8) // Select bus size
) (
    // Wishbone slave interface
    input                       wb_clk_in, 
    input                       wb_rst_in,

    input [$clog2(SIZE)-1:0]    wb_adr_in,
    input [WIDTH-1:0]           wb_dat_in,
    input                       wb_we_in,
    input                       wb_cyc_in,
    input                       wb_stb_in,

    output reg                  wb_ack_o,
    output reg [WIDTH-1:0]      wb_dat_o
);

    reg verbose;
    initial verbose = $test$plusargs("verbose") || VERBOSE;

    reg [WIDTH-1:0] mem [SIZE-1:0]; // the memory array
    reg [$clog2(SIZE)-1:0]  adr_in;         // to latch the address we got on the bus
    wire selected = wb_cyc_in & wb_stb_in;  // CYC indicates a transfer is in progress
                                            // STB indicates the start of R/W phase 
                                            // Wishbone B4, pg. 40, 43

    // Wishbone transfer
    always @(posedge wb_clk_in) begin
        if (wb_rst_in) begin
            // Wishbone reset. Nothing much to do
            wb_ack_o <= 1'b0;
            wb_dat_o <= {WIDTH{1'bz}};
            end
        else begin
            adr_in <= wb_adr_in;            // latch-in the address
            if (selected & !wb_ack_o) begin
                wb_ack_o <= 1'b1;           // ACK follows STB&CYC as we cannot stall (for now)

                wb_dat_o = mem[adr_in];     // always output output the data and keep it till 
                                            // the next transfer. This is acceptable, as master
                                            // should only sample the data once on the 2nd clk
                                            // during read and never does that during write
                if (wb_we_in) begin         // Handle write
                    mem[adr_in] <= wb_dat_in;
                    end // !wb_we_in & wb_ack_o
                end
            else begin
                wb_ack_o <= 1'b0;            // Slave not selected, de-assert ACK
                end // selected
            end
        end // posedge wb_clk_in
    

    // Initialization
    integer i;
    initial begin
        wb_ack_o <= 1'b0;
        wb_dat_o <= {WIDTH{1'bz}};
        if (MEMFILE != "") begin
            if (verbose) $display("Reading %s", MEMFILE);
            $readmemh(MEMFILE, mem);
            end
        else begin
            if (verbose) $display("Initializing memory with 0"); 
            for (i = 0; i != SIZE; i = i + 1) begin
                mem[i] = {WIDTH{1'b0}};
                end
            end
        end
endmodule
