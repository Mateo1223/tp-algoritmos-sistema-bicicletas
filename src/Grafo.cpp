#include "Grafo.h"
#include "Cola.h"
#include <iostream>

using namespace std;

Grafo::Grafo()
{
    capacidad = 8;
    cantidadVertices = 0;
    cantidadAristas = 0;
    adyacencia = new NodoAdyacencia*[capacidad];
    estaciones = new Estacion*[capacidad];
    for (int i = 0; i < capacidad; i++)
    {
        adyacencia[i] = 0;
        estaciones[i] = 0;
    }
}

Grafo::~Grafo()
{
    liberarListas();
    delete[] adyacencia;
    delete[] estaciones;
}

void Grafo::liberarListas()
{
    for (int i = 0; i < cantidadVertices; i++)
    {
        NodoAdyacencia* aux = adyacencia[i];
        while (aux != 0)
        {
            NodoAdyacencia* borrar = aux;
            aux = aux->siguiente;
            delete borrar;
        }
        adyacencia[i] = 0;
    }
}

void Grafo::redimensionar()
{
    int nuevaCapacidad = capacidad * 2;

    NodoAdyacencia** nuevaAdyacencia = new NodoAdyacencia*[nuevaCapacidad];
    Estacion** nuevasEstaciones = new Estacion*[nuevaCapacidad];

    for (int i = 0; i < nuevaCapacidad; i++)
    {
        nuevaAdyacencia[i] = 0;
        nuevasEstaciones[i] = 0;
    }
    for (int i = 0; i < cantidadVertices; i++)
    {
        nuevaAdyacencia[i] = adyacencia[i];
        nuevasEstaciones[i] = estaciones[i];
    }

    delete[] adyacencia;
    delete[] estaciones;

    adyacencia = nuevaAdyacencia;
    estaciones = nuevasEstaciones;
    capacidad = nuevaCapacidad;
}

int Grafo::agregarVertice(Estacion* estacion)
{
    if (cantidadVertices == capacidad)
    {
        redimensionar();
    }

    adyacencia[cantidadVertices] = 0;
    estaciones[cantidadVertices] = estacion;
    cantidadVertices++;

    return cantidadVertices - 1;
}

void Grafo::agregarAdyacente(int origen, int destino)
{
    NodoAdyacencia* nuevo = new NodoAdyacencia;
    nuevo->vertice = destino;
    nuevo->siguiente = adyacencia[origen];
    adyacencia[origen] = nuevo;
}

void Grafo::agregarArista(int origen, int destino)
{
    if (origen < 0 || destino < 0 || origen >= cantidadVertices || destino >= cantidadVertices)
    {
        return;
    }
    if (origen == destino)
    {
        return;   // no se admiten lazos en la red de ciclovias
    }

    // se controla que la arista no exista ya para no duplicarla
    NodoAdyacencia* aux = adyacencia[origen];
    while (aux != 0)
    {
        if (aux->vertice == destino)
        {
            return;
        }
        aux = aux->siguiente;
    }

    agregarAdyacente(origen, destino);
    agregarAdyacente(destino, origen);
    cantidadAristas++;
}

