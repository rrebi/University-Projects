; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a, b, c - byte, d - word
; ((a+b-c)*2 + d-5)*d
; ex. 1: a = 10; b = 5; c = 9; d = 2 Result: ((10+5-9)*2+2-5)*2=(6*2+2-5)*2=(12+2-5)*2=9*2=18

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 10
	b  db 5
    c  db 9
    d  dw 2
segment  code use32 class=code ; code segment
start: 
	mov AL, [a] ;AL=a
    add AL, [b] ;AL=AL+b=a+b
    sub AL, [c] ;AL=AL-c=a+b-c
    mov CL, 2 ;CL=2
    mul CL  ;AX=AL*CL=(a+b-c)*2
	
    add AX, [d] ;AX=AX+d=(a+b-c)*2+d
    sub AX, 5 ;AX=AX-5=(a+b-c)*2+d-5
    
    mov CX, [d] ;cx=2
    mul CX ;AX=AX*CX
    
    push CX ;the high part of the doubleword DX:AX is saved on the stack
    push AX ;the low part of the doubleword DX:AX is saved on the stack
    pop EAX ;EAX= CX:AX = ((a+b-c)*2+d-5)*2
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of the program
