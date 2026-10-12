#ifndef TABLAHASH_H_INCLUDED
#define TABLAHASH_H_INCLUDED

#include <string>
#include "Estacion.h"

// Tabla de hash que indexa estaciones por su codigo, con resolucion de
// colisiones por encadenamiento (chaining): cada posicion de la tabla es el
// puntero al primero de una lista enlazada de nodos con la misma direccion.
//
// Funcion de hash: se toma la clave como un numero en base 128 (el apunte de
// la catedra propone esta base para los codigos ASCII) y luego se aplica el
// metodo de la division (modulo) con un tamanio de tabla primo.
class TablaHash
{
private:
    struct NodoHash
    {
        std::string clave;
        Estacion* valor = 0;
        NodoHash* siguiente = 0;
    };

    // atributos
    NodoHash** tabla;        // arreglo dinamico de punteros a listas
    int tamanio;             // cantidad de posiciones (numero primo)
    int cantidad;            // cantidad de estaciones almacenadas
    int colisiones;          // inserciones que cayeron en una posicion ocupada
    int largoMaximoCadena;   // mayor cantidad de nodos de una misma posicion

public:
    // pre: tamanioDeseado > 0
    // pos: crea la tabla con un tamanio primo mayor o igual al deseado
    TablaHash(int tamanioDeseado);

    // pos: libera la memoria de todos los nodos y del arreglo de la tabla
    ~TablaHash();

    // pos: devuelve la posicion que le corresponde a la clave
    int funcionHash(const std::string& clave) const;

    // pos: inserta la estacion con su clave; si la clave ya existe actualiza el
    //      valor. Cuenta una colision si la posicion ya tenia elementos
    void insertar(const std::string& clave, Estacion* valor);

    // pos: devuelve la estacion asociada a la clave, o 0 si no esta
    Estacion* buscar(const std::string& clave) const;

    // pre: la clave existe en la tabla
    // pos: elimina el nodo de la clave y devuelve true; false si no existia
    bool eliminar(const std::string& clave);

    // pos: devuelve true si la clave esta en la tabla
    bool contiene(const std::string& clave) const;

    // consultas de estado
    int obtenerCantidad() const;
    int obtenerTamanio() const;
    int obtenerColisiones() const;
    int obtenerLargoMaximoCadena() const;
    double factorDeCarga() const;

    // pos: muestra cantidad de elementos, colisiones y factor de carga
    void mostrarEstadisticas() const;

    // pos: devuelve el primo mas cercano mayor o igual al valor indicado
    static int primoMayorOIgual(int valor);

    // la tabla no se copia: se maneja por puntero o por referencia
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;
};

#endif // TABLAHASH_H_INCLUDED
