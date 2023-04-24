bits 32 
global start
extern exit ;tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll  ;exit is a function that ends the calling process. It is defined in msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
	s db 5, 25, 55, 127
	len equ $-s ;the length of the string 
    d times len db 0
	doi db 2   ;variabile used for determining the digits in base 2 of a number by successive divisions to 2
	suma db 0   ;variabile used for holding the sum of the digits 

    
; our code starts here
segment code use32 class=code
    
    ;A byte string s is given. Build the byte string d such that every byte d[i] is equal to the count of ones in the corresponding byte s[i] of s
    
    start:
    cld ;df=0
	mov ecx, len    ;we will parse the elements of the string in a loop with len iterations.
    mov esi, s      ;s: 5, 25, 55, 127
    mov edi, d      ;d: 0
    
	;we obtain the 2-nd base digits of the number bl by successive divisions to 2 and then compute the sum of these digits
    ;101, 11001, 110111, 1111111
    ;d: 2, 3, 5, 7
    
	jecxz end_loop
    do:
        lodsb  ;al=[esi] + inc esi
        ; mov byte[suma], 0   ;suma = 0
        mov byte [suma], 0
        transf:
            mov ah, 0       ;converting al -> ax
            div byte[doi]   
            add [suma], ah  ;suma += ah(=quotient of s[esi] (s[esi]%2))
            cmp al, 0       ;if s[esi] = 0: next number
            jz sf
        jmp transf
        sf:
        mov al, byte[suma]
        stosb   ;d[edi] = al + inc edi
    loop do
    end_loop:
    
    push dword 0; push the parameter for exit onto the stack
    call [exit]; call exit to terminate the program
        