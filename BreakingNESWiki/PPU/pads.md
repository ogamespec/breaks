# Контакты PPU

![ppu_pads](/BreakingNESWiki/imgstore/ppu_pads.jpg)

|Название|Направление|Описание|
|---|---|---|
|R/W	|в PPU	|Read-notWrite. Используется для чтения/записи регистров PPU. Если R/W = 1, то производится чтение, иначе запись. Запомнить контакт легко : "Читаем(1), не пишем".|
|D0-D7	|двунаправленная	|Шина данных для передачи значений регистров. Когда /DBE = 1 шина отсоединена (Z)|
|RS0-RS2	|в PPU	|Register Select. Задается номер регистра PPU (0-7)|
|/DBE	|в PPU	|Data Bus Enable. Если /DBE = 0, то шина D0-D7 используется для обмена значений с регистрами PPU, иначе шина отсоединена.|
|EXT0-EXT3	|двунаправленная	|Шина используется для подмешивания цвета текущего пикселя с другого PPU, или выдачи текущего цвета наружу. Направление шины определяется разрядом регистра $2002\[6\] (0: input, 1: output)|
|CLK	|в PPU	|Тактовый сигнал|
|/INT	|из PPU	|Сигнал прерывания PPU (VBlank)|
|ALE	|из PPU	|Address Latch Enable. Если ALE=1, то шина AD0-AD7 работает как адресная шина (A0-A7), иначе она работает как шина данных (D0-D7)|
|AD0-AD7	|ALE=1: из PPU (адрес), ALE=0: двунаправленная (данные)	|Мультиплексированная шина адреса/данных. Когда ALE=1 шина работает как адресная, когда ALE=0 по шине передаются данные в PPU (паттерны, атрибуты), или наружу с порта PPU (регистра $2007)|
|A8-A13	|из PPU (адрес)	|По этой шине передается остальная часть адресных линий.|
|/RD	|из PPU	|/RD=0: шина данных PPU (AD0-AD7) используется для чтения|
|/WR	|из PPU	|/WR=0: шина данных PPU (AD0-AD7) используется для записи|
|/RES	|в PPU	|/RES=0: произвести сброс PPU|
|VOUT	|из PPU	|Композитный видеосигнал|

Условно контакты можно поделить на следующие группы:
- Интерфейс с CPU
- Интерфейс с VRAM
- Интерфейс с другими PPU
- Управляющие сигналы
- VOUT

## Интерфейс с CPU

Интерфейс с CPU используется для получения доступа к регистрам PPU. К данной группе контактов относятся:
- R/W
- D0-D7
- RS0-RS2
- /DBE

### R/W

<img src="/BreakingNESWiki/imgstore/20181128-101155.png" width="600px">

Сигнал R/W определяет направление обмена данных по шине D0-D7:
- R/W=0: Write. Шина данных становится input
- R/W=1: Read. Шина данных становится output

### D0-D7

<img src="/BreakingNESWiki/imgstore/20181128-101050.png" width="600px">

Шина данных D0-D7 используется для обмена данными между CPU и регистрами PPU.

Индекс регистра выбирается контактами RS0-RS2.

### RS0-RS2

<img src="/BreakingNESWiki/imgstore/20181128-100949.png" width="600px">

Сигналы RS0-RS2 выбирают индекс регистра PPU (0-7) для обмена данными с CPU.

### /DBE

<img src="/BreakingNESWiki/imgstore/20181128-100801.png" width="600px">

Контакт запрещает обмен по шине D0-D7, то есть полностью отключает интерфейс с CPU.

- /DBE=0: Интерфейс с CPU включен
- /DBE=1: Интерфейс с CPU отключен

## Интерфейс с VRAM

Больше половины логики PPU предназначена для выборки, хранения и выдачи наружу (в виде видеосигнала) данных из VRAM. К данной группе контактов относятся:
- ALE
- AD0-AD7
- A8-A13
- /RD
- /WR

### ALE

<img src="/BreakingNESWiki/imgstore/20181128-101334.png" width="600px">

