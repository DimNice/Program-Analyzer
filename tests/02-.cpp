// !test format_string_error
// !test warn_format_string_error

#include <iostream>

void vulnerable_function(char *input) {
    printf(input); // Уязвимость: ошибка форматной строки
}

int main() {
    char input[50];
    std::cout << "Enter your input: ";
    std::cin >> input; // Уязвимость: неконтролируемый ввод
    vulnerable_function(input);
    return 0;
}