; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a, b, c, d - byte
; c - (a + d) + (b + d)
; ex: a = 4; b = 3; c = 10; d = 2 => 10 - (4 + 2) + (3 + 2) = 10 - 6 + 5 = 9

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 4
	b  db 3
    c  db 10
    d  db 2
segment  code use32 class=code ; code segment
start: 
    mov  AL, 0 ;AL = 0
	mov  AL, [a] ;AL = a
    add  AL, [d] ;AL = AL + d = a + d

    sub [c], AL  ;c = c - AL = c - (a + d)
    
    mov AL,  [b] ;AL = b
    add AL,  [d] ;AL = AL + d = b + d
    
    add [c], AL  ;c = c + AL = c + (b + d) = c - (a + d) + (b + d)
	
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution ofthe program