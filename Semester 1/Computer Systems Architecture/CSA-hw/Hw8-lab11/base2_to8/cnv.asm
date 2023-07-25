bits 32 

global cnv      

segment data use32 class=data
    db '|'
    len db 0
    db '|'
    cifra_8 db 0
    db '|'

segment code use32 class=code
		
	;|--------------|
    ;| adresa retur |  <- [esp]
    ;|--------------|
    ;|      x       |  <- offsetul lui y, [esp+4]
    ;|--------------|
	;|  	y       |  <- offsetul lui x, [esp+8]
    ;|--------------|
	; Conversia unui nr din baza 2 in baza 8 citit ca string
    cnv:
        ; luam parametrii (x si y) din stack si punem adresele respective in ebx si ecx:
		mov ebx, [esp+4] ; offsetul lui x
		mov ecx, [esp+8] ; offsetul lui y
       
		mov esi, -1 ; contorul pt cifrele in baza 2
		; mov edi, 0
	numara:
		inc esi						; numar cate cifre sunt in baza 2
		cmp byte [ebx + esi], ""
		jne numara
        
        xor edi, edi
        
        mov ax, si
        mov dl, 3
        div dl
        cmp ah, 0
        je nu_adauga
            mov edi, 1
        nu_adauga:
        xor ah, ah
        add di, ax
        
        mov byte [edi + ecx], "" ; empty string ca sa stim cand se termina
        
    convertim_din_baza_2_in_baza_8: 		; cate o cifra
		mov byte [len], 0 					; contor pt grup de 3 cifre
		mov byte [cifra_8], 0

    bucla:
        cmp byte [ebx + esi - 1], "1"
		jne am_verificat_cifra_binara		; daca [x + esi - 1] nu este 1 at ax ramane la fel, altfel se modifica
		
        ; verificam pozitia cifrei:
		cmp byte [len], 0 ; = pozitia cifrei de 1 din x, daca prima cifra este 1 at add cifra_in_baza_8, 1		
		jne a_2a_cifra		
	
		add byte [cifra_8], 1
		jmp am_verificat_cifra_binara
	
	a_2a_cifra:
		cmp byte [len], 1		; daca a 2 a cifra este 1 at add cifra_in_baza_8, 2
		jne a_3a_cifra
		add byte [cifra_8], 2
		jmp am_verificat_cifra_binara
	
	a_3a_cifra:
		add byte [cifra_8], 4		; daca a 3 a cifra este 1 at add cifra_in_baza_8, 4
		
	am_verificat_cifra_binara:
		dec esi
		inc byte [len]
		cmp byte [len], 3		; daca s-au verificat 3 cifre din baza 2 at scrie una in baza 8 
		je scrie
		cmp esi, 0 		; daca nu mai sunt cifre in baza 2
		je scrie
		jmp bucla
		
	scrie:
        ; adauga cifra in baza 8 in y:
        mov al, [cifra_8]
		add al, "0"
		
        mov byte [edi + ecx - 1], al
        dec edi
        
        cmp esi, 0
		jle final
		jmp convertim_din_baza_2_in_baza_8
	
	final:

		ret 4*2

        
        