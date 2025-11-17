#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.

struct rep_colaDePrioridadReservas
{
    TReserva *elementos;
    nat *prioridades;
    nat cantidad;
    nat capacidad;
    bool menorPrioritario;
};

TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N)
{
    TColaDePrioridadReservas cp = new rep_colaDePrioridadReservas;
    cp->elementos = new TReserva[N + 1]; // 1-indexed
    cp->prioridades = new nat[N + 1];
    cp->cantidad = 0;
    cp->capacidad = N;
    cp->menorPrioritario = true; // por defecto menor rango tiene prioridad
    return cp;
}
// Funciones aux:

static nat padre(nat i)
{
    return i / 2;
}

static nat hijoIzq(nat i)
{
    return 2 * i;
}

static nat hijoDer(nat i)
{
    return 2 * 1 + 1;
}

static bool esMasPrioritario(nat p1, nat p2, bool menorPrioritario)
{
    if (menorPrioritario)
        return p1 < p2;
    else
        return p1 > p2;
}

static void intercambiar(TColaDePrioridadReservas cp, nat i, nat j)
{
    // Intercambiar reservas
    TReserva tempRes = cp->elementos[i];
    cp->elementos[i] = cp->elementos[j];
    cp->elementos[j] = tempRes;

    // Intercambiar prioridades
    nat tempPrio = cp->prioridades[i];
    cp->prioridades[i] = cp->prioridades[j];
    cp->prioridades[j] = tempPrio;
}

static void filtradoAsc(TColaDePrioridadReservas cp, nat pos)
{
    if (pos > 1)
    {
        nat p = padre(pos);
        // Si el elemento actual es MÁS prioritario que su padre
        if (esMasPrioritario(cp->prioridades[pos], cp->prioridades[p], cp->menorPrioritario))
        {
            intercambiar(cp, pos, p);
            filtradoAsc(cp, p); // Recursión para continuar subiendo
        }
    }
}

static void filtradoDes(TColaDePrioridadReservas cp, nat pos)
{
    nat izq = hijoIzq(pos);

    // Verificar si tiene al menos un hijo izquierdo
    if (izq <= cp->cantidad)
    { // Tiene al menos hijo izquierdo
        nat der = hijoDer(pos);
        nat hijoMasPrioritario = izq; // Por defecto, elegir izquierdo

        // Encontrar el hijo más prioritario
        // Si existe hijo derecho Y es más prioritario que el izquierdo
        if (der <= cp->cantidad)
        {
            if (esMasPrioritario(cp->prioridades[der], cp->prioridades[izq], cp->menorPrioritario))
            {
                hijoMasPrioritario = der;
            }
        }
        // Nota: en caso de empate, se queda con el izquierdo (según especificación)

        // Si el hijo más prioritario es efectivamente más prioritario que el actual
        if (esMasPrioritario(cp->prioridades[hijoMasPrioritario], cp->prioridades[pos], cp->menorPrioritario))
        {
            intercambiar(cp, pos, hijoMasPrioritario);
            filtradoDes(cp, hijoMasPrioritario); // Recursión para continuar bajando
        }
        // Si el hijo no es más prioritario, la función termina automáticamente (sin break)
    }
}

void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp)
{
    cp->menorPrioritario = !cp->menorPrioritario;

    int i = cp->cantidad / 2;
    while (i >= 1)
    {
        filtradoDes(cp, i);
        i--;
    }
}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp)
{
    if(cp != NULL)
    {
        nat i = 1;
        while (i <= cp->cantidad)
        {
            liberarTReserva(cp->elementos[i]);
            i++;
        }
        delete[] cp->elementos;
        delete[] cp->prioridades;
        delete cp;
        cp = NULL;
    }
}

void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva)
{
    cp->cantidad++;
    cp->elementos[cp->cantidad] = reserva;
    cp->prioridades[cp->cantidad] = rangoTSocio(socioTReserva(reserva));
    filtradoAsc(cp, cp->cantidad);
}

bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp)
{
    return cp->cantidad == 0;
}

TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp)
{
    return cp->elementos[1];
}

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp)
{
    
}

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro)
{
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro)
{
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp)
{
    return NULL;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp)
{
}
