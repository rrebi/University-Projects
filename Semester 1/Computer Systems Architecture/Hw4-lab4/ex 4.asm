; Given the byte A, obtain the integer number n represented on the bits 2-4 of A. Then obtain the byte B by rotating A n positions to the right. Compute the doubleword C as follows:
; the bits 8-15 of C have the value 0
; the bits 16-23 of C are the same as the bits of B
; the bits 24-31 of C are the same as the bits of A
; the bits 0-7 of C have the value 1

; Observation: bits are numbered from right to left

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it
import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
     a db 01101011b
     b db 0 ; 11011010
     c dd 0 ;   00000000 11111111
segment  code use32 class=code ; code segment
start: 

    mov  ebx, 0 ; we compute the result in bx
    
    
    ;finding n
    mov dl, [a]
    and dl, 00011100b ; dl = the integer number n represented on the bits 2-4 ; isolating the bits 2-4
    mov cl, 2
    ror dl, cl ; rotating to right the bits 0 and 1
    
    
    ; obtaining b
    mov al, [a] ; al = 01101011b
    mov cl, dl ; mov in cl, dl = n (n=2)
    ror al, cl ; 11011010b ; we rotate n positions to the right
    mov [b], al ; b = 11011010b

    
    ; the bits 0-7 of C have the value 1
    ; the bits 8-15 of C have the value 0
    mov ebx, 00000000000000000000000011111111b
    
    
    ; the bits 16-23 of C are the same as the bits of B
    mov eax, 0 
    mov ax, [b] ; ax = 11011010
    mov cl, 16  
    shl eax, cl ; the bits are shifted to the left
    or ebx, eax ; ebx = 11011010 00000000 11111111 ;
    
    
    ; the bits 24-31 of C are the same as the bits of A 
    mov eax, 0 
    mov ax, [a] ; ax = 01101011
    mov cl, 24 
    shl eax, cl ; the bits are shifted to the left 
    or ebx, eax ; storing eax in ebx = 01101011 11011010 00000000 11111111 ;6BDA00FF
    
    
    mov  [c], ebx ; we move the result from the register to the result variable

    push dword 0 ;saves on stack the parameter of the function exit
    call [exit] ;function exit is called in order to end the execution of the program	
