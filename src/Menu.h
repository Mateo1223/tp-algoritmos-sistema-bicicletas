#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>
#include "SistemaBicicletas.h"

// Menu por consola del Sprint 1: permite probar el Bloque A (gestion de
// estaciones) y la informacion general del sistema.
class Menu
{
private:
    // atributos
    SistemaBicicletas& sistema;
    bool entradaTerminada;   // se pone en true cuando se termina la entrada

    // opciones del menu
    void mostrarMenuPrincipal() const;
    void ejecutarGestionDeEstaciones();
    void ejecutarInformacionGeneral();

    // ayudas de entrada y salida
    int leerEntero(const std::string& mensaje);
    std::string leerTexto(const std::string& mensaje);
    void mostrarTitulo(const std::string& titulo) const;

public:
    // pos: crea el menu asociado al sistema indicado
    Menu(SistemaBicicletas& sistema);

    // pos: muestra el menu y ejecuta las opciones hasta que se elige salir
    void ejecutar();
};

#endif // MENU_H_INCLUDED
