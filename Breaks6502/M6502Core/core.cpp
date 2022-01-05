#include "pch.h"

using namespace BaseLogic;

namespace M6502Core
{
	M6502::M6502()
	{
		decoder = new Decoder;
		predecode = new PreDecode;
		ir = new IR;
		ext = new ExtraCounter;
		brk = new BRKProcessing;
		disp = new Dispatcher;
		random = new RandomLogic;
	}

	M6502::~M6502()
	{
		delete decoder;
		delete predecode;
		delete ir;
		delete ext;
		delete brk;
		delete disp;
		delete random;
	}

	void M6502::sim(TriState inputs[], TriState outputs[], TriState inOuts[])
	{
		TriState n_NMI = inputs[(size_t)InputPad::n_NMI];
		TriState n_IRQ = inputs[(size_t)InputPad::n_IRQ];
		TriState n_RES = inputs[(size_t)InputPad::n_RES];
		TriState PHI0 = inputs[(size_t)InputPad::PHI0];
		TriState RDY = inputs[(size_t)InputPad::RDY];
		TriState SO = inputs[(size_t)InputPad::SO];

		// Logic associated with external input terminals

		TriState PHI1 = NOT(PHI0);
		TriState PHI2 = PHI0;

		prdy_latch1.set(NOT(RDY), PHI2);
		prdy_latch2.set(prdy_latch1.nget(), PHI1);
		TriState n_PRDY = prdy_latch2.nget();

		// Dispatcher and other auxiliary logic

		disp->sim();

		TriState FETCH = TriState::Zero;
		TriState Z_IR = TriState::Zero;

		TriState pd_in[(size_t)PreDecode_Input::Max];
		TriState pd_out[(size_t)PreDecode_Output::Max];
		TriState n_PD[8];

		pd_in[(size_t)PreDecode_Input::PHI2] = PHI2;
		pd_in[(size_t)PreDecode_Input::Z_IR] = Z_IR;

		predecode->sim(pd_in, inOuts, pd_out, n_PD);

		ir->sim(PHI1, FETCH, n_PD);

		TriState ext_in[(size_t)ExtraCounter_Input::Max] = { TriState::Zero };
		TriState ext_out[(size_t)ExtraCounter_Output::Max] = { TriState::Zero };

		ext_in[(size_t)ExtraCounter_Input::PHI1] = PHI1;
		ext_in[(size_t)ExtraCounter_Input::PHI2] = PHI2;

		ext->sim(ext_in, ext_out);

		TriState decoder_in[Decoder::inputs_count];
		TriState decoder_out[Decoder::outputs_count];

		decoder->sim(decoder_in, decoder_out);

		// Random Logic

		random->sim(decoder_out);

		// Bottom Part

		// Outputs

		outputs[(size_t)OutputPad::PHI1] = PHI1;
		outputs[(size_t)OutputPad::PHI2] = PHI2;
	}

}