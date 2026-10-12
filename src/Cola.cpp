#include "Cola.h"
#include <iostream>

using namespace std;

Cola::Cola()
{
    primero = 0;
    ultimo = 0;
    cantidad = 0;
}

Cola::~Cola()
{
    while (!estaVacia())
    {
        desacolar();
    }
}

void Cola::acolar(int dato)
{
    NodoCola* nuevo = new NodoCola;
    nuevo->dato = dato;
    nuevo->siguiente = 0;

    if (estaVacia())
    {
        primero = nuevo;
    }
    else
    {
        ultimo->siguiente = nuevo;
    }

    ultimo = nuevo;
    cantidad++;
}

int Cola::desacolar()
{
    NodoCola* borrar = primero;
    int dato = borrar->dato;

    primero = borrar->siguiente;
    if (primero == 0)
    {
        ultimo = 0;
    }

    delete borrar;
    cantidad--;

    return dato;
}

int Cola::obtenerPrimero() const
{
    return this->primero->dato;
}

bool Cola::estaVacia() const
{
    return (cantidad == 0);
}

int Cola::obtenerCantidad() const
{
    return cantidad;
}

bool Cola::contiene(int dato) const
{
    NodoCola* aux = primero;
    while (aux != 0)
    {
        if (aux->dato == dato)
        {
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void Cola::mostrar() const
{
    cout << "[";
    NodoCola* aux = primero;
    while (aux != 0)
    {
        cout << aux->dato;
        if (aux->siguiente != 0)
        {
            cout << ", ";
        }
        aux = aux->siguiente;
    }
    cout << "]";
}
