#pragma once

#include "decoder.h"
#include "flags.h"
#include "regs_control.h"
#include "alu_control.h"
#include "bus_control.h"
#include "pc_control.h"
#include "dispatch.h"
#include "flags_control.h"
#include "branch_logic.h"
#include "random_logic.h"

namespace M6502Core
{
	enum class InputPad
	{
		n_NMI = 0,
		n_IRQ,
		n_RES,
		PHI0,
		RDY,
		SO,
		Max,
	};

	enum class OutputPad
	{
		PHI1 = 0,
		PHI2,
		RnW,
		SYNC,
		A0, A1, A2, A3, A4, A5, A6, A7,
		A8, A9, A10, A11, A12, A13, A14, A15,
		Max,
	};

	enum class InOutPad
	{
		D0 = 0, D1, D2, D3, D4, D5, D6, D7,
		Max,
	};

#pragma pack(push, 1)
	struct DebugInfo
	{
		// Regs & Buses

		uint8_t SB;
		uint8_t DB;
		uint8_t ADL;
		uint8_t ADH;

		// Dispatcher

		// Decoder

		uint8_t decoder_out[Decoder::outputs_count];

		// Control commands

		uint8_t Y_SB;
		uint8_t SB_Y;
		uint8_t X_SB;
		uint8_t SB_X;
		uint8_t S_ADL;
		uint8_t S_SB;
		uint8_t SB_S;
		uint8_t S_S;
		uint8_t NDB_ADD;
		uint8_t DB_ADD;
		uint8_t Z_ADD;
		uint8_t SB_ADD;
		uint8_t ADL_ADD;
		uint8_t ANDS;
		uint8_t EORS;
		uint8_t ORS;
		uint8_t SRS;
		uint8_t SUMS;
		uint8_t ADD_SB7;
		uint8_t ADD_SB06;
		uint8_t ADD_ADL;
		uint8_t SB_AC;
		uint8_t AC_SB;
		uint8_t AC_DB;
		uint8_t ADH_PCH;
		uint8_t PCH_PCH;
		uint8_t PCH_ADH;
		uint8_t PCH_DB;
		uint8_t ADL_PCL;
		uint8_t PCL_PCL;
		uint8_t PCL_ADL;
		uint8_t PCL_DB;
		uint8_t ADH_ABH;
		uint8_t ADL_ABL;
		uint8_t Z_ADL0;
		uint8_t Z_ADL1;
		uint8_t Z_ADL2;
		uint8_t Z_ADH0;
		uint8_t Z_ADH17;
		uint8_t SB_DB;
		uint8_t SB_ADH;
		uint8_t DL_ADL;
		uint8_t DL_ADH;
		uint8_t DL_DB;
		uint8_t n_ACIN;
		uint8_t n_DAA;
		uint8_t n_DSA;
		uint8_t n_1PC;			// From Dispatcher
	};
#pragma pack(pop)

	class PreDecode;
	class IR;
	class ExtraCounter;
	class BRKProcessing;

	class AddressBus;
	class Regs;
	class ALU;
	class ProgramCounter;
	class DataBus;

	class M6502
	{
		BaseLogic::FF nmip_ff;
		BaseLogic::FF irqp_ff;
		BaseLogic::FF resp_ff;
		BaseLogic::DLatch irqp_latch;
		BaseLogic::DLatch resp_latch;

		BaseLogic::DLatch prdy_latch1;
		BaseLogic::DLatch prdy_latch2;

		BaseLogic::DLatch rw_latch;

		BaseLogic::TriState SB[8];
		BaseLogic::TriState DB[8];
		BaseLogic::TriState ADL[8];
		BaseLogic::TriState ADH[8];

		Decoder* decoder = nullptr;
		PreDecode* predecode = nullptr;
		IR* ir = nullptr;
		ExtraCounter* ext = nullptr;
		BRKProcessing* brk = nullptr;
		Dispatcher* disp = nullptr;
		RandomLogic* random = nullptr;

		AddressBus* addr_bus = nullptr;
		Regs* regs = nullptr;
		ALU* alu = nullptr;
		ProgramCounter* pc = nullptr;
		DataBus* data_bus = nullptr;

		BaseLogic::TriState decoder_out[Decoder::outputs_count];
		BaseLogic::TriState rand_out[(size_t)RandomLogic_Output::Max];
		BaseLogic::TriState disp_late_out[(size_t)Dispatcher_Output::Max];

	public:
		M6502();
		~M6502();

		void sim(BaseLogic::TriState inputs[], BaseLogic::TriState outputs[], BaseLogic::TriState inOuts[]);

		void getDebug(DebugInfo* info);
	};
}
