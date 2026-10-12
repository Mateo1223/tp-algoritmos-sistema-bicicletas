#include "Estacion.h"
#include <iostream>

using namespace std;

Estacion::Estacion()
{
    codigo = "";
    nombre = "";
    barrio = "";
    capacidadAnclajes = 0;
    bicisDisponibles = 0;
    indiceGrafo = -1;
}

Estacion::Estacion(const string& codigo, const string& nombre, const string& barrio,
                   int capacidadAnclajes, int bicisDisponibles)
{
    this->codigo = codigo;
    this->nombre = nombre;
    this->barrio = barrio;
    this->capacidadAnclajes = capacidadAnclajes;
    this->bicisDisponibles = bicisDisponibles;
    this->indiceGrafo = -1;
}

string Estacion::obtenerCodigo() const
{
    return codigo;
}

string Estacion::obtenerNombre() const
{
    return nombre;
}

string Estacion::obtenerBarrio() const
{
    return barrio;
}

int Estacion::obtenerCapacidadAnclajes() const
{
    return capacidadAnclajes;
}

int Estacion::obtenerBicisDisponibles() const
{
    return bicisDisponibles;
}

int Estacion::obtenerIndiceGrafo() const
{
    return indiceGrafo;
}

int Estacion::calcularFaltantes() const
{
    return capacidadAnclajes - bicisDisponibles;
}

double Estacion::calcularOcupacion() const
{
    if (capacidadAnclajes == 0)
    {
        return 0.0;
    }
    return (100.0 * bicisDisponibles) / capacidadAnclajes;
}

bool Estacion::tieneBajaOcupacion() const
{
    return (calcularOcupacion() < 20.0);
}

Cola& Estacion::obtenerColaEspera()
{
    return colaEspera;
}

void Estacion::cambiarIndiceGrafo(int indice)
{
    indiceGrafo = indice;
}

void Estacion::cambiarBicisDisponibles(int cantidad)
{
    bicisDisponibles = cantidad;
}

bool Estacion::retirarBicicleta()
{
    if (bicisDisponibles == 0)
    {
        return false;
    }
    bicisDisponibles--;
    return true;
}

bool Estacion::devolverBicicleta()
{
    if (bicisDisponibles >= capacidadAnclajes)
    {
        return false;
    }
    bicisDisponibles++;
    return true;
}

void Estacion::mostrar() const
{
    cout << "  Codigo: " << codigo
         << " | Nombre: " << nombre
         << " | Barrio: " << barrio
         << " | Anclajes: " << capacidadAnclajes
         << " | Bicis disponibles: " << bicisDisponibles
         << " | Faltantes: " << calcularFaltantes()
         << " | Ocupacion: " << calcularOcupacion() << "%" << endl;
    cout << "  Cola de espera: ";
    colaEspera.mostrar();
    cout << endl;
}
