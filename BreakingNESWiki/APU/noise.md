# Генератор шума

![apu_locator_noise](/BreakingNESWiki/imgstore/apu/apu_locator_noise.jpg)

![NOISE](/BreakingNESWiki/imgstore/apu/NOISE.jpg)

## Frequency Reg

![noise_freq_in_tran](/BreakingNESWiki/imgstore/apu/noise_freq_in_tran.jpg)

![NOISE_FreqReg](/BreakingNESWiki/imgstore/apu/NOISE_FreqReg.jpg)

![RegisterBitRes](/BreakingNESWiki/imgstore/apu/RegisterBitRes.jpg)

Используется вариация регистра с дополнительным сбросом (сразу на защёлку).

## Decoder

![noise_decoder_tran](/BreakingNESWiki/imgstore/apu/noise_decoder_tran.jpg)

![NOISE_Decoder](/BreakingNESWiki/imgstore/apu/NOISE_Decoder.jpg)

Первая стадия декодера (демультиплексор 4-to-16):

```
00000000 11111111
11111111 00000000
00001111 00001111
11110000 11110000
00110011 00110011
11001100 11001100
01010101 01010101
10101010 10101010
```

Вторая стадия декодера:

```
11101111 11111111
10001011 11110111
00111100 11001111
11111110 11110011
01100111 00011111
11110010 00000011
11111111 11000111
11011110 11100001
11011001 01111111
11000001 00010000
11011010 00000111
```

Битовая маска топологическая. 1 означает есть транзистор, 0 означает нет транзистора.

|![NOISE_Decoder1](/BreakingNESWiki/imgstore/apu/NOISE_Decoder1.jpg)|![NOISE_Decoder2](/BreakingNESWiki/imgstore/apu/NOISE_Decoder2.jpg)|
|---|---|

|Decoder In|Decoder Out|
|---|---|
|0|0x002|
|1|0x00a|
|2|0x0aa|
|3|0x2bb|
|4|0x139|
|5|0x173|
|6|0x063|
|7|0x067|
|8|0x1a9|
|9|0x106|
|10|0x227|
|11|0x062|
|12|0x642|
|13|0x20f|
|14|0x300|
|15|0x140|

## Frequency LFSR

![noise_freq_lfsr_tran](/BreakingNESWiki/imgstore/apu/noise_freq_lfsr_tran.jpg)

![noise_freq_control_tran](/BreakingNESWiki/imgstore/apu/noise_freq_control_tran.jpg)

![NOISE_FreqLFSR](/BreakingNESWiki/imgstore/apu/NOISE_FreqLFSR.jpg)

![FreqLFSRBit](/BreakingNESWiki/imgstore/apu/FreqLFSRBit.jpg)

## Random LFSR

![noise_random_lfsr_tran](/BreakingNESWiki/imgstore/apu/noise_random_lfsr_tran.jpg)

![noise_feedback_tran](/BreakingNESWiki/imgstore/apu/noise_feedback_tran.jpg)

![NOISE_RandomLFSR](/BreakingNESWiki/imgstore/apu/NOISE_RandomLFSR.jpg)

![RandomLFSRBit](/BreakingNESWiki/imgstore/apu/RandomLFSRBit.jpg)

Дизайн регистра сдвига для ДСЧ отличается тем, что значение хранится в регистре (статическая память), т.к. между сдвигом значения может пройти значительное время и поэтому нельзя использовать регистры сдвига на динамической памяти (DLatch).

## Envelope

![noise_envelope_rate_counter_tran](/BreakingNESWiki/imgstore/apu/noise_envelope_rate_counter_tran.jpg)

![noise_envelope_control_tran](/BreakingNESWiki/imgstore/apu/noise_envelope_control_tran.jpg)

![noise_envelope_counter_tran](/BreakingNESWiki/imgstore/apu/noise_envelope_counter_tran.jpg)

Схема идентична схеме Envelope прямоугольных каналов. На транзисторной схеме пометки промежуточных сигналов могут отличаться, но не обращайте на это внимание, по контексту всё должно быть понятно.

![EnvelopeUnit](/BreakingNESWiki/imgstore/apu/EnvelopeUnit.jpg)

|Сигнал EnvelopeUnit|Noise Channel|
|---|---|
|WR_Reg|W400C|
|WR_LC|W400F|
|LC|RND/LC|

## Output

![noise_output_tran](/BreakingNESWiki/imgstore/apu/noise_output_tran.jpg)
