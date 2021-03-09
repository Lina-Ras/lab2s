#include <iostream>

int main()
{
    std::cout << "Please, enter the number of the task: ";
    int choice;
    std::cin >> choice;
    while (choice != 1 && choice != 2) {
        std::cout << "This number was incorrect. Please, enter the number of the task: ";
        std::cin >> choice;
    }
    if (choice == 1) {
        unsigned int a, b, c;
        std::cout << "a = ";
        std::cin >> a;
        std::cout << "b = ";
        std::cin >> b;
        std::cout << "c = ";
        std::cin >> c;
        __asm {
            mov eax, a
            mov ebx, b
            adc eax, ebx
            jc _success
            mov ecx, c
            cmp ecx, eax
            jng _fail
            jmp _success

            mov eax, a
            mov ebx, c
            adc eax, ebx
            jc _success
            mov ecx, b
            cmp ecx, eax
            jng _fail
            jmp _success

            mov eax, c
            mov ebx, b
            adc eax, ebx
            jc _success
            mov ecx, a
            cmp ecx, eax
            jng _fail
            jmp _success

            _success :
        }
        std::cout << "it's a triangle";
        __asm {
            jmp _end;
        _fail:
        }
        std::cout << "it's not a triangle";
        __asm {
        _end:;
        }
    }
    else {
        std::cout << "Please, enter n: ";
        int n;
        std::cin >> n;

        int* a = new int [n];
        int* b = new int[n];
        int* result = new int[n];

        int sum;

        for (int i = 0; i < n; i++) {
            std::cout << "a[" << i << "]: ";
            std::cin >> a[i];
        }

        for (int i = 0; i < n; i++) {
            std::cout << "b[" << i << "]: ";
            std::cin >> b[i];
        }

        __asm {
            mov eax, a
            mov ebx, b
            mov ecx, result
            mov edx, n
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
            mov ecx, result
            mov edx, n
            _start_sum:
            cmp edx, 0
                je _end_of_sum
                add eax, [ecx]
                add ecx, 4
                sbb edx, 1
                jmp _start_sum
                _end_of_sum:
            mov sum, eax

        }

        std::cout << "Sum of all elements: " << sum;

        delete [] a;
        delete [] b;
        delete [] result;

    }
    return 0;
}

