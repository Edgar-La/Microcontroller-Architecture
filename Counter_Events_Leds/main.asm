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

			; Inicializar el puerto	PxOUT
            clr.b     &P1OUT
            clr.b     &P1IN
			; Configurar las entradas y salidas del puerto PxDIR
            ; Escribo 0 en el PxDIR para volver entrada la correspondiente patita
            ; Escribo 1 en el PxDIR para volver salida la correspondiente patita
            ; Puerto 1 [0 1 0 0 0 0 0 1] = [P1.7 P1.6 P1.5 01.4 P1.3 P1.2 P1.1 P1.0] = [X Out X X In X X Out]
            ;P1.6 -> LED verde		; P1.0 -> LED rojo
            mov.b    #01000001b, &P1DIR		;0x41
            ; Tengo que desabilitar las resistencias pullup de las entradas
            ; en este caso la entrada está en P1.3	P1 = [1 1 1 1 0 1 1 1] -> 0xF7
            bic.b    #0x08, &P1REN			;bit clear, de P1REN y del bit 3
            ; La otra forma (creo es) mov.b  b'11110111', P1REN



inicio		bit.b	#0x08, &P1IN
			jnz      aprieto1		; Si el bit 3 de P1IN esta en uno brincare a la seccion del programa etiquetada como aprieto1 ; Jump to label if zero bit is set
            jmp     inicio			; Si el bit 3 de P1IN esta en cero se regresa a inicio
;-------------------------------------

aprieto1    mov.b   #0x01, &P1OUT
            bit.b   #0x08, &P1IN
            jz      aprieto1
            jmp     suelto1

suelto1     bit.b   #0x08, &P1IN
            jz      aprieto2
            jmp     suelto1
;-------------------------------------

aprieto2    mov.b    #0x40, &P1OUT
            bit.b   #0x08, &P1IN
            jz      aprieto2
            jmp     suelto2

suelto2     bit.b   #0x08, &P1IN
            jz      aprieto3
            jmp     suelto2
;-------------------------------------

aprieto3    mov.b    #0x41, &P1OUT
            bit.b   #0x08, &P1IN
            jz      aprieto3
            jmp     suelto3

suelto3     bit.b   #0x08, &P1IN
            jz      aprieto4
            jmp     suelto3
;-------------------------------------

aprieto4    mov.b   #0x00, &P1OUT
            bit.b   #0x08, &P1IN
            jz      aprieto4
            jmp     suelto4

suelto4     bit.b   #0x08, &P1IN
            jz      inicio
            jmp     suelto4

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
            
