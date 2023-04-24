; A string of numbers is given. Show the values in base 16 and base 2.
bits 32
global start

;extern conv

extern printf, exit
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    doi db 1
	s1 db 10,20,30,40,50
    l equ $-s1
    s2 times l db 0
    s3 times l db 0
    base16print db "s[%d] (base 10) = %x (base 16)", 10, 13, 0
    base2print db "s[%d] (base 10) = %d (base 2)", 10, 13, 0

segment code use32 class=code

; base 16 
; copying the numbers from s1 to s2 in reverse order on the stack 

base16: 
    ; the return address = esp
	mov esi, [esp + 4]  ; address of s1 -input
	mov edi, [esp + 8]  ; address of s2 -output
	mov ecx, [esp + 12] ; len -input
    
    rep movsb   ; store the byte from the address <DS:ESI> to the address <ES:EDI>   ; copy from source to destination
    
    ret 12  ; pop the return address  ; free 3 parameters (3*4 bytes)
    
; base 2
base2:
    ; the return address = esp
	mov esi, [esp + 4]  ; address of s1 -input
	mov edi, [esp + 8]  ; address of s2 -output
	mov ecx, [esp + 12] ; len -input
    
    jecxz end_loop
    do:
        mov bl, 0
        lodsb  ;al=[esi] + inc esi
        ; mov byte[suma], 0   ;suma = 0
        ; mov byte [suma], 0
        transf:
            mov ah, 0       ;converting al -> ax
            mov dx, ax
            div byte[doi]   
            ; add [suma], ah  ;suma += ah(=quotient of s[esi] (s[esi]%2))
            ;mov cl, 1
            ;shr ah, cl
            add bl, ah
            mov al, 0
            mov al, bl
            mov bl, 10
            mul bl
            mov bl, al
            
            mov ax, dx
            ;stosb
            ;dec edi
            cmp al, 0       ;if s[esi] = 0: next number
            jz sf
        jmp transf
        sf:
        mov al, bl
        ; mov al, byte[suma]
        stosb   ;d[edi] = al + inc edi
        ;inc edi
    loop do
    end_loop:
    ret 12  ; pop the return address  ; free 3 parameters (3*4 bytes)
    
    
; "main" program       
start:
    ; for base16
    ; push on the stack in reverse order
	push dword l        
	push dword s2        
	push dword s1  
    call base16
    ; s2 = s1 in base 16
    
	;print array s2
	mov esi, s2
	mov ebx, 0
	mov ecx, l
    print_loop:
        mov eax, 0
        lodsb
        pushad
        
        ;printf("s[%d]=%d", index=ebx, value=eax)
        push eax
        push ebx
        push dword base16print
        call [printf]
        add esp, 4*3
        
        popad
        inc ebx
    loop print_loop
    
    
    ; for base2
    ; push on the stack in reverse order
	push dword l        
	push dword s3        
	push dword s1  
    call base2
    ; s3 = s1 in base 2
    
	;print array s3
	mov esi, s3
	mov ebx, 0
	mov ecx, l
    print_loop1:
        mov eax, 0
        lodsb
        pushad
        
        ;printf("s[%d]=%d", index=ebx, value=eax)
        push eax
        push ebx
        push dword base2print
        call [printf]
        add esp, 4*3
        
        popad
        inc ebx
    loop print_loop1
    

	push 0
	call [exit]