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

             clr.b	&P1OUT
             mov.b	#11110111b, P1DIR		; Configuro P1.3 como entrada
             bic.b	#3,P1REN				; Desactivo resistencia pullup

             clr.b	&P2OUT					;
             mov.b	#0xFF, P2DIR			;


             ; Aqui empiezo a programar el controlador
             ; Contador de 0 a 9
inicio       mov.b	#00111111b, P2OUT		; Muestro el numero 0
			 call 	#retardo

             mov.b	#00000110b, P2OUT		; Muestro el numero 1
			 call 	#retardo

           	 mov.b	#01011011b, P2OUT		; Muestro el numero 2
			 call 	#retardo

             mov.b	#01001111b, P2OUT		; Muestro el numero 3
			 call 	#retardo

             mov.b	#01100110b, P2OUT		; Muestro el numero 4
			 call 	#retardo

             mov.b	#01101101b, P2OUT		; Muestro el numero 5
			 call 	#retardo

             mov.b	#01111101b, P2OUT		; Muestro el numero 6
			 call 	#retardo

             mov.b	#00000111b, P2OUT		; Muestro el numero 7
			 call 	#retardo

             mov.b	#01111111b, P2OUT		; Muestro el numero 8
			 call 	#retardo

             mov.b	#01101111b, P2OUT		; Muestro el numero 9
			 call 	#retardo

			 jmp inicio						; Se repie el ciclo

retardo		 mov #6000, R15
restar 		 dec R15
			 jnz restar
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
            
