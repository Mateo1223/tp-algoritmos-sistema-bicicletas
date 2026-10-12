#include "LectorArchivos.h"
#include <fstream>
#include <sstream>

using namespace std;

int LectorArchivos::contarLineas(const string& ruta)
{
    ifstream archivo(ruta.c_str());
    if (!archivo.is_open())
    {
        return -1;
    }

    int contador = 0;
    string linea;
    while (getline(archivo, linea))
    {
        if (!linea.empty())
        {
            contador++;
        }
    }
    archivo.close();

    return contador;
}

bool LectorArchivos::leerEstaciones(const string& ruta, Estacion**& estaciones, int& cantidad)
{
    int lineas = contarLineas(ruta);
    if (lineas < 0)
    {
        return false;
    }

    estaciones = new Estacion*[lineas];
    cantidad = 0;

    ifstream archivo(ruta.c_str());
    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        istringstream campos(linea);
        string codigo;
        string nombre;
        string barrio;
        int capacidadAnclajes;
        int bicisDisponibles;

        campos >> codigo >> nombre >> barrio >> capacidadAnclajes >> bicisDisponibles;

        estaciones[cantidad] = new Estacion(codigo, nombre, barrio, capacidadAnclajes, bicisDisponibles);
        cantidad++;
    }
    archivo.close();

    return true;
}

bool LectorArchivos::leerBicicletas(const string& ruta, Bicicleta**& bicicletas, int& cantidad)
{
    int lineas = contarLineas(ruta);
    if (lineas < 0)
    {
        return false;
    }

    bicicletas = new Bicicleta*[lineas];
    cantidad = 0;

    ifstream archivo(ruta.c_str());
    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        istringstream campos(linea);
        int id;
        string codigoEstacion;
        string tipo;
        string estado;
        int kilometros;

        campos >> id >> codigoEstacion >> tipo >> estado >> kilometros;

        bicicletas[cantidad] = new Bicicleta(id, codigoEstacion,
                                             Bicicleta::tipoDesdeTexto(tipo),
                                             Bicicleta::estadoDesdeTexto(estado),
                                             kilometros);
        cantidad++;
    }
    archivo.close();

    return true;
}

bool LectorArchivos::leerViajes(const string& ruta, Viaje**& viajes, int& cantidad)
{
    int lineas = contarLineas(ruta);
    if (lineas < 0)
    {
        return false;
    }

    viajes = new Viaje*[lineas];
    cantidad = 0;

    ifstream archivo(ruta.c_str());
    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        istringstream campos(linea);
        int id;
        int biciId;
        int dniUsuario;
        string estacionOrigen;
        string estacionDestino;
        string fecha;
        int duracionMin;

        campos >> id >> biciId >> dniUsuario >> estacionOrigen >> estacionDestino
               >> fecha >> duracionMin;

        viajes[cantidad] = new Viaje(id, biciId, dniUsuario, estacionOrigen,
                                     estacionDestino, Viaje::fechaDesdeTexto(fecha),
                                     duracionMin);
        cantidad++;
    }
    archivo.close();

    return true;
}

bool LectorArchivos::leerCiclovias(const string& ruta, Conexion*& conexiones, int& cantidad)
{
    int lineas = contarLineas(ruta);
    if (lineas < 0)
    {
        return false;
    }

    conexiones = new Conexion[lineas];
    cantidad = 0;

    ifstream archivo(ruta.c_str());
    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        istringstream campos(linea);
        string estacionA;
        string estacionB;

        campos >> estacionA >> estacionB;

        conexiones[cantidad].estacionA = estacionA;
        conexiones[cantidad].estacionB = estacionB;
        cantidad++;
    }
    archivo.close();

    return true;
}
