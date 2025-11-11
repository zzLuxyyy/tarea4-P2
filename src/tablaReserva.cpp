#include "../include/tablaReserva.h"
#include <cstdlib>

// Se debe implementar mediante una tabla de dispersión abierta (hash)
struct Entrada
{
    int isbn;
    TColaDePrioridadReservas colaPrioridad;
    Entrada *siguiente;
};

struct rep_tablaTablaReserva
{
    Entrada **tabla;
    int max;
    int N;
    int cantLibros;
};

static int hash(int isbn, int max)
{
    return abs(isbn) % max;
}

TTablaReserva crearTTablaReserva(int max, int N)
{
    TTablaReserva nuevaTabla = new rep_tablaTablaReserva;
    nuevaTabla->max = max;
    nuevaTabla->N = N;
    nuevaTabla->cantLibros = 0;
    nuevaTabla->tabla = new Entrada *[max];

    for (int i = 0; i < max; i++)
    {
        nuevaTabla->tabla[i] = NULL;
    }

    return nuevaTabla;
}

void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva)
{
    //  Función para insertar una asociación (isbn, reserva) en la tabla de reservas.
    //  La función asocia el isbn de un libro con su reserva.
    //  PRE: !perteneceTTablaReserva(tabla, reserva)
    //  La funcion es O(N + l) peor caso, siendo:
    //    N: el parametro N usado al crear la tabla
    //    l: la cantidad de libros para los cuales hay reservas en la tabla
}

bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro)
{
    int indice = hash(isbnLibro, tabla->max);
    Entrada *actual = tabla->tabla[indice];

    while (actual != NULL)
    {
        if (actual->isbn == isbnLibro)
        {
            return estaTColaDePrioridadReservas(actual->colaPrioridad, ciSocio, isbnLibro);
        }
        actual = actual->siguiente;
    }

    return false;
}

TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn)
{
    //  Función para obtener toda la cola de reservas del libro asociado
    //  al isbn dado.
    //  PRE: perteneceTTablaReserva(tabla, isbn)
    //  La función es O(1) promedio.
    return NULL;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn)
{
    TColaDePrioridadReservas cola = obtenerReservaTTablaReserva(tabla, isbn);
    if (cola != NULL && !estaVaciaTColaDePrioridadReservas(cola))
    {
        return prioritarioTColaDePrioridadReservas(cola);
    }
    return NULL;
}

void liberarTTablaReserva(TTablaReserva &tabla)
{
    if (tabla == NULL)
        return;

    for (int i = 0; i < tabla->max; i++)
    {
        Entrada *actual = tabla->tabla[i];
        while (actual != NULL)
        {
            Entrada *aBorrar = actual;
            actual = actual->siguiente;
            liberarTColaDePrioridadReservas(aBorrar->colaPrioridad);
            delete aBorrar;
        }
    }

    delete[] tabla->tabla;
    delete tabla;
    tabla = NULL;
}
