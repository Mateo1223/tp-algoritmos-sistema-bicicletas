#include "Viaje.h"
#include <iostream>

using namespace std;

Viaje::Viaje()
{
    id = 0;
    biciId = 0;
    dniUsuario = 0;
    estacionOrigen = "";
    estacionDestino = "";
    fecha = 0;
    duracionMin = 0;
}

Viaje::Viaje(int id, int biciId, int dniUsuario, const string& estacionOrigen,
             const string& estacionDestino, int fecha, int duracionMin)
{
    this->id = id;
    this->biciId = biciId;
    this->dniUsuario = dniUsuario;
    this->estacionOrigen = estacionOrigen;
    this->estacionDestino = estacionDestino;
    this->fecha = fecha;
    this->duracionMin = duracionMin;
}

int Viaje::obtenerId() const
{
    return id;
}

int Viaje::obtenerBiciId() const
{
    return biciId;
}

int Viaje::obtenerDniUsuario() const
{
    return dniUsuario;
}

string Viaje::obtenerEstacionOrigen() const
{
    return estacionOrigen;
}

string Viaje::obtenerEstacionDestino() const
{
    return estacionDestino;
}

int Viaje::obtenerFecha() const
{
    return fecha;
}

int Viaje::obtenerDuracionMin() const
{
    return duracionMin;
}

bool Viaje::estaEnRangoDeFechas(int desde, int hasta) const
{
    return (fecha >= desde && fecha <= hasta);
}

bool Viaje::esDelUsuario(int dni) const
{
    return (dniUsuario == dni);
}

bool Viaje::parteDeLaEstacion(const string& codigoEstacion) const
{
    return (estacionOrigen == codigoEstacion);
}

void Viaje::mostrar() const
{
    cout << "  Viaje " << id
         << " | Bici: " << biciId
         << " | DNI: " << dniUsuario
         << " | " << estacionOrigen << " -> " << estacionDestino
         << " | Fecha: " << fecha
         << " | Duracion: " << duracionMin << " min" << endl;
}

int Viaje::fechaDesdeTexto(const string& texto)
{
    return stoi(texto);
}
