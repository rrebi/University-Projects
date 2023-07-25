; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a, b, c - byte
; ((a-b)*4)/c
; ex. 1: a = 20; b = 10; c = 2; Result: ((20-10)*4)/2=40/2=20

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 20
	b  db 10
    c  db 2
    
segment  code use32 class=code ; code segment
start: 
	mov AL, [a] ;AL=a
    sub AL, [b] ;AL=AL-b
    
    mov CL, 4 ;CL=4
    mul CL  ;AX=AL*CL=(a-b)*4
    
    mov CL, [c] ;cl=2
    div CL ;AL=AX/CL
    
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of the program
