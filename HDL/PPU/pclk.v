// Pixel clock (abbreviated as PCLK) is used by all PPU parts (except the video phase generator).

module PixelClock (
	n_CLK, CLK, RES,
	n_PCLK, PCLK);

	input n_CLK;
	input CLK;				// NTSC: 21477272 Hz (~0,046 �s), PAL: 26601712 Hz (~0,037 �s)
	input RES;

	output n_PCLK;
	output PCLK;			// NTSC: 5369318 Hz (~0,186 �s), PAL: 5320342.4 Hz (~0,187 �s)

	// wires
	
	wire latch1_in;
	wire latch1_out;
	wire latch2_out;
	wire latch3_out;
	wire latch4_out;
	wire pclk;
	wire pclk_out;
	wire npclk_out;

	// The PCLK is obtained by slowing down (dividing) the input clock signal CLK (21.48 MHz) by a factor of 4.
	// For this purpose, a divider on static latches is used:

	nor (latch1_in, RES, latch4_out);

	dlatch latch1 (.d(latch1_in), .en(n_CLK), .nq(latch1_out) );
	dlatch latch2 (.d(latch1_out), .en(CLK), .nq(latch2_out) );
	dlatch latch3 (.d(latch2_out), .en(n_CLK), .nq(latch3_out) );
	dlatch latch4 (.d(latch3_out), .en(CLK), .nq(latch4_out) );

	assign pclk = latch4_out;

	// Just below the divider is the single phase splitter.
	// This is a canonical circuit based on a single FF that makes two phases (/PCLK + PCLK) from a single phase (PCLK).

	rsff PCLK_FF (.r(pclk), .s(~pclk), .q(pclk_out), .nq(npclk_out) );

	assign n_PCLK = ~pclk_out;
	assign PCLK = ~npclk_out;

endmodule // PixelClock
