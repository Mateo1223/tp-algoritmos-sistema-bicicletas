#ifndef BICICLETA_H_INCLUDED
#define BICICLETA_H_INCLUDED

#include <string>

// Tipo de bicicleta: las electricas tienen prioridad maxima en el taller.
enum TipoBicicleta
{
    MECANICA,
    ELECTRICA
};

// Estado de la bicicleta: las averiadas van al taller de reparaciones.
enum EstadoBicicleta
{
    OK,
    AVERIADA
};

// Representa una bicicleta de la red.
class Bicicleta
{
private:
    // atributos
    int id;
    std::string codigoEstacion;
    TipoBicicleta tipo;
    EstadoBicicleta estado;
    int kilometros;

public:
    // pos: crea una bicicleta sin datos
    Bicicleta();

    // pos: crea una bicicleta con los datos indicados
    Bicicleta(int id, const std::string& codigoEstacion, TipoBicicleta tipo,
              EstadoBicicleta estado, int kilometros);

    // consultas
    int obtenerId() const;
    std::string obtenerCodigoEstacion() const;
    TipoBicicleta obtenerTipo() const;
    EstadoBicicleta obtenerEstado() const;
    int obtenerKilometros() const;
    bool esElectrica() const;
    bool estaAveriada() const;
    bool superaKilometros(int limite) const;
    std::string tipoComoTexto() const;
    std::string estadoComoTexto() const;

    // modificaciones
    void cambiarCodigoEstacion(const std::string& codigo);
    void cambiarEstado(EstadoBicicleta nuevoEstado);
    void cambiarKilometros(int nuevosKilometros);

    // pos: muestra los datos de la bicicleta
    void mostrar() const;

    // pos: convierte el texto de un archivo al tipo correspondiente
    static TipoBicicleta tipoDesdeTexto(const std::string& texto);
    static EstadoBicicleta estadoDesdeTexto(const std::string& texto);
};

#endif // BICICLETA_H_INCLUDED