void Grafo::eliminarVertice(int vertice)
{
    if (vertice < 0 || vertice >= cantidadVertices)
    {
        return;
    }

    // se libera la lista de adyacencia del vertice que se elimina
    NodoAdyacencia* aux = adyacencia[vertice];
    while (aux != 0)
    {
        NodoAdyacencia* borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    adyacencia[vertice] = 0;
    estaciones[vertice] = 0;

    // se quitan las aristas que apuntaban al vertice en las otras listas
    for (int i = 0; i < cantidadVertices; i++)
    {
        NodoAdyacencia* actual = adyacencia[i];
        NodoAdyacencia* anterior = 0;

        while (actual != 0)
        {
            if (actual->vertice == vertice)
            {
                NodoAdyacencia* borrar = actual;
                if (anterior == 0)
                {
                    adyacencia[i] = actual->siguiente;
                    actual = adyacencia[i];
                }
                else
                {
                    anterior->siguiente = actual->siguiente;
                    actual = anterior->siguiente;
                }
                delete borrar;
                cantidadAristas--;
            }
            else
            {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
    }
}

int Grafo::buscarVertice(const string& codigoEstacion) const
{
    for (int i = 0; i < cantidadVertices; i++)
    {
        if (estaciones[i] != 0 && estaciones[i]->obtenerCodigo() == codigoEstacion)
        {
            return i;
        }
    }
    return -1;
}

int Grafo::obtenerCantidadVertices() const
{
    return cantidadVertices;
}

int Grafo::obtenerCantidadAristas() const
{
    return cantidadAristas;
}

Estacion* Grafo::obtenerEstacion(int vertice) const
{
    if (vertice < 0 || vertice >= cantidadVertices)
    {
        return 0;
    }
    return estaciones[vertice];
}

int Grafo::obtenerGrado(int vertice) const
{
    if (vertice < 0 || vertice >= cantidadVertices)
    {
        return 0;
    }

    int grado = 0;
    NodoAdyacencia* aux = adyacencia[vertice];
    while (aux != 0)
    {
        grado++;
        aux = aux->siguiente;
    }
    return grado;
}

bool Grafo::caminoMinimo(int origen, int destino, Estacion** camino, int& tramos) const
{
    tramos = 0;
    if (origen < 0 || destino < 0 || origen >= cantidadVertices || destino >= cantidadVertices)
    {
        return false;
    }
    if (estaciones[origen] == 0 || estaciones[destino] == 0)
    {
        return false;   // el vertice fue eliminado del grafo
    }

    bool* visitado = new bool[cantidadVertices];
    int* padre = new int[cantidadVertices];
    for (int i = 0; i < cantidadVertices; i++)
    {
        visitado[i] = false;
        padre[i] = -1;
    }

    // recorrido en anchura (BFS): explora por niveles, por lo que la primera
    // vez que llega al destino lo hace con la menor cantidad de aristas
    Cola cola;
    visitado[origen] = true;
    cola.acolar(origen);

    while (!cola.estaVacia())
    {
        int actual = cola.desacolar();
        if (actual == destino)
        {
            break;
        }

        NodoAdyacencia* aux = adyacencia[actual];
        while (aux != 0)
        {
            if (estaciones[aux->vertice] != 0 && !visitado[aux->vertice])
            {
                visitado[aux->vertice] = true;
                padre[aux->vertice] = actual;
                cola.acolar(aux->vertice);
            }
            aux = aux->siguiente;
        }
    }

    bool hayCamino = visitado[destino];
    if (hayCamino)
    {
        // se reconstruye el camino desde el destino hasta el origen
        int longitud = 0;
        int actual = destino;
        while (actual != -1)
        {
            longitud++;
            actual = padre[actual];
        }

        int posicion = longitud - 1;
        actual = destino;
        while (actual != -1)
        {
            camino[posicion] = estaciones[actual];
            posicion--;
            actual = padre[actual];
        }

        tramos = longitud - 1;   // cantidad de aristas del camino
    }

    delete[] visitado;
    delete[] padre;

    return hayCamino;
}

void Grafo::mostrar() const
{
    cout << "  Grafo de ciclovias: " << cantidadVertices << " vertices y "
         << cantidadAristas << " aristas" << endl;

    for (int i = 0; i < cantidadVertices; i++)
    {
        if (estaciones[i] == 0)
        {
            continue;   // el vertice fue eliminado del grafo
        }

        cout << "   " << estaciones[i]->obtenerCodigo() << " (grado " << obtenerGrado(i) << "):";
        NodoAdyacencia* aux = adyacencia[i];
        while (aux != 0)
        {
            cout << " " << estaciones[aux->vertice]->obtenerCodigo();
            aux = aux->siguiente;
        }
        cout << endl;
    }
}
