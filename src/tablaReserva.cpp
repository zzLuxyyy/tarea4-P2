#include "../include/tablaReserva.h"
#include <cstdlib>

struct Entrada
{
    /* Nodo de la lista enlazada */
    int isbn;
    TColaDePrioridadReservas colaPrioridad;
    Entrada *siguiente;
};

struct rep_tablaTablaReserva
{
    /* Estructura de la tabla hash */
    Entrada **tabla; // Arreglo de punteros
    int max;         // Tamaño de la tabla
    int N;           // Capacidad máxima de la cola
    int cantLibros;  // Cantidad de libros dif
};

static int hash(int isbn, int max)
{
    /* Función hash O(1)*/
    return abs(isbn) % max;
}

TTablaReserva crearTTablaReserva(int max, int N)
{
    /* Crea una tabla vacía */
    TTablaReserva nuevaTabla = new rep_tablaTablaReserva;
    nuevaTabla->max = max;
    nuevaTabla->N = N;
    nuevaTabla->cantLibros = 0;
    nuevaTabla->tabla = new Entrada *[max]; // Arreglo de punteros a listas

    for (int i = 0; i < max; i++)
    {
        nuevaTabla->tabla[i] = NULL; // Iniciar las posiciones en NULL
    }

    return nuevaTabla;
}

void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva)
{
    int indice = hash(isbn, tabla->max);
    Entrada* actual = tabla->tabla[indice];

    while (actual != NULL)
    {
        if (actual->isbn == isbn)
        {
            insertarTColaDePrioridadReservas(actual->colaPrioridad, reserva);
            return;
        }
        actual = actual->siguiente;
    }

    Entrada* nueva = new Entrada;
    nueva->isbn = isbn;
    nueva->colaPrioridad = crearTColaDePrioridadReservas(tabla->N);
    insertarTColaDePrioridadReservas(nueva->colaPrioridad, reserva);

    nueva->siguiente = tabla->tabla[indice];
    tabla->tabla[indice] = nueva;
    tabla->cantLibros++;
}

bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro)
{
    /* Verifica si existr una reserva en la tabla */
    int indice = hash(isbnLibro, tabla->max);
    Entrada *actual = tabla->tabla[indice];

    // Busca la entrada con el isbn del libro
    while (actual != NULL)
    {
        if (actual->isbn == isbnLibro)
        {
            // Cuando lo encuentra, verifica su cola de prioridad
            return estaTColaDePrioridadReservas(actual->colaPrioridad, ciSocio, isbnLibro);
        }
        actual = actual->siguiente;
    }

    return false; // No encontró el libro
}

TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn)
{
   int indice = hash(isbn, tabla->max);
   Entrada* actual = tabla->tabla[indice];

   while(actual != NULL)
   {
        if (actual->isbn == isbn)
        {
            return actual->colaPrioridad;
        }
        actual = actual->siguiente;
   }    
    return NULL;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn)
{
    /* Obtiene la siguiente reserva segun prioridad */
    TColaDePrioridadReservas cola = obtenerReservaTTablaReserva(tabla, isbn);
    if (cola != NULL && !estaVaciaTColaDePrioridadReservas(cola))
    {
        return prioritarioTColaDePrioridadReservas(cola);
    }
    return NULL;
}

void liberarTTablaReserva(TTablaReserva &tabla)
{
    /* Libera toda la memoria de la tabla */
    if (tabla == NULL)
        return;

    // Recorre la lista
    for (int i = 0; i < tabla->max; i++)
    {
        Entrada *actual = tabla->tabla[i];
        while (actual != NULL)
        {
            Entrada *aBorrar = actual;
            actual = actual->siguiente;

            // Libera la cola de prioridad
            liberarTColaDePrioridadReservas(aBorrar->colaPrioridad);
            delete aBorrar; // Libera la entrada
        }
    }

    delete[] tabla->tabla; // Libera el array
    delete tabla;          // Libera la estructura
    tabla = NULL;
}
