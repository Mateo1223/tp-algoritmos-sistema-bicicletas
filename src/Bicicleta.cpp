#include "Bicicleta.h"
#include <iostream>

using namespace std;

Bicicleta::Bicicleta()
{
    id = 0;
    codigoEstacion = "";
    tipo = MECANICA;
    estado = OK;
    kilometros = 0;
}

Bicicleta::Bicicleta(int id, const string& codigoEstacion, TipoBicicleta tipo,
                     EstadoBicicleta estado, int kilometros)
{
    this->id = id;
    this->codigoEstacion = codigoEstacion;
    this->tipo = tipo;
    this->estado = estado;
    this->kilometros = kilometros;
}

int Bicicleta::obtenerId() const
{
    return id;
}

string Bicicleta::obtenerCodigoEstacion() const
{
    return codigoEstacion;
}

TipoBicicleta Bicicleta::obtenerTipo() const
{
    return tipo;
}

EstadoBicicleta Bicicleta::obtenerEstado() const
{
    return estado;
}

int Bicicleta::obtenerKilometros() const
{
    return kilometros;
}

bool Bicicleta::esElectrica() const
{
    return (tipo == ELECTRICA);
}

bool Bicicleta::estaAveriada() const
{
    return (estado == AVERIADA);
}

bool Bicicleta::superaKilometros(int limite) const
{
    return (kilometros > limite);
}

string Bicicleta::tipoComoTexto() const
{
    if (tipo == ELECTRICA)
    {
        return "Electrica";
    }
    return "Mecanica";
}

string Bicicleta::estadoComoTexto() const
{
    if (estado == AVERIADA)
    {
        return "Averiada";
    }
    return "OK";
}

void Bicicleta::cambiarCodigoEstacion(const string& codigo)
{
    codigoEstacion = codigo;
}

void Bicicleta::cambiarEstado(EstadoBicicleta nuevoEstado)
{
    estado = nuevoEstado;
}

void Bicicleta::cambiarKilometros(int nuevosKilometros)
{
    kilometros = nuevosKilometros;
}

void Bicicleta::mostrar() const
{
    cout << "  Bici " << id
         << " | Estacion: " << codigoEstacion
         << " | Tipo: " << tipoComoTexto()
         << " | Estado: " << estadoComoTexto()
         << " | Kilometros: " << kilometros << endl;
}

TipoBicicleta Bicicleta::tipoDesdeTexto(const string& texto)
{
    if (texto == "Electrica")
    {
        return ELECTRICA;
    }
    return MECANICA;
}

EstadoBicicleta Bicicleta::estadoDesdeTexto(const string& texto)
{
    if (texto == "Averiada")
    {
        return AVERIADA;
    }
    return OK;
}
