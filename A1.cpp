#include <iostream>

int Calculate(int a, int b, int c, int y)
{
    int result;

    __asm
    {
        //3ax+by+c=0
        mov eax, y
        mov ebx, b
        imul ebx
        mov ebx, c
        adc eax, ebx
        mov ecx, eax
        mov eax, a
        mov ebx, -3
        cdq
        imul ebx
        mov ebx, eax
        mov eax, ecx
        cdq
        idiv ebx

        mov ecx, eax
        mov esi, edx
        mov eax, ebx
        mov ebx, 2
        cdq
        idiv ebx

        
        cmp ecx, 0
            jng _neg_number;
            cmp edx, 0
                je _even_pos_number;
            cmp esi, eax
                jnl _end;
            add ecx, 1
                jmp _end;
            _even_pos_number:
                cmp esi, eax
                    je _half_pos;
                cmp esi, eax
                    jg _end;
                add ecx, 1
                    jmp _end;
            _half_pos:
                mov eax, ecx
                mov ebx, 2
                idiv ebx
                cmp edx, 0
                    je _end;
                add ecx, 1
                    jmp _end;

            _neg_number:
                neg edx
                cmp edx, 0
                    je _even_neg_number;
                cmp esi, eax
                    jg _end;
                add ecx, -1
                    jmp _end;
            _even_neg_number:
                neg eax
                cmp esi, eax
                    je _half_neg;
                cmp esi, eax
                    jng _end;
                add ecx, -1
                    jmp _end;
            _half_neg:
                mov eax, ecx
                mov ebx, 2
                idiv ebx
                cmp edx, 0
                    je _end;
                add ecx, -1
                    jmp _end;
            _end:
                mov eax, ecx
                mov result, eax;
    }

    return result;
}


int main() {
    int a, b, c, y;
    std::cout << "Please, enter a: ";
    std::cin >> a;
    std::cout << "Please, enter b: ";
    std::cin >> b;
    std::cout << "Please, enter c: ";
    std::cin >> c;
    std::cout << "Please, enter y: ";  
    std::cin >> y;
    int x;
    x = Calculate(a, b, c, y);
    std::cout << "result: " << x << '\n';
}