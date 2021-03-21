.586
PUBLIC _sum@16
.model flat
.code
_sum@16 proc
mov eax, [esp + 4]
mov ebx, [esp + 8]
mov ecx, [esp + 12]
mov edx, [esp + 16]
_start_mul:
cmp edx, 0
    je _end_of_mul
    mov esi, [eax]
    imul esi, [ebx]
    mov[ecx], esi
    add eax, 4
    add ebx, 4
    add ecx, 4
    sbb edx, 1
    jmp _start_mul
    _end_of_mul:

mov eax, 0
mov ecx, [esp + 12]
mov edx, [esp + 16]
_start_sum:
cmp edx, 0
    je _end_of_sum
    add eax, [ecx]
    add ecx, 4
    sbb edx, 1
    jmp _start_sum
    _end_of_sum:
ret 16
_sum@16 endp
end