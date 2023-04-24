;Two byte strings S1 and S2 are given, having the same length. Obtain the string D in the following way: each element found on the even positions of D is the sum of the corresponding elements from S1 and S2, and each element found on the odd positions of D is the difference of the corresponding elements from S1 and S2.
bits 32 
global start        
extern exit ;printf ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
	s1 db 1, 2, 3, 4    ; declare the string of bytes
    len equ $-s1      ; compute the length of the strings in l (they have the same length)
    s2 db 5, 6, 7, 8    ; declare the string of bytes

	d times len db 0  ; reserve l bytes for the destination string and initialize it
    doi db 2
segment code use32 class=code
start:
	mov esi, 0  ; gonna increment it at the end to get the next position   
	mov ecx, len  ; we put the length l in ecx in order to make the loop
 
	jecxz end_loop      
	do:
        
        mov dl, [s1+esi]    ; we move in al the element from s1
        mov bl, [s2+esi]    ; we move in bl the element from s2
        
        mov al, [esi]
        
        ;test esi, 01h   ;0000 0001b
        
        ;jpo position_is_even     ; jump short if parity even pf = 1
        mov ah, 0
        div byte [doi] ; al has quotient; ah has reminder
        cmp ah, 0
        
        ;if al is even add it to the sum, if al is odd skip it
        jne itsodd
            add dl, bl  ; al = al + bl
            jmp end_if
        ;position_is_even:
        itsodd:
        
        ;jpe position_is_odd   ; pf = 0
        sub dl, bl  ; al = al - bl 
        ;position_is_odd:
        
        end_if:
        
		mov [d+esi], dl   ; we move in d the element from al
        
		inc esi    ; esi ++
	loop do
	end_loop:   ;end of the program

    
	; exit(0)
	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program