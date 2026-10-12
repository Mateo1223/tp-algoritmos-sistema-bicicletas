#ifndef VIAJE_H_INCLUDED
#define VIAJE_H_INCLUDED

#include <string>

// Representa un viaje realizado por un usuario.
// La fecha se guarda como entero con formato AAAAMMDD, por lo que se puede
// comparar directamente para saber si esta dentro de un rango.
class Viaje
{
private:
    // atributos
    int id;
    int biciId;
    int dniUsuario;
    std::string estacionOrigen;
    std::string estacionDestino;
    int fecha;        // AAAAMMDD
    int duracionMin;

public:
    // pos: crea un viaje sin datos
    Viaje();

    // pos: crea un viaje con los datos indicados
    Viaje(int id, int biciId, int dniUsuario, const std::string& estacionOrigen,
          const std::string& estacionDestino, int fecha, int duracionMin);

    // consultas
    int obtenerId() const;
    int obtenerBiciId() const;
    int obtenerDniUsuario() const;
    std::string obtenerEstacionOrigen() const;
    std::string obtenerEstacionDestino() const;
    int obtenerFecha() const;
    int obtenerDuracionMin() const;

    // pos: devuelve true si la fecha esta entre desde y hasta (inclusive)
    bool estaEnRangoDeFechas(int desde, int hasta) const;

    // pos: devuelve true si el viaje pertenece al usuario indicado
    bool esDelUsuario(int dni) const;

    // pos: devuelve true si el viaje comienza en la estacion indicada
    bool parteDeLaEstacion(const std::string& codigoEstacion) const;

    // pos: muestra los datos del viaje
    void mostrar() const;

    // pos: convierte el texto de un archivo (AAAAMMDD) a entero
    static int fechaDesdeTexto(const std::string& texto);
};

#endif // VIAJE_H_INCLUDED
