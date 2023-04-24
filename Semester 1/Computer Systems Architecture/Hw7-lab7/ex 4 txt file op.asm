bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen, fclose, fread, printf, fprintf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)


; 4. A text file is given. Read the content of the file, count the number of odd digits and display the result on the screen. The name of text file is defined in the data segment.
segment data use32 class=data
    
    file_name db "odd.txt", 0
    acces_mode db "r", 0
    file_descriptor dd -1
    format_file db "The file contains: ", 10, 13, 0
    format_s db "%s",0
    format_endl db " ", 10, 13, 0   ; \n
    text times 100 db 0 ; reserve 100 bytes for the destination string and initialize it
    format db "Odd digits found: %d", 10, 13, 0
    odd db '1','3','5','7','9'
    len_odd equ $-odd   ;the length of the string odd
    

; our code starts here
segment code use32 class=code
    start:
        ; fopen(file_name, acces_mode) (the file read)
        push dword acces_mode   ; r
        push dword file_name    ; odd.txt
        call [fopen]
        add esp, 4*2   ;changing the stack pointer (empty the stack)
        
        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        cmp eax, 0 ; checking whether the file was open corectly
        je endl    ; jump if not to the end of the loop
        
            ; printf(format_file)  
            push dword format_file  ; the file contains..
            call [printf]
            add esp, 4*1
               
            mov ebp, 0 ; = counts odd numbers
            repeat_:
                pushad  ; save the register
                
                ; fread(text, 1, len, file_descriptor)
                push dword [file_descriptor]
                push dword 1    
                push dword 1   
                push dword text 
                call [fread]
                add esp, 4*4
                
                cmp eax, 0
                je empty_file
                 
                    ; printf(format_s, text ) prints everyth from the file
                    push dword text
                    push dword format_s ;%s
                    call [printf]
                    add esp, 4*2  
                    
                    popad   ; pop the register saved
                   
                    mov ebx, [text]            
                    mov ecx, len_odd
                    mov esi, odd
                    mov eax, 0  ; result in eax = a character -> clear
                    while_len:    ; ecx != 0
                        lodsb; al=[esi] + inc esi  
                        cmp al, bl
                        jne not_odd ; jump if it is not equal (not odd or not a digit)
                            inc ebp
                        not_odd:
                        
                    loop while_len
                    
            jmp repeat_
            empty_file:
           
            ; printf(format_endl)  - new line \n
            push dword format_endl 
            call [printf]
            add esp, 4*1
           
            ; printf(format, value) - ebp = final number (odd digits) 
            push dword ebp
            push dword format   ; odd digits found..
            call [printf]
            add esp, 4*2
           
            
            ; fclose(file_descriptor)
            push dword [file_descriptor]
            call [fclose]
            add esp, 4*1
        
        endl:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program