bits 32 ; assembling for the 32 bits architecture

; 14. Se citesc mai multe numere de la tastatura, in baza 2. Sa se afiseze aceste numere in baza 8.

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern conversie

; declare external functions needed by our program
extern exit, scanf, printf              
import exit msvcrt.dll 
import scanf msvcrt.dll
import printf msvcrt.dll  

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    x times 30 db 0
	y times 10 db 0
	format db "%s", 0
	msg1 db "How many nos? n=", 0
	msg2 db "No. in base 2:", 0
	msg3 db "No. in base 8:%s", 13, 10, 0
	
	nr dd 0
	format_nr db "%d", 0	
	
; our code starts here
segment code use32 class=code

    start:
		; printf(msg1)
		push dword msg1
		call [printf]
		add esp, 4*1
		
		; scanf(format_nr,nr)
		push dword nr
		push dword format_nr
		call [scanf]
		add esp, 4*2
		
		mov ecx, [nr]
		jecxz final
		
		
		
	repeta:
		pushad
		; printf(msg2)
		push dword msg2
		call [printf]
		add esp, 4*1

		
		; scanf(format, x)
		push dword x
		push dword format
		call [scanf]
		add esp, 4*2

		push dword y		
		push dword x
		call conversie
		
		; printf(msg3, y)
		push dword y
		push dword msg3
		call [printf]
		add esp, 4*2
		popad
		
		loop repeta
	final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
