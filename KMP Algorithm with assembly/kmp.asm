segment .bss
i resd 1
j resd 1
m resd 1
n resd 1

segment .data
printnum	db	"%d ",0
prompt		db	"Prefix table: ",0

segment .text
global kmp
extern printf

kmp:
	push ebp
	mov ebp, esp
	
	; calculate n (length of text):
	
	xor eax, eax			; clear a
	mov ebx, [ebp + 8]		; ebx <- &text
calcn:
	mov ecx, [ebx + eax]
	inc eax
	cmp ecx, 0
	jne calcn
	dec eax
	mov [n], eax
	
	; calculate m (length of pattern and table);
	
	xor eax, eax			; clear a
	mov ebx, [ebp + 12]		; ebx <- &pattern
calcm:
	mov ecx, [ebx + eax]
	inc eax
	cmp ecx, 0
	jne calcm
	dec eax
	mov [m], eax
	
	
	; calculate prefix table:

	push prompt 
	call printf
	add esp, 4
	
	push dword 0			; the first element of the table is 0.
	push printnum			; print after adding to the table.
	call printf
	add esp, 4
	
	mov eax, [m]			; skip calculating prefix table if
	cmp eax, 1				; pattern has only 1 character
	je onechar				
	
	mov eax, 0				; initialize j to 0.
	mov [j], eax			
	mov eax, 1				; initialize i to 1.
	mov [i], eax
		
calcprefix:
	mov ecx, [i]
	mov ah, byte [ebx + ecx]; using 8-bit registers to make
	mov ecx, [j]			; byte-wise comparison.
	mov dh, byte [ebx + ecx]
	cmp ah, dh				; pattern[i] == pattern[j] ?
	jne condition1
	
	mov ecx, [j]			; j++
    inc ecx
    mov [j], ecx
    
    push ecx				; table[i] = j
    push printnum
    call printf
    add esp, 4
    
    mov ecx, [i]			; i++
	inc ecx
	mov [i], ecx
	jmp resume
	
condition1:
    mov ecx, [j]
    cmp ecx, 0				; j == 0 ?	
    jne condition2
    
    push dword 0			; table[i] = 0
    push printnum
    call printf
    add esp, 4
    
    mov ecx, [i]			; i++
	inc ecx
	mov [i], ecx
    
    jmp resume

condition2:
	mov eax, [i]
	mov ecx, [j]
	sub eax, ecx
	mov ecx, [esp + 4*eax]	; ecx <- [esp + 4 * (i - j)]
	mov [j], ecx			; j = table[j - 1]
resume:
	mov eax, [i]
	mov ecx, [m]
	cmp eax, ecx
	jb calcprefix			; i < m ?

onechar:					; don't calculate prefix table and jump here
							; if pattern has only 1 character.
	

	; search string:
		
	mov eax, 0				; initialize i and j to 0.
	mov [j], eax
	mov eax, 0
	mov [i], eax
	
	mov eax, [ebp + 8]		; eax <- &text (ebp is already &pattern)
search:	
	mov ecx, [i]
	mov edx, [n]
	cmp ecx, edx
	jae fail
	mov ecx, [i]
	mov dh, byte [eax + ecx]
	mov ecx, [j]
	mov dl, byte [ebx + ecx]
	cmp dh, dl				; text[i] == pattern[j] ?
	je increment
back:
	mov ecx, [j]
	mov edx, [m]
	cmp ecx, edx
	je endsearch
	mov ecx, [i]
	mov edx, [n]
	cmp ecx, edx
	jb cond1
	
	jmp search
cond1:
	mov ecx, [i]
	mov dh, byte [eax + ecx]
	mov ecx, [j]
	mov ch, byte [ebx + ecx]
	cmp dh, ch				; text[i] != pattern[j] ?
	je search
	mov edx, [j]
	cmp edx, 0
	je cond2
	mov ecx, [m]
	mov edx, [j]
	sub ecx, edx
	mov edx, [esp + 4*ecx]
	mov [j], edx
	jmp search
increment:
	mov ecx, [j]			; j++
	inc ecx					;
	mov [j], ecx			;
	mov ecx, [i]			; i++
	inc ecx					;
	mov [i], ecx			;
	jmp back
cond2:
	mov ecx, [i]
	inc ecx
	mov [i], ecx
	jmp search	
endsearch:
	mov eax, [i]
	mov ebx, [j]
	sub eax, ebx
	jmp end
fail:
	mov eax, -1
	
	
end:	
	mov esp, ebp
	pop ebp
	ret


