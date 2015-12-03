#include <avr/io.h>

.global joystick_init_asm
.global adc_get_asm
.global joystick_status_asm

.section .text

joystick_init_asm:
push r16
push r17

;adc_init()
ldi r16, (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2)
sts ADCSRA, r16

ldi r16, (0 << MUX5) | (0 << ADTS0) | (0 << ADTS1) | (0 << ADTS2)
sts ADCSRB, r16

ldi r16, (1 << REFS0)
sts ADMUX, r16

ldi r16, ~(0x02|0x01)
lds r17, DDRF
and r17,r16
sts DDRF,r17

ldi r16, ~(0x02|0x01)
lds r17, PORTF
and r17,r16
sts PORTF,r17

ldi r24, 0x01
call adc_get_asm

ldi r25, 0x02
call adc_get_asm

pop r17
pop r16
ret


adc_get_asm:
push r16
push r17

ldi r16, (1 << REFS0)
ldi r17, 0x07
and r17, r24
or r16, r17
sts ADMUX, r16


ldi r17, (1<<ADSC)
lds r16, ADCSRA
or r16, r17
sts ADCSRA, r16

bw1:
lds r17, ADCSRA
sbrc r17, ADSC
jmp bw1

lds r24, ADCL
lds r25, ADCH

pop r17
pop r16

ret

joystick_status_asm:
push r16
push r17

ldi r24, 0x00
call adc_get_asm
call compute_x
mov r16,r24

ldi r24, 0x01
call adc_get_asm
call compute_y
mov r17,r24

mov r24,r16
mov r25,r17

pop r17
pop r16
ret