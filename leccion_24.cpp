#include <iostream>

int getValueFromUser() {
    int value{};
    std::cout << "Enter an integer value: ";
    std::cin >> value;
    return value;
}

void printValue(int value) {
    std::cout << "You entered: " << value << std::endl;
}

// unreferenced params 
void unreferencedExample(int unusedParam) {
     // el warning aparece, porque "unusedParam" nunca se usa
    std::cout << "This function does not use its parameter." << std::endl;
}
// unnamed params
void unnamedExample(int /*unusedParam*/) {
     // sin warning: "borrás" el nombre pero dejás el tipo (comentado, como documentación)
    std::cout << "This function also does not use its parameter." << std::endl;
}

int main() {
    // int userValue = getValueFromUser();  esto es lo mismo que la siguiente línea
    int userValue { getValueFromUser() };
    printValue(userValue);
    return 0;
}