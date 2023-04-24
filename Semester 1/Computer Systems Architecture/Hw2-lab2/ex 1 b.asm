; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a, b, c, d - word
; (c + b + a) - (d + d)
; ex: a = 10; b = 30; c = 40; d = 20=>(40 + 30 + 10)-(20 + 20) = 40

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  dw 10
	b  dw 30
    c  dw 40
    d  dw 20
segment  code use32 class=code ; code segment
start: 
    mov  AX, 0 ;AX = 0
	mov  AX, [b] ;AX = b
    add  [c], AX ;c = c + AX = c + b
    mov  AX, [a] ;AX = a
    add  [c], AX ;c = c + AX = c + b + a
    
    mov  AX, [d] ;AX = d
    add  AX, [d] ;AX = AX + d = d + d
    
    sub [c], AX  ;c = c - AX = (c + b + a) - (d + d)
    
	
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution ofthe program
