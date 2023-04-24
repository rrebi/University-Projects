bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf,scanf                ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll
; our data is declared here (the variables needed by our program)

; Two natural numbers a and b (a, b: dword, defined in the data segment) are given. Calculate their product and display the result in the following format: "<a> * <b> = <result>". Example: "2 * 4 = 8"
;The values will be displayed in decimal format (base 10) with sign.
    
segment data use32 class=data
    a dd 0
    b dd 0
    format_a db "a = ", 0
    format_b db "b = ", 0
    format_s db "%d", 0
    format_r db "Read numbers are: %d and %d ",10,13,0
    format db "%d * %d = %d", 0     ; %d <=> decimal number
    
; our code starts here
segment code use32 class=code
    start:
        ; printf (format_a)
        push dword format_a
        call [printf]
        add esp, 4*1 ;changing the stack pointer (empty the stack) 
        
        
        ; scanf(format_2, a) 
        push dword a 
        push dword format_s 
        call [scanf]
        add esp, 4*2
        
        ; printf (format_b) 
        push dword format_b
        call [printf]
        add esp, 4*1 ; 
        
        ; scanf(format_2, b) 
        push dword b 
        push dword format_s 
        call [scanf]
        add esp, 4*2
            
        ; printf (format, a, b)  which numbers are read from the keyboard
        push dword [b]
        push dword [a]
        push dword format_r
        call [printf]
        add esp, 4*3 ; clear stack 
        
        
        ; a*b  
        mov ebx, dword[a]
        imul ebx, dword[b] ; ebx = a*b  
        
        ; printf (format, a, b, EBX)
        push ebx 
        push dword [b]
        push dword [a]
        push dword format
        call [printf]
        add esp, 4*4 ; clear stack 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program