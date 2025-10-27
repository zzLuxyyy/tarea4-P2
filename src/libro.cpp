#include "../include/libro.h"

struct rep_libro {
};

TLibro crearTLibro(int isbn, const char titulo[MAX_TITULO], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], const char descripcion[MAX_DESCRIPCION], int idGeneroLibro, TFecha fechaEdicion){
    return NULL;
}

void liberarTLibro(TLibro &l){
}

int isbnTLibro(TLibro l){
    return 0;
}

char* tituloTLibro(TLibro l){
    return NULL;
}
 
char* descripcionTLibro(TLibro l){
    return NULL; 
}

char* nombreAutorTLibro(TLibro l){
    return NULL;
}

char* apellidoAutorTLibro(TLibro l){
    return NULL;
}

int idGeneroTLibro(TLibro l){
    return 0;
}

TFecha fechaEdicionTLibro(TLibro l){
    return NULL;
}

void imprimirTLibro(TLibro l){
}

TLibro copiarTLibro(TLibro l){
    return NULL;
}
