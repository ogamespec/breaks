# Breaking NES Wiki

Данный ресурс содержит исчерпывающую информацию по трём микросхемам: [MOS](MOS.md) [6502](6502/Readme.md), [Ricoh](Ricoh.md) 2A03 и Ricoh 2C02.

Микросхемы 2A03 ([APU](APU/Readme.md)) и 2С02 ([PPU](PPU/Readme.md)) являются основой игровой приставки Nintendo NES, Famicom и их [многочисленных аналогов](Dendy.md).

Поскольку процессор 6502 в немного "урезанном" варианте входит в состав микросхемы 2A03, он изучается отдельно.

Процессор 6502:

<img src="/BreakingNESWiki/imgstore/mos_6502ad_top.jpg" width="300px">

Микросхемы APU и PPU различных ревизий:

<img src="/BreakingNESWiki/imgstore/2701408_600px.jpg" width="400px">

## Источник информации

Источником информации являются микрофотографии микросхем в высоком разрешении.

В то время микросхемы были очень простые и производились по технологии [[NMOS]], с одним поверхностным слоем металла. Поэтому для получения векторных масок достаточно сделать два типа фотографий: фотографию поверхности с металлом и фотографию без металла. Обычно для снятия металла со старых микросхем применяют кипящую кислоту.

Микросхемы под микроскопом выглядят примерно вот так (6502, APU и PPU соответственно):

<img src="/BreakingNESWiki/imgstore/6502_die_shot.jpg" width="180px"> <img src="/BreakingNESWiki/imgstore/apu_die_shot.jpg" width="200px"> <img src="/BreakingNESWiki/imgstore/ppu_die_shot.jpg" width="210px">

После получения векторных масок на них производится поиск транзисторов, которые в итоге формируют логическую схему.
Процесс создания векторных масок, рисование транзисторных и логических схем подробно освещён в моих стримах.

## Структура и назначение вики

Все основные фото и видео-материалы вы можете найти на [главном сайте проекта](http://breaknes.com).

В функции вики входит подробное описание всех функциональных блоков микросхем, с результатами программной симуляции каждого блока. Тем самым мы постепенно заменяем раздел "Чтиво" с главного сайта, поскольку там не очень удобно было отслеживать изменения. А тут вы можете сразу узнать что новенького :smiley:

Вики разделена на 3 раздела, по количеству изучаемых микросхем. Через навигационное меню можно ознакомиться с основными функциональными блоками каждой микросхемы.

Каждый раздел представляет собой подробное рассмотрение вначале транзисторной схемы, потом логической схемы и в результате производится симуляция всего блока, для проверки логики его работы. В качестве "базовой" логики используются следующие "примитивы" на языке Си:
```c
#define BIT(n)     ( (n) & 1 )    // вырезать все лишнее
int NOT(int a) { return (~a & 1); }       // НЕ
int NAND(int a, int b) { return ~((a & 1) & (b & 1)) & 1; }     // И-НЕ
int NOR(int a, int b) { return ~((a & 1) | (b & 1)) & 1; }      // ИЛИ-НЕ
```

Также в некоторых местах в конце раздела приводится Verilog для изучаемой схемы.

Как обычно, для понимания материала необходимо знание микроэлектроники и программирования. Раньше требовался туго набитый косячок, но после различных собеседований в разных компаниях когда я показывал вики как своё портфолио - эту шутку воспринимали буквально, поэтому я убрал это требование.

Приятного просмотра!