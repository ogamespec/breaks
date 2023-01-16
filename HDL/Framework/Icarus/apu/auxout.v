// Simple DAC

module AUX (AUX_A, AUX_B, AOut, BOut);

	input [7:0] AUX_A;			// Digital input AUX A {SQB[3:0],SQA[3:0]}
	input [14:0] AUX_B;			// Digital input AUX B {DMC[6:0],RND[3:0],TRI[3:0]}
	output [31:0] AOut; 		// Analog output AUX A (float, volts)
	output [31:0] BOut;			// Analog output AUX B (float, volts)

	reg [31:0] auxa_rom [0:255];
	reg [31:0] auxb_rom [0:32767];

	initial begin
		$readmemh("auxa.mem", auxa_rom);
		$readmemh("auxb.mem", auxb_rom);
	end

	assign AOut = auxa_rom[AUX_A];
	assign BOut = auxb_rom[AUX_B];

endmodule // AUX
