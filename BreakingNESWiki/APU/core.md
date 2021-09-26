# Ядро 6502 и сопутствующая логика

В данном разделе описаны особенности ядра и окружающей его вспомогательной логики, предназначенной для интеграции с остальными компонентами.

## Различия между ядром 6502 APU и оригиналом

Внешне ядро 6502 выглядит как копи-паста исходного процессора MOS в уменьшенном варианте.

После детального изучения схемы 2A03 были получены следующие результаты:
- Отличий в декодере не обнаружено
- Флаг D работает как обычно, его можно установить или сбросить, он используется нормальным образом при обработке прерываний (сохраняется в стеке) и после выполнения инструкций PHP/PLP, RTI.
- Рандомная логика отвечающая за генерацию двух контрольных линий DAA (decimal addition adjust) и DSA (decimal subtraction adjust) работает обычным образом.

Отличие заключается в том, что контрольные линии DAA и DSA, отвечающие за включение схем коррекции, отсоединены от схемы, путём вырезания 5 кусочков полисиликона (см. картинку). полисиликон обозначен фиолетовым цветом, вырезанные кусочки обозначены голубым, а места обведены красным.

Это приводит к тому, что схема вычилсения десятичного переноса при сложении и схема добавления/отнимания 6 к результату - не работают. Поэтому встроенный процессор 2A03 всегда считает двоичными числами, даже если флаг D установлен.

Процесс исследования: http://youtu.be/Gmi1DgysGR0

Ключевые узлы по которым был проведен анализ (декодер, рандомная логика, флаги и АЛУ) представлена на следующем изображении:

<img src="/BreakingNESWiki/imgstore/2a03_6502_diff_sm.jpg" width="400px">