
module ACLKGen(PHI1, PHI2, ACLK, n_ACLK, RES);

	input PHI1;
	input PHI2;
	output ACLK;
	output n_ACLK;
	input RES;

	wire n_latch1_out;
	wire n_latch2_out;
	wire latch1_in;

	dlatch phi1_latch (
		.d(latch1_in),
		.en(PHI1),
		.nq(n_latch1_out) );

	dlatch phi2_latch (
		.d(n_latch1_out),
		.en(PHI2),
		.nq(n_latch2_out) );

	nor (latch1_in, RES, n_latch2_out);

	wire n1;
	nor (n1, ~PHI1, latch1_in);
	nor (n_ACLK, ~PHI1, n_latch2_out);
	not (ACLK, n1);
	assign ACLK = ~n1;

endmodule // ACLKGen

module SoftTimer(
	PHI1, n_ACLK, ACLK,
	RES, n_R4015, W4017, DB, DMCINT, INT_out, nLFO1, nLFO2);

	input PHI1;
	input n_ACLK;
	input ACLK;

	input RES;
	input n_R4015;
	input W4017;
	inout [7:0] DB;
	input DMCINT;
	output INT_out;
	output nLFO1;
	output nLFO2;

	wire n_mode;
	wire mode;
	wire [5:0] PLA_out;
	wire Z2;
	wire F1;				// 1: Reset LFSR
	wire F2;				// 1: Perform the LFSR step
	wire n_sin;
	wire [14:0] sout;
	wire [14:0] n_sout;

	// SoftCLK control circuits have a very conventional division, because they are "scattered" in an even layer on the chip and it is difficult to determine their boundaries

	FrameCnt_Control fcnt_ctl (
		.PHI1(PHI1),
		.n_ACLK(n_ACLK),
		.RES(RES),
		.DB(DB),
		.DMCINT(DMCINT),
		.n_R4015(n_R4015),
		.W4017(W4017),
		.PLA_in(PLA_out),
		.n_mdout(n_mode),
		.mdout(mode),
		.Timer_Int(INT_out) );

	FrameCnt_LFSR_Control lfsr_ctl(
		.n_ACLK(n_ACLK),
		.ACLK(ACLK),
		.RES(RES),
		.W4017(W4017),
		.n_mode(n_mode),
		.mode(mode),
		.PLA_in(PLA_out),
		.C13(n_sout[13]),
		.C14(n_sout[14]),
		.Z2(Z2),
		.F1(F1),
		.F2(F2),
		.n_sin_toLFSR(n_sin) );

	FrameCnt_LFSR lfsr (
		.n_ACLK(n_ACLK),
		.F1_Reset(F1),
		.F2_Step(F2),
		.n_sin(n_sin),
		.sout(sout),
		.n_sout(n_sout) );

	FrameCnt_PLA pla (
		.s(sout),
		.ns(n_sout),
		.md(mode),
		.PLA_out(PLA_out) );

	// LFO Output

	wire tmp1;
	nor (tmp1, PLA_out[0], PLA_out[1], PLA_out[2], PLA_out[3], PLA_out[4], Z2);
	wire tmp2;
	nor (tmp2, tmp1, ACLK);
	assign nLFO1 = ~tmp2;

	wire tmp3;
	nor (tmp3, PLA_out[1], PLA_out[3], PLA_out[4], Z2);
	wire tmp4;
	nor (tmp4, tmp3, ACLK);
	assign nLFO2 = ~tmp4;

endmodule // SoftTimer

module FrameCnt_Control(
	PHI1, n_ACLK,
	RES, DB, DMCINT, n_R4015, W4017, PLA_in,
	n_mdout, mdout, Timer_Int);

	input PHI1;
	input n_ACLK;

	input RES;
	inout [7:0] DB;
	input DMCINT;
	input n_R4015;
	input W4017;
	input [5:0] PLA_in;

	inout n_mdout;
	output mdout;
	output Timer_Int;

	wire R4015_clear;
	wire mask_clear;
	wire intff_out;
	wire n_intff_out;
	wire int_sum;
	wire int_latch_out;

	nor (R4015_clear, n_R4015, PHI1);

	RegisterBit mode (.d(DB[7]), .ena(W4017), .n_ACLK(n_ACLK), .nq(n_mdout) );
	RegisterBit mask (.d(DB[6]), .ena(W4017), .n_ACLK(n_ACLK), .q(mask_clear) );
	rsff_2_4 int_ff (.res1(RES), .res2(R4015_clear), .res3(mask_clear), .s(n_mdout & PLA_in[3]), .q(intff_out), .nq(n_intff_out) );
	dlatch md_latch (.d(n_mdout), .en(n_ACLK), .nq(mdout) );
	dlatch int_latch (.d(n_intff_out), .en(n_ACLK), .q(int_latch_out) );
	bustris int_status (.a(int_latch_out), .n_x(DB[6]), .n_en(n_R4015) );

	nor (int_sum, intff_out, DMCINT);
	assign Timer_Int = ~int_sum;

