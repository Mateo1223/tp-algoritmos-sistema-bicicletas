#include "Ordenamiento.h"

bool Ordenamiento::debeIrAntes(Estacion* primera, Estacion* segunda, int criterio)
{
    if (criterio == 2)
    {
        return (primera->obtenerBicisDisponibles() > segunda->obtenerBicisDisponibles());
    }
    return (primera->obtenerCapacidadAnclajes() > segunda->obtenerCapacidadAnclajes());
}

void Ordenamiento::burbujeo(Estacion** arreglo, int cantidad, int criterio)
{
    for (int i = 0; i < cantidad - 1; i++)
    {
        for (int j = 0; j < cantidad - 1 - i; j++)
        {
            if (!debeIrAntes(arreglo[j], arreglo[j + 1], criterio))
            {
                Estacion* auxiliar = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = auxiliar;
            }
        }
    }
}

void Ordenamiento::seleccion(Estacion** arreglo, int cantidad, int criterio)
{
    for (int i = 0; i < cantidad - 1; i++)
    {
        int posicionMenor = i;
        for (int j = i + 1; j < cantidad; j++)
        {
            if (debeIrAntes(arreglo[j], arreglo[posicionMenor], criterio))
            {
                posicionMenor = j;
            }
        }
        if (posicionMenor != i)
        {
            Estacion* auxiliar = arreglo[i];
            arreglo[i] = arreglo[posicionMenor];
            arreglo[posicionMenor] = auxiliar;
        }
    }
}

void Ordenamiento::insercion(Estacion** arreglo, int cantidad, int criterio)
{
    for (int i = 1; i < cantidad; i++)
    {
        Estacion* actual = arreglo[i];
        int j = i - 1;

        while (j >= 0 && !debeIrAntes(arreglo[j], actual, criterio))
        {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = actual;
    }
}
