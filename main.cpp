#include <iostream>
using namespace std;






void funcion_por_ref(int &param) // & indica paso por ref
{
    param = param + 1;          // modifica el original
}

void funcion_por_valor(int param) // modifica una copia
{
    param = param + 1;         
}

void ejemplo_de_paso_params_funciones()
{
    int porValor = 2;
    int porRef = 5;

    funcion_por_ref(porRef);
    cout << porRef << endl;       // modifica el original

    funcion_por_valor(porValor);
    cout << porValor << endl;     // NO modifica el original
}


void ejemplo_puntero()
{
    int x = 42;             // variable normal
    int* ptr = &x;          // ptr es un puntero, & es direccion de

    cout << x << endl;             // imprime: 42
    cout << ptr << endl;           // imprime algo como: 0x7ffee3a2b4ac (una dirección de memoria)
    cout << *ptr << endl;          // imprime: 42  →  el * "desreferencia": "andá a esa dirección y traeme el valor"
}



// array y punteros
void array_y_punteros()
{
    int numeros[5] = {12, 5, 30, 1, 8};
    int* ptr = numeros;             // p apunta al primer elemento (12)

    cout << numeros << endl;      // imprime una dirección de memoria (el array "decae" a puntero)
    cout << *numeros << endl;     // imprime 12 → el valor del PRIMER elemento
    cout << numeros[0] << endl;   // imprime 12 → lo mismo, pero con sintaxis de array



    cout << "==================" << endl;
    cout << *ptr << endl;      // 12
    cout << *(ptr + 1) << endl; // 5 → avanzó UN int (4 bytes), no 1 byte
    cout << *(ptr + 2) << endl; // 30

    ptr++;                      // ahora p apunta al segundo elemento
    cout << *ptr << endl;       // 5

    // sizeof(numeros) = 20   // el array completo: 5 elementos × 4 bytes cada uno
    // sizeof(p) = 8           // el puntero, siempre 8 bytes en 64 bits
}

int main()
{
    // paso de parametros por ref o valor

    ejemplo_de_paso_params_funciones();
    array_y_punteros();

    return true;
}