Сигнал ALE (Address Latch Enable) используется для мультиплексирования шины AD0-AD7:
- Когда ALE=1 шина AD0-AD7 работает как адресная шина VRAM (A0-A7)
- Когда ALE=0 шина AD0-AD7 работает как шина данных VRAM (D0-D7)

Данный трюк был широко распространен в те времена, для уменьшения количества контактов.

В современных микросхемах мультиплексирование шин стало реже использоваться, так как оно требует дополнительных тактов на перевод шины из одного состояния в другое да и технологические нормы позволяют разделить шины.

### AD0-AD7

<img src="/BreakingNESWiki/imgstore/20181128-101650.png" width="600px">

Двунаправленная мультиплексируемая шина данных/адреса для обмена данными с VRAM.

### A8-A13

<img src="/BreakingNESWiki/imgstore/20181128-101736.png" width="600px">

Шина адреса VRAM.

Работает только на выход (output).

### /RD

<img src="/BreakingNESWiki/imgstore/20181128-101819.png" width="600px">

Сигнал /RD является комплементарным сигналу /WR (они не могут принимать одинаковые значения).

Когда /RD=0 шина данных AD0-AD7 используется для чтения данных VRAM (input).

### /WR

<img src="/BreakingNESWiki/imgstore/20181128-101848.png" width="600px">

Сигнал /WR является комплементарным сигналу /RD (они не могут принимать одинаковые значения).

Когда /WR=0 шина данных AD0-AD7 используется для записи данных VRAM (output).

Сигналы /RD и /WR можно перепутать с внутренними сигналами /RD\_internal и /WR\_internal, которые получаются из входного сигнала R/W схемой [RW декодера](regs.md).

## Интерфейс с другими PPU

Данный интерфейс реализуется inout контактами EXT0-EXT3.

<img src="/BreakingNESWiki/imgstore/20181128-100636.png" width="600px">

Разработчики предусмотрели взаимодействие нескольких PPU. Схема взаимодействия немудреная и выглядит следующим образом:
- Внутри PPU находится [мультиплексор](mux.md), который по выбору может направлять "картинку" как на экран, так и на внешние контакты EXT
- Также мультиплексор может получать "картинку" с внешних контактов EXT

Под понятием "картинка" подразумевается некий набор абстрактных видеоданных, чтобы пояснить суть взаимодействия между PPU.

Таким образом PPU могут соединяться по цепочке и каждый из PPU может "подмешивать" свою часть изображения к результирующей "картинке".

На практике такая схема (насколько мне известно) не применялась, возможно потому что у PPU нет сигнала для синхронизации (SYNC) между несколькими PPU. Без такого сигнала сложно синхронизировать обмен данными по контактам EXT, так как не понятно что сейчас делать - брать новые данные или отдавать их наружу.

## Управляющие сигналы

### CLK

![PPU clk](/BreakingNESWiki/imgstore/clk.jpg)

(контактная площадка не показана)

Входной CLK разводится на два внутренних комплементарных сигнала: CLK и /CLK.

CLK используется исключительно в фазогенераторе видеотракта PPU.

Все остальные схемы тактируются посредством [Pixel Clock](pclk.md)

### /RES

![PPU resetpad](/BreakingNESWiki/imgstore/resetpad.jpg)

(контактная площадка не показана)

После прихода внешнего сигнала /RES = 0 защелка устанавливается, чтобы "не потерять" сигнал сброса.
Защелка остается установленной до тех пор, пока не будет очищена `RESCL` = 1.

Выходное значение защелки подается на схему очистки регистров (сигнал `RC` - Register Clear).

При включении питания защелка `Reset FF` (на рисунке отмечена желтым гексагоном) принимает неопределенное значение (x).

Схема полностью асинхронная и не зависит от CLK.

### /INT

<img src="/BreakingNESWiki/imgstore/20181128-101916.png" width="600px">

Выходной сигнал /INT используется для сигнализации CPU о прерывании VBlank.

В NES сигнал /INT заведен на сигнал /NMI процессора 6502.

## VOUT

Выходной аналоговый видеосигнал.