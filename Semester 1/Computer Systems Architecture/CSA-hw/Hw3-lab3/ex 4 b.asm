; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a - byte; b - word; c - double word; d - qword; - Signed representation
; (b + b) - c - (a + d)
; ex: a = 10; b = 90; c = 4; d = 80 => 180 - 4 - 90 = 86 

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 10
	b  dw 90
    c  dd 4
    d  dq 80
    r resq 1 ;reserve 1 quadword in memory to save the result
    
segment  code use32 class=code ; code segment
start: 
    mov AX, [b] ;AX = b
    add AX, [b] ;AX = b + b
    cwde ;converting AX to EAX
    sub EAX, [c] ;EAX = (b + b) - c
    cdq ;converting  EAX to EDX:EAX
    mov EBX, EAX
    mov ECX, EDX
    
    mov AL, [a] ; AL = a
    cbw ;converting AL to AX
    cwde ;converting AX to EAX
    cdq ;converting  EAX to EDX:EAX
    add EAX, dword [d]
    adc EAX, dword [d+4]; 

    clc ;clear carry flag
    sub EBX, EAX ;ebx = ebx - eax
    sbb ECX, EDX ;ecx = ecx - edx - cf
    
    mov dword [r+0], ebx 
	mov dword [r+4], ecx 
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution ofthe program