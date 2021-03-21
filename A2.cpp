#include <iostream>
extern "C" int _stdcall triangle(unsigned int, unsigned int, unsigned int);
extern "C" int _stdcall sum(int*, int*, int*, int);

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
        if (triangle(a, b, c) == 0) {
            std::cout << "it's not a triangle";
        }
        else {
            std::cout << "It's triangle!";
        }
    }
    else {
        std::cout << "Please, enter n: ";
        int n;
        std::cin >> n;

        int* a = new int [n];
        int* b = new int[n];
        int* result = new int[n];

        for (int i = 0; i < n; i++) {
            std::cout << "a[" << i << "]: ";
            std::cin >> a[i];
        }

        for (int i = 0; i < n; i++) {
            std::cout << "b[" << i << "]: ";
            std::cin >> b[i];
        }

        std::cout << "Sum of all elements: " << sum(a,b,result, n);

        delete [] a;
        delete [] b;
        delete [] result;

    }
    return 0;
}

