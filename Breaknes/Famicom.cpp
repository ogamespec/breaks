#include "pch.h"

using namespace BaseLogic;

namespace Breaknes
{
	Famicom::Famicom()
	{
		core = new M6502Core::M6502;
	}

	Famicom::~Famicom()
	{
		delete core;
	}

	void Famicom::sim()
	{
		TriState core_inputs[(size_t)M6502Core::InputPad::Max];
		TriState core_outputs[(size_t)M6502Core::OutputPad::Max];
		TriState core_inOuts[(size_t)M6502Core::InOutPad::Max];

		// DEBUG: Clear the data bus for debugging the logic

		for (size_t n = 0; n < (size_t)M6502Core::InOutPad::Max; n++)
		{
			core_inOuts[n] = TriState::Zero;
		}

		core_inputs[(size_t)M6502Core::InputPad::RDY] = TriState::One;
		core_inputs[(size_t)M6502Core::InputPad::PHI0] = CLK;

		core->sim(core_inputs, core_outputs, core_inOuts);

		CLK = CLK == TriState::Zero ? TriState::One : TriState::Zero;
	}
}