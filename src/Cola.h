#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

// Cola FIFO (first in, first out) implementada a mano con nodos enlazados.
// No se utiliza la cola de la STL: la estructura se resuelve con punteros.
// Se usa para la cola de espera de cada estacion.
class Cola
{
private:
    struct NodoCola
    {
        int dato;
        NodoCola* siguiente;
    };

    // atributos
    NodoCola* primero;
    NodoCola* ultimo;
    int cantidad;

public:
    // pos: crea una cola vacia
    Cola();

    // pos: libera toda la memoria utilizada por la cola
    ~Cola();

    // pos: agrega el dato al final de la cola
    void acolar(int dato);

    // pre: la cola no esta vacia
    // pos: quita y devuelve el primer elemento de la cola
    int desacolar();

    // pre: la cola no esta vacia
    // pos: devuelve el primer elemento sin quitarlo de la cola
    int obtenerPrimero() const;

    // pos: devuelve true si la cola no tiene elementos
    bool estaVacia() const;

    // pos: devuelve la cantidad de elementos encolados
    int obtenerCantidad() const;

    // pos: devuelve true si el dato se encuentra en la cola, sin alterar el orden
    bool contiene(int dato) const;

    // pos: muestra por pantalla los elementos de la cola, del primero al ultimo
    void mostrar() const;

    // la cola no se copia: se maneja siempre por referencia o por puntero
    Cola(const Cola&) = delete;
    Cola& operator=(const Cola&) = delete;
};

#endif // COLA_H_INCLUDED
