bits 32 

global conv      

segment data use32 class=data
    db '|'
    len db 0
    db '|'
    doi db 2
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
    conv:
        ; luam parametrii (x si y) din stack si punem adresele respective in ebx si ecx:
		mov esi, [esp + 4]  ; address of s1 -input
        mov edi, [esp + 8]  ; address of s2 -output
        mov ecx, [esp + 12] ; len -input
		; mov edi, 0

	jecxz end_loop
    do:
        lodsb  ;al=[esi] + inc esi
        ; mov byte[suma], 0   ;suma = 0
        ; mov byte [suma], 0
        transf:
            mov ah, 0       ;converting al -> ax
            div byte[doi]   
            ; add [suma], ah  ;suma += ah(=quotient of s[esi] (s[esi]%2))
            ;mov cl, 1
            ;shr ah, cl
            mov byte [edi + ecx - 1], ah
            ;dec edi
            cmp al, 0       ;if s[esi] = 0: next number
            jz sf
        jmp transf
        sf:
        ; mov al, byte[suma]
        ; stosb   ;d[edi] = al + inc edi
    loop do
    end_loop:
		ret 4*2
