#pragma once

namespace M6502Core
{
	enum class AddressBus_Input
	{
		PHI1 = 0,
		PHI2,
		Z_ADL0,
		Z_ADL1,
		Z_ADL2,
		Z_ADH0,
		Z_ADH17,
		ADL_ABL,
		ADH_ABH,
		Max,
	};

	class AddressBus
	{
		BaseLogic::FF ABL[8];
		BaseLogic::FF ABH[8];

	public:

		void sim_ConstGen(BaseLogic::TriState inputs[], BaseLogic::TriState ADL[], BaseLogic::TriState ADH[], bool ADL_Dirty[8], bool ADH_Dirty[8]);

		void sim_Output(BaseLogic::TriState inputs[], BaseLogic::TriState ADL[], BaseLogic::TriState ADH[], BaseLogic::TriState cpu_out[]);

		uint8_t getABL();
		uint8_t getABH();
	};
}
