module top(led, lrck_left, lrck_right, data_left, data_right, bck_left, bck_right, mck_left, mck_right, clk, lrck_1, data_1, bck_1, mck_1);
	output wire led;
	input wire clk;
	output wire lrck_left;
	output wire lrck_right;
	output wire data_left, data_right;
	output wire bck_left, bck_right;
	output wire mck_left, mck_right; 
	
	input wire lrck_1, data_1, bck_1, mck_1;

	tee tee_lrck(.in(bck_1), .out1(lrck_left), .out2(lrck_right));
	tee tee_bck(.in(lrck_1), .out1(bck_left), .out2(bck_right));
	
	tee tee_data(.in(mck_1), .out1(data_left), .out2(data_right));
	tee tee_mck(.in(data_1), .out1(mck_left), .out2(mck_right));

	led_counter ledcntr(.clock(clk), .out(led));
endmodule

module tee(in, out1, out2);
	input wire in;
	output wire out1;
	output wire out2;
	
	assign out1 = in;
	assign out2 = in;
endmodule

module led_counter(clock, out);
	input wire clock;
	output reg out;
	
	reg [31:0] counter;
	
	initial 
	begin
		out = 1'b0;
		counter = 32'b0;
	end
	
	always @(posedge clock)
	begin
		counter <= counter + 1'b1; 
		out <= counter[28];
	end
		
endmodule