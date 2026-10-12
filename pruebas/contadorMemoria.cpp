// Verificador de memoria para el trabajo practico.
//
// Sobrecarga los operadores globales new y delete y lleva un registro de los
// punteros que todavia estan vivos. Al terminar el programa informa cuantos
// bloques quedaron sin liberar (0 = sin fugas) y cuantas dobles liberaciones
// se detectaron (liberar dos veces el mismo puntero).
//
// Este archivo NO forma parte del entregable: se compila aparte, junto con el
// resto de las fuentes, para poder verificar el manejo de memoria dinamica en
// Windows, donde no hay Valgrind.
//
// Nota: el registro se reserva con malloc (no con new) para no llamarse a si
// mismo. Solo se liberan y cuentan los bloques pedidos por el programa; las
// liberaciones de memoria de la biblioteca estandar se ignoran.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <new>

namespace
{
    const long TAMANIO_REGISTRO = 1 << 17;   // 131072 posiciones

    void* const LIBRE = 0;                    // posicion nunca usada
    void* const LIBERADO = (void*)1;          // marca: la posicion tuvo un bloque ya liberado

    void** registro = 0;       // tabla de punteros (direccionamiento abierto)
    long vivos = 0;
    long asignaciones = 0;
    long liberaciones = 0;
    long doblesLiberaciones = 0;

    int posicionDe(void* puntero)
    {
        std::uintptr_t valor = reinterpret_cast<std::uintptr_t>(puntero);
        return (int)((valor >> 4) % (std::uintptr_t)TAMANIO_REGISTRO);
    }

    void registrar(void* puntero)
    {
        if (registro == 0)
        {
            registro = (void**)std::calloc(TAMANIO_REGISTRO, sizeof(void*));
        }
        int posicion = posicionDe(puntero);
        for (int i = 0; i < TAMANIO_REGISTRO; i++)
        {
            int actual = (posicion + i) % TAMANIO_REGISTRO;
            if (registro[actual] == LIBRE || registro[actual] == LIBERADO)
            {
                registro[actual] = puntero;
                vivos++;
                return;
            }
        }
    }

    // Devuelve:
    //   1  -> el puntero estaba vivo (se libera ahora)
    //  -1  -> el puntero ya se habia liberado (DOBLE liberacion)
    //   0  -> el puntero nunca fue registrado (memoria de la biblioteca)
    //
    // Al liberar NO se deja el hueco en LIBRE sino en LIBERADO: asi el sondeo
    // lineal nunca se corta antes de tiempo y un segundo delete se reconoce
    // como doble liberacion en lugar de pasar como "desconocido".
    int desregistrar(void* puntero)
    {
        if (registro == 0)
        {
            return 0;
        }
        int posicion = posicionDe(puntero);
        for (int i = 0; i < TAMANIO_REGISTRO; i++)
        {
            int actual = (posicion + i) % TAMANIO_REGISTRO;
            if (registro[actual] == LIBRE)
            {
                return 0;
            }
            if (registro[actual] == puntero)
            {
                registro[actual] = LIBERADO;
                vivos--;
                return 1;
            }
        }
        return 0;
    }

    struct Informe
    {
        ~Informe()
        {
            std::printf("\n[memoria] new: %ld  delete: %ld  bloques sin liberar: %ld  dobles liberaciones: %ld\n",
                        asignaciones, liberaciones, vivos, doblesLiberaciones);
            if (doblesLiberaciones > 0)
            {
                std::printf("[memoria] ERROR: se detectaron %ld doble(s) liberacion(es)\n",
                            doblesLiberaciones);
            }
            if (vivos == 0)
            {
                std::printf("[memoria] OK: toda la memoria pedida fue liberada\n");
            }
            else
            {
                std::printf("[memoria] ATENCION: quedaron %ld bloques sin liberar\n", vivos);
            }
        }
    };

    Informe informe;
}

void* operator new(std::size_t tamanio)
{
    void* puntero = std::malloc(tamanio);
    if (puntero == 0)
    {
        throw std::bad_alloc();
    }
    asignaciones++;
    registrar(puntero);
    return puntero;
}

void* operator new[](std::size_t tamanio)
{
    return ::operator new(tamanio);
}

void operator delete(void* puntero) noexcept
{
    if (puntero == 0)
    {
        return;
    }
    int resultado = desregistrar(puntero);
    if (resultado == 1)
    {
        liberaciones++;
        std::free(puntero);
    }
    else if (resultado == -1)
    {
        // doble liberacion: se cuenta pero NO se vuelve a liberar, para no
        // abortar el programa y poder informar el problema
        doblesLiberaciones++;
    }
    // resultado == 0: puntero de la biblioteca estandar (no pedido con new)
}

void operator delete[](void* puntero) noexcept
{
    ::operator delete(puntero);
}

void operator delete(void* puntero, std::size_t) noexcept
{
    ::operator delete(puntero);
}

void operator delete[](void* puntero, std::size_t) noexcept
{
    ::operator delete(puntero);
}
