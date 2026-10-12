#ifndef ESTACION_H_INCLUDED
#define ESTACION_H_INCLUDED

#include <string>
#include "Cola.h"

// Representa una estacion de la red de bicicletas publicas.
// Cada estacion conoce su ubicacion, su capacidad de anclajes, cuantas
// bicicletas tiene disponibles y la cola de usuarios que esperan una bici.
class Estacion
{
private:
    // atributos
    std::string codigo;
    std::string nombre;
    std::string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;
    int indiceGrafo;   // posicion que ocupa la estacion como vertice del grafo
    Cola colaEspera;   // usuarios (dni) esperando una bicicleta

public:
    // pos: crea una estacion vacia (sin codigo ni bicicletas)
    Estacion();

    // pos: crea una estacion con los datos indicados
    Estacion(const std::string& codigo, const std::string& nombre, const std::string& barrio,
             int capacidadAnclajes, int bicisDisponibles);

    // consultas
    std::string obtenerCodigo() const;
    std::string obtenerNombre() const;
    std::string obtenerBarrio() const;
    int obtenerCapacidadAnclajes() const;
    int obtenerBicisDisponibles() const;
    int obtenerIndiceGrafo() const;
    int calcularFaltantes() const;
    double calcularOcupacion() const;
    bool tieneBajaOcupacion() const;
    Cola& obtenerColaEspera();

    // modificaciones
    void cambiarIndiceGrafo(int indice);
    void cambiarBicisDisponibles(int cantidad);

    // pre: bicisDisponibles > 0
    // pos: descuenta una bicicleta y devuelve true; si no hay, devuelve false
    bool retirarBicicleta();

    // pre: bicisDisponibles < capacidadAnclajes
    // pos: suma una bicicleta y devuelve true; si la estacion esta llena, false
    bool devolverBicicleta();

    // pos: muestra los datos de la estacion y su cola de espera
    void mostrar() const;
};

#endif // ESTACION_H_INCLUDED
