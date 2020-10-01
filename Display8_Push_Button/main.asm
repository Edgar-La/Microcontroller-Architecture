;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
;Aqui se definen los Pines  y los bites que seran
	; tanto de entrada como salida.
;Tambien se desactiva la resistencia pull up para
	; el psuh button.
			clr.b	&P1OUT
			mov.b	#11110111b,P1DIR
			bic.b	#3,P1REN
			clr.b	&P2OUT
			mov.b	#0xFF,P2DIR


Tabla
			mov.b	#00111111b, &0x200	;0
			mov.b	#00000110b, &0x202	;1
			mov.b	#01011011b, &0x204	;2
			mov.b	#01001111b, &0x206	;3
			mov.b	#01100110b, &0x208	;4
			mov.b	#01101101b, &0x20A	;5
			mov.b	#01111101b, &0x20C	;6
			mov.b	#00000111b, &0x20E	;7
			mov.b	#01111111b, &0x210	;8
			mov.b	#01101111b, &0x212	;9

inicio		mov 	#0x200, R4
manda		mov.b	@R4+, &P2OUT
ciclo		bit.b	#0x08, &P1IN		;Verifica estado del push button
			jnz		ciclo				;Se mantiene en el ciclo
			call	#soltar
			inc		R4					;Para incrementar el numero guardado en la tabla.
			cmp		#0x214, R4			;Verifica si ya se llegó al numero 9
			jne		manda				;Si no, se repite la iteracion de incremento
			jmp		inicio				;Se reinicia el ciclo


soltar		bit.b	#0x08,	&P1IN		;Verifica estado del push button
			jz		soltar				;Se mantiene en el ciclo
			ret							;Rgresa a a donde fue llamado

retardo		mov		#10000, R15
nueve		dec		R15
			jnz		nueve
			ret

;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
