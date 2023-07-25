; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a - byte; b - word; c - double word; d - qword; - Unsigned representation
; (a - b) + (c - b - d) + d
; ex: a = 4; b = 3; c = 90; d = 80 => (4-3) + (90-3-80) + 80=1+7+80=88

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 4
	b  dw 3
    c  dd 90
    d  dq 80
    r resq 1 ;reserve 1 quadword in memory to save the result
    
segment  code use32 class=code ; code segment
start: 
	mov  AL, [a] ;AL = a
    mov  AH, 0 ;converting AL to AX/ byte to word
    sub  AX, [b] ;AX = AX - b = a - b 
    mov  DX, 0 ;converting AX to DX:AX
    mov  EDX, 0 ;converting EAX to EDX:EAX
    
    mov EBX, [c] ;EBX = c
    sub EBX, [b] ;EBX = c - b
    mov ECX, 0 ;conversion from edx to ecx:ebx, ECX:EBX = c - b
    sub EBX, dword [d]
    sbb EBX, dword [d+4]; ECX:EBX = c - b - d

    clc ;clear carry flag
    add EAX, EBX ;eax = eax + ebx
    adc EDX, ECX ;edx = edx + ecx + cf
    
    clc ;clear carry flag
	add EAX, dword [d]
    adc EAX, dword [d+4] ;edx:eax = (a - b) + (c - b - d) + d
    
    mov dword [r+0], eax 
	mov dword [r+4], edx 
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution ofthe program