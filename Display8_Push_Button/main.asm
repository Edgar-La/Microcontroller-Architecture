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
			mov.b	#10,R12		; Se define la variable comparadora.


Reset		clr.b	R10			; Aqui se reseta nuestro contador, para recomenzar el ciclo


NextNum		call 	#Tabla
Apretar		mov.b	R11,&P2OUT		;Numero que aparece en el display
			bit.b	#0x08,&P1IN		;Verfica el estado del push button
			jz		Apretar			;Si es 1 se mantiene en el ciclo
			call	#Soltar			;Si es cero sale, y llama a Soltar
			inc 	R10				;Se incrementa el contador
			cmp		R10, R12		;Compara si el contador es igual a 10
			jeq		Reset			;Si es igual a 10, se reinicia, sino sigue
			jmp		NextNum			;Si no fue 10, avanza a sig. iteracion


Soltar		bit.b	#0x08,	&P1IN	;Verifica estado del push button
			jnz		Soltar			;Se mantiene en el ciclo
			ret						;Rgresa a a donde fue llamado


Tabla		mov.b	R10, R13
			add		R13, R13
			mov.b	R13, R14
			add		R13, R14
			add		R13, R14
			add		R14,	PC
			mov.b	#00111111b,R11	;Aparece en display 0
			ret
			mov.b	#00000110b,R11	;Aparece en display 1
			ret
			mov.b	#01011011b,R11	;Aparece en display 2
			ret
			mov.b	#01001111b,R11	;Aparece en display 3
			ret
			mov.b	#01100110b,R11	;Aparece en display 4
			ret
			mov.b	#01101101b,R11	;Aparece en display 5
			ret
			mov.b	#01111101b,R11	;Aparece en display 6
			ret
			mov.b	#00000111b,R11	;Aparece en display 7
			ret
			mov.b	#01111111b,R11	;Aparece en display 8
			ret
			mov.b	#01101111b,R11	;Aparece en display 9
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
            
