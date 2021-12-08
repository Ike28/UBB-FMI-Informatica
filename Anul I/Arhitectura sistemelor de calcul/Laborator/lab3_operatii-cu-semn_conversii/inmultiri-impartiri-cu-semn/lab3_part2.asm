bits 32
global  start 

extern  exit
import  exit msvcrt.dll
segment  data use32 class=data
	a db 7h ; = 7d
	b db 3Ch ; = 60d
	c db 0Dh ; = 13d
	d db 2h ; = 2d
	e dw 2BEh ; = 702d
	x dq 10000h ; = 65536d
	y resd 1
segment  code use32 class=code
start: 
	; inmultiri/impartiri 23 - ( a * b - 2 * c * d) / ( c - e) + x / a = 9362d = 2492h
	; a,b,c,d - byte; e - word; x - qword
	mov al, [a]
	imul byte [b] ; AX = a*b
	cwde ; EAX = a*b
	mov ebx, eax
	mov al, 2h
	imul byte [c] ; AX = 2*c
	mov dx, ax
	mov al, [d]
	cbw ; AX = d
	imul dx ; DX:AX = 2*c*d
	push dx
	push ax
	pop edx ; EDX = 2*c*d
	sub ebx, edx ; EBX = a*b - 2*c*d
	push ebx
	pop ax
	pop dx ; DX:AX = a*b - 2*c*d = 0000:0170h
	mov bx, ax
	mov al, [c]
	cbw
	sub ax, [e]
	mov cx, ax ; CX = c-e
	mov ax, bx
	idiv cx ; AX = DX:AX/CX = ( a * b - 2 * c * d) / ( c - e), DX = DX:AX%CX
	mov cx, ax
	mov eax, dword [x+0]
	mov edx, dword [x+4] ; EDX:EAX = x = 00000000:00010000h
	mov ebx, eax
	mov al, [a]
	cbw
	cwde
	mov [y], eax
	mov eax, ebx
	mov ebx, [y]
	idiv ebx ; AX = EDX:EAX/EBX = x / a
	add ax, cx ;  rezultatul este in AX = 2492h
	
	push   dword 0
	call   [exit]