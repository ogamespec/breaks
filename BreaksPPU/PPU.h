
// Pads.
enum {
    PPU_CLK,        // clock input
    PPU_nRES,       // /RES
    PPU_nINT,       // /INT (vblank interrupt)
    PPU_EXT,        // external bus
    PPU_nDBE,       // /DBE
    PPU_RS,         // register select bus
    PPU_D,          // register data bus
    PPU_RW,         // register data bus direction
    PPU_ALE,        // address latch
    PPU_AD,         // address/data bus to external PPU memory
    PPU_nRD,        // /RD
    PPU_nWR,        // /WR
};

// ------------------------------------------------------------------------
// Control lines

enum {
    PPU_CTRL_RES,           // inverted /RES
    PPU_CTRL_RC,            // register clear
    PPU_CTRL_RESCL,         // clear reset flip/flop
    PPU_CTRL_nCLK,          // /CLK
    PPU_CTRL_VIN,           // V-counter input
    PPU_CTRL_HC,            // H-counter clear
    PPU_CTRL_VC,            // V-counter clear
    PPU_CTRL_PCLK, PPU_CTRL_nPCLK,  // pixel clock phases

    PPU_CTRL_MAX,
};

// ------------------------------------------------------------------------
// Individual static and dynamic latches (flip/flops)

enum {
    PPU_FF_RESET,           // reset flip/flop
    PPU_FF_PCLK0, PPU_FF_PCLK1, PPU_FF_PCLK2, PPU_FF_PCLK3, // pixel clock div/4 latches
    PPU_FF_HC,              // H-counter clear

    PPU_FF_MAX,
};

// ------------------------------------------------------------------------
// Registers

enum {
    PPU_REG_HIN, PPU_REG_HOUT,    // H-counter
    PPU_REG_VIN, PPU_REG_VOUT,    // V-counter

    PPU_REG_MAX,
};

// ------------------------------------------------------------------------
// Buses

enum {
    PPU_BUS_DB,             // internal data bus
    PPU_BUS_H, PPU_BUS_V,   // H/V counter outputs
    PPU_BUS_PAL,            // palette index
    PPU_BUS_OAM,            // OAM index
    PPU_BUS_PD,             // PPU data

    PPU_BUS_MAX,
};

// ------------------------------------------------------------------------
// Memory offsets

enum {
    PPU_MEM_OAM = 0,
    PPU_MEM_TEMP = 256,
    PPU_PALETTE = 288,
};    

// ------------------------------------------------------------------------
// Debug

enum {
    PPU_DEBUG_PIXCOUNT,

    PPU_DEBUG_MAX,
};

// ------------------------------------------------------------------------
// Context.

typedef struct ContextPPU
{
    float    vid;               // video output (composite video, normalized to 1.0)
    unsigned long pad[12];      // I/O pads and external buses
    int     latch[PPU_FF_MAX];       // individual latches
    int     ctrl[PPU_CTRL_MAX];      // control lines
    unsigned long reg[PPU_REG_MAX][16];  // registers
    unsigned char mem[256+32+64];    // primary OAM, secondary OAM, palette
    unsigned long bus[PPU_BUS_MAX][16];  // internal buses
    int     debug[PPU_DEBUG_MAX];    // debug variables
} ContextPPU;

// Emulate single PPU clock.
void PPUStep (ContextPPU *ppu);
