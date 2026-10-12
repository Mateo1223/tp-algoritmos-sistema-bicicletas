#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

#include "Estacion.h"

// Algoritmos de ordenamiento implementados a mano sobre un arreglo de
// punteros a estacion. No se utiliza la funcion sort de la STL.
//
// criterio 1: por capacidad de anclajes (de mayor a menor)
// criterio 2: por bicicletas disponibles (de mayor a menor)
class Ordenamiento
{
public:
    // pos: ordena el arreglo con el metodo de burbujeo
    static void burbujeo(Estacion** arreglo, int cantidad, int criterio);

    // pos: ordena el arreglo con el metodo de seleccion
    static void seleccion(Estacion** arreglo, int cantidad, int criterio);

    // pos: ordena el arreglo con el metodo de insercion
    static void insercion(Estacion** arreglo, int cantidad, int criterio);

    // pos: devuelve true si la primera estacion debe ir antes que la segunda
    static bool debeIrAntes(Estacion* primera, Estacion* segunda, int criterio);
};

#endif // ORDENAMIENTO_H_INCLUDED
