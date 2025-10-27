#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
};

TBiblioteca crearTBiblioteca(){
  return NULL;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
}


bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro){
    return false;
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
}

void imprimirSociosTBiblioteca(TBiblioteca biblioteca){
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
}

void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]) {
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
  return NULL;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
}
