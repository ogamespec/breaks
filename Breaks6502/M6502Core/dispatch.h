#pragma once

namespace M6502Core
{
	// Some of the outputs from the earlier stages of the dispatcher are used as inputs for later stages.
	// Signals are sorted, if possible, in order from earlier use, to later use.

	enum class Dispatcher_Input
	{
		PHI1 = 0,
		PHI2,
		RDY,
		DORES,
		B_OUT,
		ACR,

		RESP,
		BRK6E,
		BRFW,
		n_BRTAKEN,
		n_TWOCYCLE,
		n_IMPLIED,
		PC_DB,
		n_ADL_PCL,
		n_ready,
		T0,
		T5,
		T6,
		ACRL1,
		ACRL2,
		Max,
	};

	enum class Dispatcher_Output
	{
		T0 = 0,
		n_T0,
		n_T1X,
		Z_IR,
		FETCH,
		n_ready,
		WR,
		TRES2,
		ACRL1,
		ACRL2,

		T1,
		T5,
		T6,
		n_1PC,

		ENDS,
		ENDX,
		TRES1,
		TRESX,

		Max,
	};

	class Dispatcher
	{
		BaseLogic::DLatch acr_latch1;
		BaseLogic::DLatch acr_latch2;

		BaseLogic::DLatch t56_latch;
		BaseLogic::DLatch t5_latch1;
		BaseLogic::DLatch t5_latch2;
		BaseLogic::DLatch t6_latch1;
		BaseLogic::DLatch t6_latch2;
		
		BaseLogic::DLatch tres2_latch;
		BaseLogic::DLatch tresx_latch1;
		BaseLogic::DLatch tresx_latch2;

		BaseLogic::DLatch fetch_latch;
		BaseLogic::DLatch wr_latch;
		BaseLogic::DLatch ready_latch1;
		BaseLogic::DLatch ready_latch2;

		BaseLogic::DLatch ends_latch1;
		BaseLogic::DLatch ends_latch2;

		BaseLogic::DLatch nready_latch;
		BaseLogic::DLatch step_latch1;
		BaseLogic::DLatch step_latch2;
		BaseLogic::DLatch t1_latch;

		BaseLogic::DLatch comp_latch1;
		BaseLogic::DLatch comp_latch2;
		BaseLogic::DLatch comp_latch3;

		BaseLogic::DLatch rdydelay_latch1;
		BaseLogic::DLatch rdydelay_latch2;

		BaseLogic::DLatch t0_latch;
		BaseLogic::DLatch t1x_latch;

		BaseLogic::DLatch br_latch1;
		BaseLogic::DLatch br_latch2;
		BaseLogic::DLatch ipc_latch1;
		BaseLogic::DLatch ipc_latch2;
		BaseLogic::DLatch ipc_latch3;

	public:
		
		void sim_BeforeDecoder(BaseLogic::TriState inputs[], BaseLogic::TriState outputs[]);

		void sim_BeforeRandomLogic(BaseLogic::TriState inputs[], BaseLogic::TriState d[], BaseLogic::TriState outputs[]);

		void sim_AfterRandomLogic(BaseLogic::TriState inputs[], BaseLogic::TriState d[], BaseLogic::TriState outputs[]);

		BaseLogic::TriState getTRES2();

		BaseLogic::TriState getT1();

		BaseLogic::TriState getSTOR(BaseLogic::TriState d[]);
	};
}
