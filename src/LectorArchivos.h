#ifndef LECTORARCHIVOS_H_INCLUDED
#define LECTORARCHIVOS_H_INCLUDED

#include <string>
#include "Estacion.h"
#include "Bicicleta.h"
#include "Viaje.h"

// Conexion leida del archivo de ciclovias (dos codigos de estacion)
struct Conexion
{
    std::string estacionA;
    std::string estacionB;
};

// Lee los archivos de entrada del sistema.
// Cada archivo tiene un registro por linea, con los campos separados por
// espacios. Se asume que los archivos estan bien formados; de todos modos, si
// un archivo no se puede abrir se informa y se devuelve false.
class LectorArchivos
{
public:
    // Pos: carga las estaciones del archivo en un arreglo dinamico nuevo.
    //      Devuelve true si pudo leer el archivo
    static bool leerEstaciones(const std::string& ruta, Estacion**& estaciones, int& cantidad);

    // Pos: carga las bicicletas del archivo en un arreglo dinamico nuevo
    static bool leerBicicletas(const std::string& ruta, Bicicleta**& bicicletas, int& cantidad);

    // Pos: carga los viajes del archivo en un arreglo dinamico nuevo
    static bool leerViajes(const std::string& ruta, Viaje**& viajes, int& cantidad);

    // Pos: carga las conexiones de ciclovias en un arreglo dinamico nuevo
    static bool leerCiclovias(const std::string& ruta, Conexion*& conexiones, int& cantidad);

private:
    // Pos: cuenta las lineas con contenido del archivo
    static int contarLineas(const std::string& ruta);
};

#endif // LECTORARCHIVOS_H_INCLUDED
