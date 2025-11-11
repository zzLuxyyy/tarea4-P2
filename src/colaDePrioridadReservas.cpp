#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.

struct rep_colaDePrioridadReservas {
    TReserva* elementos;
    nat* prioridades;
    nat cantidad;
    nat capacidad;
    bool menorPrioritario;
};

TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    TColaDePrioridadReservas cp = new rep_colaDePrioridadReservas;
    cp->elementos = new TReserva[N + 1]; // 1-indexed
    cp->prioridades = new nat[N + 1];
    cp->cantidad = 0;
    cp->capacidad = N;
    cp->menorPrioritario = true; // por defecto menor rango tiene prioridad
    return cp;
}

void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {

}

bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return false;
}

TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {

}
