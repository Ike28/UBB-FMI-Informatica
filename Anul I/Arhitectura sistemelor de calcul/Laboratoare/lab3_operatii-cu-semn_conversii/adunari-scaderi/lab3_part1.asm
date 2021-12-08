bits 32 
global  start 

extern  exit
import  exit msvcrt.dll

segment  data use32 class=data
	a db 38h ; = 56d
	b dw 7D0h ; = 2000d
	c dd 105B8h ; = 67 000d
	d dq 3D0900h ; = 4 000 000d
	z resq 1
segment  code use32 class=code
start: 
	; adunari/scaderi I.26 - a - byte, b - word, c - double word, d - qword - Interpretare fara semn
	; ( c - b + a ) - ( d + a )
	mov ebx, [c]
	mov eax, 0
	mov ax, [b]
	sub ebx, eax ; EBX = c - b = 0000FDE8h = 65000d
	mov eax, 0
	mov al, [a]
	add ebx, eax ; EBX = c - b + a  = 0000FE20h = 65056d
	mov eax, ebx
	mov edx, 0 ; EDX:EAX = c-b+a = 00000000:0000FE20h

	mov ebx, dword [d+0] ; EBX = 003D0900
	mov ecx, dword [d+4] ; ECX:EBX = d
	clc
	add bl,[a]
	adc bh, 0 ; ECX:EBX = 00000000:003D0938

	clc
	sub eax, ebx
	sbb edx, ecx ; rezultatul este in EDX:EAX = FFFFFFFF:FFC3F4E8

	; adunar/scaderi II.25 - a - byte, b - word, c - double word, d - qword - Interpretare cu semn
	; (a + b - c) + (a + b + d) - (a + b) = 3C0B50h
	mov al, [a]
	cbw ; convertim a la word
	clc
	add ax, [b]
	cwde ; convertim rezultatul la dword, EAX = a+b
	
	clc
	sub eax, [c]
	mov ebx, eax ; EBX = a+b-c = FFFF0250h (mutam in EBX pentru a converti a la dword)
	mov al, [a]
	cbw
	cwde ; EAX = a
	add ebx, eax ; EBX = (a+b-c) + a = FFFF0288h
	mov ax, [b]
	cwde
	add ebx, eax
	mov eax, ebx
	cdq ; EDX:EAX = (a+b-c) + a + b
	mov ebx, dword [d+0]
	mov ecx, dword [d+4] ; ECX:EBX = d
	clc
	add eax, ebx
	adc edx, ecx ; EDX:EAX = (a + b - c) + (a + b + d)
	clc
	sub al, [a]
	sbb ah, 0 ; EDX:EAX = (a + b - c) + (a + b + d) - a
	clc
	mov ebx, eax
	mov ecx, edx ; transferam rezultatul in ECX:EBX pentru a pregati operandul b qword
	mov ax, [b]
	cwde ; EAX = b
    cdq ; EDX:EAX = b
	clc
	sub ebx, eax ; EBX = EBX - EAX
	sbb ecx, edx ; ECX = ECX - EDX - CF
				 ; rezultatul este in ECX:EBX = 00000000:003C0B50

	push   dword 0
	call   [exit]