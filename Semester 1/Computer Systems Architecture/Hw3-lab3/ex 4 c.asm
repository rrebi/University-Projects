; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; b,c,d - byte; a - word; e - double word; x - qword; - Unsigned representation
; (a * 2 + b / 2 + e) / (c - d) + x / a
; ex: a = 3; b = 4; c = 10; d = 6; e = 8 => (6 + 2 + 8) / 4 + 9 / 3 = 4 + 3 = 7
bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a dw 3
    b db 4
    c db 10
    d db 6
    e dd 8
    x dq 9
    
segment  code use32 class=code ; code segment
start:
    ;(a*2 + b/2 + e) / (c-d) + x/a  ; b,c,d - byte; a - word; e - double word; x - qword
    
    mov ax, [a] ;ax = a
    mov dx, 2 ;dx = 2
    mul dx ;dx:ax = ax * dx = a*2
    
    mov bx, ax ;bx = ax = a*2
    mov cx, dx ;cx=dx
    
    mov al, [b] ;al = b
    mov ah, 0 ;converting al to ax
    mov dl, 2 ;dl = 2
    div dl ;al = ax/dl = b/2
    mov ah, 0 ;converting al to ax
    mov dx, 0 ;converting ax to dx:ax 
    
    
    ;clc ;clear carry flag
    add ax, bx
    adc dx, cx ;ax = ax + bx + cf = a*2 + b/2
    
    push dx
    push ax
    pop ebx
    
    mov eax, [e] ;eax = e
    add ebx, eax ; ebx = ebx + eax = a*2 + b/2 + e
    
    
    
    mov al, [c] ;al = c
    sub al, [d] ;al = c - d
    mov ah, 0 ;converting al to ax
    mov dx, 0 ;converting ax to dx:ax 
    
    push dx
    push ax
    
    mov eax, ebx ;eax=a*2 + b/2 + e
    mov edx, 0 ;converting eax to edx:eax
    
    pop ebx
    div ebx ;eax = edx:eax / ebx, edx = edx:eax % ebx ;eax=(s*2+b/2+e)/(c-d)
    
    mov ebx, eax ;ebx=eax=(s*2+b/2+e)/(c-d)
    ;mov ecx, edx ;ecx=edx
    
    mov eax, 0
    mov ax, [a] ;ax = a
    mov dx, 0 ;converting ax to dx:ax
    ;mov edx, 0 ;converting eax to edx:eax
    
    push dx
    push ax
    
    mov eax, dword [x] 
    mov edx, dword [x+4] ;edx:eax = x
    
    pop esp
    
    div esp ;eax = edx:eax / esp, edc = edx:eax % esp ;eax=x/a
    
    clc ;clear carry flag
    add ebx, eax ;ecx:ebx = ebx + eax + cf =(a*2 + b/2 + e) / (c-d) + x/a 
    ;adc ecx, edx 
    
    
    push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution ofthe program