#include "../include/tablaReserva.h"

// Se debe implementar mediante una tabla de dispersión abierta (hash)

struct rep_tablaTablaReserva {
    int max;
    int N;
    TReserva *reservas;
};


TTablaReserva crearTTablaReserva(int max, int N){
    //  Función para crear una nueva Tabla vacía,
//  en la que se estima que se insertarán max entradas.
//  La función es O(max) peor caso.
    TTablaReserva nuevaTabla = new rep_tablaTablaReserva;
    nuevaTabla->max = max;
    nuevaTabla->N = N;
    nuevaTabla->reservas = new TReserva[max];
    return nuevaTabla;
}


void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva){
//  Función para insertar una asociación (isbn, reserva) en la tabla de reservas.
//  La función asocia el isbn de un libro con su reserva.
//  PRE: !perteneceTTablaReserva(tabla, reserva)
//  La funcion es O(N + l) peor caso, siendo:
//    N: el parametro N usado al crear la tabla
//    l: la cantidad de libros para los cuales hay reservas en la tabla

}


bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro) {
    //  Función para verificar si en una TTablaReserva "tabla"
//  existe una asociación que representa la reserva del libro con el isbn dado.
//  Devuelve true si existe, false en caso contrario.
//  La funcion es O(N + l) peor caso, siendo:
//    N: el parametro N usado al crear la tabla
//    l: la cantidad de libros para los cuales hay reservas en la tabla
    return false;
}


TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn){
   //  Función para obtener toda la cola de reservas del libro asociado
//  al isbn dado.
//  PRE: perteneceTTablaReserva(tabla, isbn)
//  La función es O(1) promedio.
    return NULL;
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn){
    // Funcion que devuelve la primer reserva de la cola de reservas del libro con isbn dado.
// Pre: perteneceTTablaReserva(tabla, isbn)
// La función es O(1) promedio.
    return NULL;
}

void liberarTTablaReserva(TTablaReserva &tabla){
//  Función para liberar la memoria asignada a una TTablaReserva.
//  La función es O(n + max) peor caso, donde n es la cantidad actual de reservas en la tabla
//  y max la cantidad esperada de reservas en la tabla.
    for (int i = 0; i < tabla->N; i++) {
        liberarTReserva(tabla->reservas[i]);
    }
    delete[] tabla->reservas;
    delete tabla;
    tabla = NULL;
}
