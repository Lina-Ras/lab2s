.586
.model flat
.code
_IsPalindrom@4 proc
mov edi, dword ptr[esp+4]
mov al, '?'
mov ecx, -1
_continue:
add ecx, 1
scasb
jne _continue;
mov edi, dword ptr[esp+4]
mov esi, dword ptr[esp+4]
add esi, ecx
add esi, -1

_check:
cmp ecx, 0
jng _true;
add ecx, -2
mov eax, 0
std
lodsb
cld
scasb
je _check;

mov eax, 0
jmp _end;

_true:
mov eax, 1

_end:

ret 4
_IsPalindrom@4 endp

_DeleteBracers@8 proc
mov ecx, dword ptr[esp+8]
mov esi, dword ptr[esp+4]
mov edx, 0

mov eax, 0
mov al, '('
_ch1:
cmp ecx, 0
jng _end;
movsb
add edi, -1
add edx, 1
add ecx, -1
scasb
jne _ch1;

mov eax, 0
mov al, ')'
_ch2:
cmp ecx, 0
jng _end;
add ecx, -1
scasb
jne _ch2;

_ch3:
cmp ecx, 0
jng _end;
movsb
add edx, 1
add ecx, -1
jmp _ch3;

_end:
mov eax, edx

ret 8
_DeleteBracers@8 endp
end