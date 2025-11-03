#include "../include/colaReservas.h"

struct rep_nodo_reserva
{
  TReserva reserva;
  rep_nodo_reserva *siguiente;
};
typedef rep_nodo_reserva *TNodoReserva;

struct rep_colaReservas
{
  nat cardinal;
  TNodoReserva primero;
  TNodoReserva ultimo;
};

TColaReservas crearTColaReservas()
{
  TColaReservas q = new rep_colaReservas;
  q->primero = NULL;
  q->ultimo = NULL;
  q->cardinal = 0;
  return q;
}

void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva)
{
  TNodoReserva nuevo = new rep_nodo_reserva;
  nuevo->reserva = reserva;
  nuevo->siguiente = NULL; // El nodo nuevo es el ultimo.

  if (colaReservas->primero == NULL) // Cola vacía en la que primero
                                     // y utlimo apuntan a nuevo.
  {
    colaReservas->primero = nuevo;
    colaReservas->ultimo = nuevo;
  }
  else
  { // Como la cola es no nula,
    colaReservas->ultimo->siguiente = nuevo;
    colaReservas->ultimo = nuevo; // nuevo ahora es el ultimo.
  }
  colaReservas->cardinal++;
}

void desencolarTColaReservas(TColaReservas &colaReservas)
{
  TNodoReserva aBorrar = colaReservas->primero;
  liberarTReserva(aBorrar->reserva);                        // Reserva del nodo liberada.
  colaReservas->primero = colaReservas->primero->siguiente; // Mueve el puntero al siguiente

  // Si la cola queda vacia, ultimo debe ser NULL.
  if (colaReservas->primero == NULL)
  {
    colaReservas->ultimo = NULL;
  }
  delete aBorrar; // Libera el nodo.
  colaReservas->cardinal--;
}

TReserva frenteTColaReservas(TColaReservas colaReservas)
{
  return colaReservas->primero->reserva;
}

nat cantidadTColaReservas(TColaReservas colaReservas)
{
  return colaReservas->cardinal;
}

void imprimirTColaReservas(TColaReservas colaReservas)
{
  printf("Cola de Reservas:\n");
  TNodoReserva actual = colaReservas->primero;

  while (actual != NULL)
  { // imprimirTReservas imprime la reserva.
    imprimirTReserva(actual->reserva);
    actual = actual->siguiente;
  }
}

void liberarTColaReservas(TColaReservas &colaReservas)
{
  TNodoReserva actual = colaReservas->primero;
  TNodoReserva aBorrar;
  while (actual != NULL)
  {
    aBorrar = actual;
    actual = actual->siguiente;
    liberarTReserva(aBorrar->reserva);
    delete aBorrar;
  }
  delete colaReservas;
  colaReservas = NULL;
}

void liberarTColaReservasSoloEstructura(TColaReservas &colaReservas)
{
  TNodoReserva actual = colaReservas->primero;
  TNodoReserva aBorrar;

  while (actual != NULL)
  {
    aBorrar = actual;
    actual = actual->siguiente; 
    liberarTReservaSoloEstructura(aBorrar->reserva);
    delete aBorrar;
  }

  delete colaReservas;
  colaReservas = NULL;
}

TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas)
{
  TNodoReserva aBorrar = colaReservas->primero;
  TReserva res = aBorrar->reserva;

  // Mueve el puntero primero al siguiente nodo.
  colaReservas->primero = colaReservas->primero->siguiente;

  if (colaReservas->primero == NULL) // Si la cola quedó vacía,
  {                                  // ultimo debe ser NULL.
    colaReservas->ultimo = NULL;
  }

  delete aBorrar;
  colaReservas->cardinal--; // Actualiza el cardinal.

  return res;
}
