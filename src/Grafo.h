#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "Estacion.h"

// Grafo no dirigido que representa la red de ciclovias entre estaciones.
// Se implementa con listas de adyacencia hechas a mano: un arreglo dinamico de
// punteros donde cada posicion apunta a la lista de vertices adyacentes.
//
// El grafo no es duenio de las estaciones: solo las referencia.
class Grafo
{
private:
    struct NodoAdyacencia
    {
        int vertice;
        NodoAdyacencia* siguiente;
    };

    // atributos
    NodoAdyacencia** adyacencia;   // arreglo de listas de adyacencia
    Estacion** estaciones;         // estacion que representa cada vertice
    int cantidadVertices;
    int cantidadAristas;
    int capacidad;

    // pos: agrega destino a la lista de adyacencia de origen
    void agregarAdyacente(int origen, int destino);

    // pos: duplica la capacidad de los arreglos cuando se llenan
    void redimensionar();

    // pos: libera todas las listas de adyacencia
    void liberarListas();

public:
    // pos: crea un grafo vacio
    Grafo();

    // pos: libera la memoria de las listas y de los arreglos
    ~Grafo();

    // pre: la estacion no fue agregada antes
    // pos: agrega la estacion como vertice y devuelve su indice
    int agregarVertice(Estacion* estacion);

    // pre: origen y destino son indices de vertices validos
    // pos: agrega la arista en los dos sentidos (el grafo es no dirigido)
    void agregarArista(int origen, int destino);

    // pre: vertice es un indice valido
    // pos: quita el vertice y todas sus aristas del grafo
    void eliminarVertice(int vertice);

    // pos: devuelve el indice de la estacion en el grafo, o -1 si no esta
    int buscarVertice(const std::string& codigoEstacion) const;

    // consultas
    int obtenerCantidadVertices() const;
    int obtenerCantidadAristas() const;
    Estacion* obtenerEstacion(int vertice) const;
    int obtenerGrado(int vertice) const;

    // pre: origen y destino son indices validos y camino tiene espacio para
    //      cantidadVertices estaciones
    // pos: busca el camino con menor cantidad de tramos usando BFS. Devuelve
    //      true y completa camino/tramos si existe, false si no hay recorrido
    bool caminoMinimo(int origen, int destino, Estacion** camino, int& tramos) const;

    // pos: muestra las listas de adyacencia del grafo
    void mostrar() const;

    // el grafo no se copia
    Grafo(const Grafo&) = delete;
    Grafo& operator=(const Grafo&) = delete;
};

#endif // GRAFO_H_INCLUDED
