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


int main()
{
    // paso de parametros por ref o valor

    ejemplo_de_paso_params_funciones();

    return true;
}



