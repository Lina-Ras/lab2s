.686
.model flat
.data
k dd 180
r dd 180
count dd 1.0
res dd 0
eps dd ?
x dd ?
xsq dd ?
tmp dd ?
.code

_arcsin@4 proc
finit
fld dword ptr[esp+4]
fld dword ptr[esp+4]
fmul
fld1
fsubr
fsqrt
fld dword ptr[esp+4]
fxch
fpatan
fldpi
fdiv
fild k
fmul
fist k
mov eax, k
ret 4
_arcsin@4 endp

_CalculateSh@8 proc
finit
fld dword ptr[esp+4]
fldpi
fmul
fild r
fdiv
fst x
fst res
fst tmp
fst st(1)
fmul
fst xsq
fld dword ptr[esp+8]
fst eps

_compare_b:
fld tmp
fabs
fld eps
fcompp
fstsw ax
sahf
ja _end;
fld tmp
fld xsq
fmul
fld1
fld count
fadd
fst count
fdiv
fld1
fld count
fadd
fst count
fdiv
fst tmp
fld res
fadd
fst res
jmp _compare_b;

_end:
fld res
ret
_CalculateSh@8 endp

end 
