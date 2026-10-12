#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu(SistemaBicicletas& sistema) : sistema(sistema)
{
    entradaTerminada = false;
}

// ---------------- ayudas de entrada y salida ----------------

int Menu::leerEntero(const string& mensaje)
{
    int valor = 0;

    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        if (cin.eof())
        {
            entradaTerminada = true;
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Entrada invalida: se esperaba un numero." << endl;
    }
}

string Menu::leerTexto(const string& mensaje)
{
    cout << mensaje;
    string valor;
    if (!getline(cin, valor))
    {
        entradaTerminada = true;
        return "";
    }
    return valor;
}

void Menu::mostrarTitulo(const string& titulo) const
{
    cout << endl << "==================== " << titulo << " ====================" << endl;
}

// ---------------- menu principal ----------------

void Menu::mostrarMenuPrincipal() const
{
    cout << endl;
    cout << "=========== SISTEMA DE BICICLETAS PUBLICAS (Sprint 1) ===========" << endl;
    cout << " 1) Gestion de estaciones" << endl;
    cout << " 2) Informacion general del sistema" << endl;
    cout << " 0) Salir" << endl;
    cout << "==================================================================" << endl;
}

void Menu::ejecutar()
{
    int opcion = -1;

    while (opcion != 0 && !entradaTerminada)
    {
        mostrarMenuPrincipal();
        opcion = leerEntero("Opcion: ");

        switch (opcion)
        {
            case 1:
                ejecutarGestionDeEstaciones();
                break;
            case 2:
                ejecutarInformacionGeneral();
                break;
            case 0:
                cout << endl << "Fin del programa." << endl;
                break;
            default:
                cout << "  Opcion invalida." << endl;
                break;
        }
    }
}

// ---------------- 1) gestion de estaciones ----------------

void Menu::ejecutarGestionDeEstaciones()
{
    int opcion = -1;

    while (opcion != 0 && !entradaTerminada)
    {
        mostrarTitulo("1) GESTION DE ESTACIONES");
        cout << " 1) Mostrar la informacion de una estacion dado su codigo" << endl;
        cout << " 2) Agregar una estacion nueva al sistema" << endl;
        cout << " 3) Eliminar una estacion existente" << endl;
        cout << " 4) Listar todas las estaciones ordenadas" << endl;
        cout << " 5) Listar estaciones con menos del 20% de ocupacion" << endl;
        cout << " 6) Recorrido con menor cantidad de tramos entre dos estaciones (BFS)" << endl;
        cout << " 0) Volver al menu principal" << endl;

        opcion = leerEntero("Opcion: ");

        if (opcion == 1)
        {
            string codigo = leerTexto("  Codigo de la estacion: ");
            sistema.mostrarEstacion(codigo);
        }
        else if (opcion == 2)
        {
            string codigo = leerTexto("  Codigo: ");
            string nombre = leerTexto("  Nombre: ");
            string barrio = leerTexto("  Barrio: ");
            int capacidad = leerEntero("  Capacidad de anclajes: ");
            int disponibles = leerEntero("  Bicicletas disponibles: ");
            sistema.agregarEstacion(codigo, nombre, barrio, capacidad, disponibles);
        }
        else if (opcion == 3)
        {
            string codigo = leerTexto("  Codigo de la estacion a eliminar: ");
            sistema.eliminarEstacion(codigo);
        }
        else if (opcion == 4)
        {
            cout << "  Criterio: 1 = capacidad de anclajes, 2 = bicicletas disponibles" << endl;
            int criterio = leerEntero("  Criterio: ");
            cout << "  Algoritmo de ordenamiento: 1 = burbujeo, 2 = seleccion, 3 = insercion" << endl;
            int algoritmo = leerEntero("  Algoritmo: ");
            sistema.listarEstacionesOrdenadas(criterio, algoritmo);
        }
        else if (opcion == 5)
        {
            sistema.listarEstacionesBajaOcupacion();
        }
        else if (opcion == 6)
        {
            string origen = leerTexto("  Codigo de la estacion de origen: ");
            string destino = leerTexto("  Codigo de la estacion de destino: ");
            sistema.recorridoMinimoTramos(origen, destino);
        }
        else if (opcion != 0)
        {
            cout << "  Opcion invalida." << endl;
        }
    }
}

// ---------------- 2) informacion general ----------------

void Menu::ejecutarInformacionGeneral()
{
    int opcion = -1;

    while (opcion != 0 && !entradaTerminada)
    {
        mostrarTitulo("2) INFORMACION GENERAL");
        cout << " 1) Estadisticas de la tabla de hash (colisiones y factor de carga)" << endl;
        cout << " 2) Ver el grafo de ciclovias (listas de adyacencia)" << endl;
        cout << " 3) Resumen general del sistema" << endl;
        cout << " 0) Volver al menu principal" << endl;

        opcion = leerEntero("Opcion: ");

        if (opcion == 1)
        {
            sistema.mostrarEstadisticasHash();
        }
        else if (opcion == 2)
        {
            sistema.mostrarGrafo();
        }
        else if (opcion == 3)
        {
            sistema.mostrarInformacionGeneral();
        }
        else if (opcion != 0)
        {
            cout << "  Opcion invalida." << endl;
        }
    }
}
