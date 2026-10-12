#include "TablaHash.h"
#include <iostream>

using namespace std;

TablaHash::TablaHash(int tamanioDeseado)
{
    tamanio = primoMayorOIgual(tamanioDeseado);
    cantidad = 0;
    colisiones = 0;
    largoMaximoCadena = 0;

    tabla = new NodoHash*[tamanio];
    for (int i = 0; i < tamanio; i++)
    {
        tabla[i] = 0;
    }
}

TablaHash::~TablaHash()
{
    for (int i = 0; i < tamanio; i++)
    {
        NodoHash* aux = tabla[i];
        while (aux != 0)
        {
            NodoHash* borrar = aux;
            aux = aux->siguiente;
            delete borrar;
        }
    }
    delete[] tabla;
}

int TablaHash::funcionHash(const string& clave) const
{
    // se interpreta la clave como un numero en base 128 y se aplica
    // el metodo de la division (modulo) con el tamanio primo de la tabla
    long acumulado = 0;
    for (size_t i = 0; i < clave.size(); i++)
    {
        acumulado = (acumulado * 128 + (unsigned char)clave[i]) % tamanio;
    }
    return (int)acumulado;
}

void TablaHash::insertar(const string& clave, Estacion* valor)
{
    int posicion = funcionHash(clave);

    NodoHash* aux = tabla[posicion];
    while (aux != 0)
    {
        if (aux->clave == clave)
        {
            aux->valor = valor;   // la clave ya existia: se actualiza el valor
            return;
        }
        aux = aux->siguiente;
    }

    if (tabla[posicion] != 0)
    {
        colisiones++;
    }

    NodoHash* nuevo = new NodoHash;
    nuevo->clave = clave;
    nuevo->valor = valor;
    nuevo->siguiente = tabla[posicion];
    tabla[posicion] = nuevo;
    cantidad++;

    int largo = 0;
    aux = tabla[posicion];
    while (aux != 0)
    {
        largo++;
        aux = aux->siguiente;
    }
    if (largo > largoMaximoCadena)
    {
        largoMaximoCadena = largo;
    }
}

Estacion* TablaHash::buscar(const string& clave) const
{
    int posicion = funcionHash(clave);

    NodoHash* aux = tabla[posicion];
    while (aux != 0)
    {
        if (aux->clave == clave)
        {
            return aux->valor;
        }
        aux = aux->siguiente;
    }
    return 0;
}

bool TablaHash::eliminar(const string& clave)
{
    int posicion = funcionHash(clave);

    NodoHash* actual = tabla[posicion];
    NodoHash* anterior = 0;

    while (actual != 0)
    {
        if (actual->clave == clave)
        {
            if (anterior == 0)
            {
                tabla[posicion] = actual->siguiente;
            }
            else
            {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

bool TablaHash::contiene(const string& clave) const
{
    return (buscar(clave) != 0);
}

int TablaHash::obtenerCantidad() const
{
    return cantidad;
}

int TablaHash::obtenerTamanio() const
{
    return tamanio;
}

int TablaHash::obtenerColisiones() const
{
    return colisiones;
}

int TablaHash::obtenerLargoMaximoCadena() const
{
    return largoMaximoCadena;
}

double TablaHash::factorDeCarga() const
{
    return (double)cantidad / tamanio;
}

void TablaHash::mostrarEstadisticas() const
{
    cout << "  Tabla de hash de estaciones" << endl;
    cout << "   Tamanio de la tabla (primo): " << tamanio << endl;
    cout << "   Estaciones almacenadas: " << cantidad << endl;
    cout << "   Colisiones producidas: " << colisiones << endl;
    cout << "   Largo maximo de una cadena: " << largoMaximoCadena << endl;
    cout << "   Factor de carga (n/m): " << factorDeCarga();
    if (factorDeCarga() <= 0.8)
    {
        cout << " (dentro del valor recomendado <= 0.8)" << endl;
    }
    else
    {
        cout << " (por encima del valor recomendado 0.8)" << endl;
    }
}

int TablaHash::primoMayorOIgual(int valor)
{
    if (valor < 2)
    {
        return 2;
    }

    int candidato = valor;
    bool encontrado = false;

    while (!encontrado)
    {
        bool esPrimo = true;
        for (int divisor = 2; divisor * divisor <= candidato; divisor++)
        {
            if (candidato % divisor == 0)
            {
                esPrimo = false;
                break;
            }
        }
        if (esPrimo)
        {
            encontrado = true;
        }
        else
        {
            candidato++;
        }
    }
    return candidato;
}
