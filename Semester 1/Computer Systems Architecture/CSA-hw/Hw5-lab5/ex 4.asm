bits 32 
global start        
extern exit ;printf ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)


;Two byte strings S1 and S2 are given, having the same length. Obtain the string D in the following way: each element found on the even positions of D is the sum of the corresponding elements from S1 and S2, and each element found on the odd positions of D is the difference of the corresponding elements from S1 and S2.
;S1: 1, 2, 3, 4
;S2: 5, 6, 7, 8
;D: 6, -4, 10, -4

segment data use32 class=data
	s1 db 1, 2, 3, 4    ; declare the string of bytes
    len equ $-s1        ; compute the length of the strings in l (they have the same length)
    s2 db 5, 6, 7, 8    ; declare the string of bytes

	d times len db 0    ; reserve l bytes for the destination string and initialize it
segment code use32 class=code
start:
	mov esi, 0    ; gonna increment it at the end to get the next position   
	mov ecx, len  ; we put the length l in ecx in order to make the loop
        
	jecxz end_loop      
	do:
        
        mov al, [s1+esi]    ; we move in al the element from s1
        mov bl, [s2+esi]    ; we move in bl the element from s2
        
        
        test esi, 01h   ;0000 0001b
        
        jpo position_is_even  ; pf = 1
            add al, bl  ; al = al + bl
            jmp end_if
        position_is_even:
        
        
        ;jpe position_is_odd   ; pf = 0
        sub al, bl  ; al = al - bl 
        ;position_is_odd:
        
        end_if:
        
		mov [d+esi], al   ; we move in d the element from al
        
		inc esi    ; esi ++
	loop do
	end_loop:   ;end of the program

    
	; exit(0)
	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program