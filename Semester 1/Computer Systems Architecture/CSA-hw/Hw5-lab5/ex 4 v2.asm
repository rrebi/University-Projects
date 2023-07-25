;Two byte strings S1 and S2 are given, having the same length. Obtain the string D in the following way: each element found on the even positions of D is the sum of the corresponding elements from S1 and S2, and each element found on the odd positions of D is the difference of the corresponding elements from S1 and S2.
bits 32 
global start        
extern exit ;printf ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
	s1 db 1, 2, 3, 4   ; declare the string of bytes	
    len equ $-s1      ; compute the length of the strings in l (they have the same length)
    s2 db 5, 6, 7, 8   ; declare the string of bytes

	d times len db 0  ; reserve l bytes for the destination string and initialize it
segment code use32 class=code
start:
	mov ecx, len/2+1  ; we put the length len in ecx in order to make the loop
	mov esi, 0  ; gonna increment it at the end to get the next position   
	jecxz even_loop    ; loop for the even positions
	do:
        
        mov al, [s1+esi]    ; we move in al the element from s1
        mov bl, [s2+esi]    ; we move in bl the element from s2
        
        add al, bl  ; al = al + bl
        
		mov [d+esi], al  ; we move in d the element from al (with the position esi) 
        
		inc esi    ; esi ++
        inc esi    ; esi ++
	loop do
	even_loop:   ;end of the program
    
    mov ecx, len/2+1  ; we put the length len in ecx in order to make the loop
    mov esi, 1  ; gonna increment it at the end to get the next position
    jecxz odd_loop     ; loop for odd positions
	do1:
        
        mov al, [s1+esi]    ; we move in al the element from s1
        mov bl, [s2+esi]    ; we move in bl the element from s2
        
        sub al, bl  ; al = al - bl
        
		mov [d+esi], al   ; we move in d the element from al (with the position esi) 
        
		inc esi    ; esi ++
        inc esi    ; esi ++
	loop do1
	odd_loop:   ;end of the program

    
	; exit(0)
	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program