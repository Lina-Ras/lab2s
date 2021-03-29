#include <iostream>

extern "C" bool _stdcall IsPalindrom(char* s);
extern "C" int _stdcall DeleteBracers(char* s, int length);

int main()
{
    std::cout << "Enter the line: \n";
    std::string input;
    std::cin >> input;

    char* c = new char[input.size() + 1];
    int n = input.size();
    for (int i = 0; i < n; ++i) {
        c[i] = input[i];
    }
    c[n] = '?';

    if (IsPalindrom(c)) {
        std::cout << "It's a palindrom\n";
    }
    else {
        std::cout << "It's not a palindrom\n";
    }
    delete[]c;

    std::cout << "Enter the line: \n";
    std::cin >> input;

    char* d = new char[input.size() + 1];
    n = input.size();
    for (int i = 0; i < n; ++i) {
        d[i] = input[i];
    }
    d[n] = '?';
    std::cout << DeleteBracers(d, input.size());
    delete[]d;

}