.code

RowCalc proc
push rbp
mov rbp, rsp
mov rbx, [rbp + 24]
xor r10, r10
mov r9, [rbp + 16]
	_begin_ch:
	movzx eax, word ptr[rbx]
	add r10, rax
	dec r9
	add rbx, 2
	cmp r9, 0
	jne _begin_ch;
mov rax, r10
pop rbp
ret 16
RowCalc endp

ColumnCalc proc
push rbp
mov rbp, rsp
mov rcx, [rbp + 24]
xor r10, r10
mov r9, [rbp + 16]
	_begin_cv:
	mov rbx, qword ptr[rcx]
	movzx eax, word ptr[rbx]
	add r10, rax
	dec r9
	add rcx, 8
	cmp r9, 0
	jne _begin_cv;
mov rax, r10
pop rbp
ret 16
ColumnCalc endp

IsMagicSquare proc
mov r8, rdx
mov r12, rcx

_begin_h:
	mov rbx, qword ptr [rcx]
		push rbx
		push rdx
		call RowCalc
	cmp r8, rdx
	jne _skiph;
	mov r11, r10
	_skiph:
	cmp r11, r10
	jne _endf;
	dec r8
	add rcx, 8
	cmp r8, 0
jne _begin_h;

xor r8, r8
_begin_v:
	mov rcx, r12
		push rcx
		push rdx
		call ColumnCalc
	cmp r11, r10
	jne _endf;
	inc r8
	add rcx, 8
	cmp r8, rdx
jne _begin_v;

xor r10, r10
mov rcx, r12   
xor r8, r8
	_begin_dm:
		mov rbx, qword ptr[rcx]
		mov r15, r8
		imul r15, 2
		add rbx, r15
		movzx eax, word ptr[rbx]
		add r10, rax
		inc r8
		add rcx, 8
		cmp r8, rdx
	jne _begin_dm;
cmp r11, r10
jne _endf;

mov r8, rdx 
dec r8
mov rcx, r12   
xor r10, r10
	_begin_ds:
		mov rbx, qword ptr[rcx]
		mov r15, r8
		imul r15, 2
		add rbx, r15
		movzx eax, word ptr[rbx]
		add r10, rax
		dec r8
		add rcx, 8
		cmp r8, -1
	jne _begin_ds;
cmp r11, r10
jne _endf;

mov rax, 1
jmp _endt;
_endf:
mov rax, 0

_endt:
ret
IsMagicSquare endp
end