endmodule // FrameCnt_Control

module FrameCnt_LFSR_Control(
	n_ACLK, ACLK,
	RES, W4017, n_mode, mode, PLA_in, C13, C14,
	Z2, F1, F2, n_sin_toLFSR);

	input n_ACLK;
	input ACLK;

	input RES;
	input W4017;
	inout n_mode;
	input mode;
	input [5:0] PLA_in;
	input C13;
	input C14;

	output Z2;
	output F1;
	output F2;
	output n_sin_toLFSR;

	wire Z1;

	// LFSR control

	wire t1;
	nor (t1, PLA_in[3], PLA_in[4], Z1);
	nor (F1, t1, ACLK);
	nor (F2, ~t1, ACLK);

	// LFO control

	wire z1_out;
	wire z2_out;
	wire zff_out;
	wire zff_set;
	nor (zff_set, z1_out, ACLK);
	dlatch z1 (.d(zff_out), .en(n_ACLK), .q(z1_out), .nq(Z1) );
	dlatch z2 (.d(n_mode), .en(n_ACLK), .q(z2_out) );
	rsff_2_3 z_ff (.res1(RES), .res2(W4017), .s(zff_set), .q(zff_out) );
	nor (Z2, z1_out, z2_out);

	// LFSR shift in complement

	wire tmp1;
	nor (tmp1, C13, C14, PLA_in[5]);
	nor (n_sin_toLFSR, C13 & C14, tmp1);

endmodule // FrameCnt_LFSR_Control

module FrameCnt_LFSR_Bit(
	n_ACLK,
	n_sin, F1, F2,
	sout, n_sout);

	input n_ACLK;

	input n_sin;
	input F1;
	input F2;

	output sout;
	output n_sout;

	wire inlatch_out;
	dlatch in_latch (
		.d(F2 ? n_sin : (F1 ? 1'b1 : 1'bz)),
		.en(1'b1), .nq(inlatch_out));
	dlatch out_latch (.d(inlatch_out), .en(n_ACLK), .q(sout), .nq(n_sout));

endmodule // FrameCnt_LFSR_Bit

module FrameCnt_LFSR(
	n_ACLK, F1_Reset, F2_Step, n_sin,
	sout, n_sout);

	input n_ACLK;
	input F1_Reset;
	input F2_Step;
	input n_sin;		// Inverse Shift-in

	output [14:0] sout;
	output [14:0] n_sout;

	FrameCnt_LFSR_Bit bits [14:0] (
		.n_ACLK(n_ACLK),
		.n_sin({n_sout[13:0],n_sin}),
		.F1(F1_Reset),
		.F2(F2_Step),
		.sout(sout),
		.n_sout(n_sout) );

endmodule // FrameCnt_LFSR

module FrameCnt_PLA(s, ns, md, PLA_out);

	input [14:0] s;
	input [14:0] ns;
	input md; 			// For PLA[3]
	output [5:0] PLA_out;

	nor (PLA_out[0], s[0], ns[1], ns[2], ns[3], ns[4], s[5], s[6], ns[7], ns[8], ns[9], ns[10], ns[11], s[12], ns[13], ns[14]);
	nor (PLA_out[1], s[0], s[1], ns[2], ns[3], ns[4], ns[5], ns[6], ns[7], ns[8], s[9], s[10], ns[11], s[12], s[13], ns[14]);
	nor (PLA_out[2], s[0], s[1], ns[2], ns[3], s[4], ns[5], s[6], s[7], ns[8], ns[9], s[10], s[11], ns[12], s[13], ns[14]);
	nor (PLA_out[3], s[0], s[1], s[2], s[3], s[4], ns[5], ns[6], ns[7], ns[8], s[9], ns[10], s[11], ns[12], ns[13], ns[14], md);	// ⚠️
	nor (PLA_out[4], s[0], ns[1], s[2], ns[3], ns[4], ns[5], ns[6], s[7], s[8], ns[9], ns[10], ns[11], s[12], s[13], s[14]);
	nor (PLA_out[5], ns[0], ns[1], ns[2], ns[3], ns[4], ns[5], ns[6], ns[7], ns[8], ns[9], ns[10], ns[11], ns[12], ns[13], ns[14]);

endmodule // FrameCnt_PLA
