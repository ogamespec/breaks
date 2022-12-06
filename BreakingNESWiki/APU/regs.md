# Регистровые операции

![apu_locator_regs](/BreakingNESWiki/imgstore/apu/apu_locator_regs.jpg)

|Сигнал|Откуда|Куда|Описание|
|---|---|---|---|
|R/W| | | |
|/DBGRD| | | |
|CPU_A\[15:0\]| | | |
|A\[15:0\]| | | |
|/REGRD| | | |
|/REGWR| | | |
|/R4015| | | |
|/R4016| | | |
|/R4017| | | |
|/R4018| | | |
|/R4019| | | |
|/R401A| | | |
|W4000| | | |
|W4001| | | |
|W4002| | | |
|W4003| | | |
|W4004| | | |
|W4005| | | |
|W4006| | | |
|W4007| | | |
|W4008| | | |
|W400A| | | |
|W400B| | | |
|W400C| | | |
|W400E| | | |
|W400F| | | |
|W4010| | | |
|W4011| | | |
|W4012| | | |
|W4013| | | |
|W4014| | | |
|W4015| | | |
|W4016| | | |
|W4017| | | |
|W401A| | | |
|SQA\[3:0\]| | | |
|SQB\[3:0\]| | | |
|TRI\[3:0\]| | | |
|RND\[3:0\]| | | |
|DMC\[6:0\]| | | |
|LOCK| | | |
|OUT\[2:0\]| | | |

Предекодер, для выбора адресного пространства регистров APU:

![pdsel_tran](/BreakingNESWiki/imgstore/apu/pdsel_tran.jpg)

- PDSELR: Промежуточный сигнал для формирования элемента 12-nor для получения сигнала `/REGRD`
- PDSELW: Промежуточный сигнал для формирования элемента 12-nor для получения сигнала `/REGWR`

R/W декодер для регистровых операций:

![reg_rw_decoder_tran](/BreakingNESWiki/imgstore/apu/reg_rw_decoder_tran.jpg)

Выбор регистровой операции:

![reg_select](/BreakingNESWiki/imgstore/apu/reg_select_tran.jpg)

:warning: Выбор адресного пространства регистров APU производится по значению адресной шины CPU (`CPU_Ax`). Но выбор регистра производится по значению адреса, который формируется на адресном мультиплексоре DMA-контроллера (cигналы A0-A4).

## Отладочные регистры

Контакт DBG:

![pad_dbg](/BreakingNESWiki/imgstore/apu/pad_dbg.jpg)

Вспомогательные схемы для DBG:

|Усиливающий инвертер|Промежуточный инвертер|Сигнал /DBGRD|
|---|---|---|
|![dbg_buf1](/BreakingNESWiki/imgstore/apu/dbg_buf1.jpg)|![dbg_not1](/BreakingNESWiki/imgstore/apu/dbg_not1.jpg)|![nDBGRD](/BreakingNESWiki/imgstore/apu/nDBGRD.jpg)|

Транзисторные схемы отладочных регистров:

|Square 0|Square 1|Triangle|Noise|DPCM|
|---|---|---|---|---|
|![square0_debug_tran](/BreakingNESWiki/imgstore/apu/square0_debug_tran.jpg)|![square1_debug_tran](/BreakingNESWiki/imgstore/apu/square1_debug_tran.jpg)|![tri_debug_tran](/BreakingNESWiki/imgstore/apu/tri_debug_tran.jpg)|![noise_debug_tran](/BreakingNESWiki/imgstore/apu/noise_debug_tran.jpg)|![dpcm_debug_tran](/BreakingNESWiki/imgstore/apu/dpcm_debug_tran.jpg)|

Регистровые операции с отладочными регистрами доступны только когда DBG = 1.

Схема LOCK:

![lock_tran](/BreakingNESWiki/imgstore/apu/lock_tran.jpg)

Сигнал `LOCK` используется для временной приостановки тональных генераторов, чтобы их значения были зафиксированы в отладочных регистрах.

## Порты ввода/вывода

Схема для формирования сигналов OUTx:

![out_tran](/BreakingNESWiki/imgstore/apu/out_tran.jpg)

- Выходное значение для контактов `OUT0-2` получается из внутренних сигналов `OUT0-2` (с таким же названием).
- Выходное значение для контактов `/IN0-1` - это внутренние сигналы `/R4016` и `/R4017` с селектора регистров.