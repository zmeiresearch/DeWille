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

module dualport_ram #(
        parameter DATA_WIDTH = 8, ADDRESS_WIDTH = 3
    )(
        // Global signals
        input clk,
        input rst,
        
        // Port A
        inout [DATA_WIDTH-1:0]      data_a,
        input [ADDRESS_WIDTH-1:0]   addr_a,
        input                       we_a,
        input                       oe_a,

        // Port B
        inout [DATA_WIDTH-1:0]      data_b,
        input [ADDRESS_WIDTH-1:0]   add_b,
        input                       we_b,
        input                       oe_b
    )

    parameter RAM_SIZE = 1 << ADDRESS_WIDTH;

    // internal data
    reg [DATA_WIDTH-1:0] memory[RAM_SIZE-1:0];

    // synchronous reset
    always @ pos



