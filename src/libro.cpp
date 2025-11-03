#include "../include/libro.h"

struct rep_libro
{
    int isbn;
    char titulo[MAX_TITULO];
    char nombreAutor[MAX_NOMBRE_AUTOR];
    char apellidoAutor[MAX_APELLIDO_AUTOR];
    char descripcion[MAX_DESCRIPCION];
    int idGeneroLibro;
    TFecha fechaEdicion;
};

TLibro crearTLibro(int isbn, const char titulo[MAX_TITULO], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], const char descripcion[MAX_DESCRIPCION], int idGeneroLibro, TFecha fechaEdicion)
{
    TLibro nuevoLibro = new rep_libro;

    nuevoLibro->isbn = isbn; // Cambie nuevo->isb = isbn; porque daba error.
    strcpy(nuevoLibro->titulo, titulo);
    strcpy(nuevoLibro->nombreAutor, nombreAutor);
    strcpy(nuevoLibro->apellidoAutor, apellidoAutor);
    strcpy(nuevoLibro->descripcion, descripcion);
    nuevoLibro->idGeneroLibro = idGeneroLibro;
    nuevoLibro->fechaEdicion = fechaEdicion; // es un puntero, entonces al asigno directamente
    //^ Cambie 'nuevo->' por nuevoLibro ya que la variable 'nuevo' no existe.
    return nuevoLibro;
}

void liberarTLibro(TLibro &l)
{
     if (l != NULL) {
        liberarTFecha(l->fechaEdicion); // Liberar la fecha
        delete l;
        l = NULL;
    }
}

int isbnTLibro(TLibro l)
{
    return l->isbn;
}

char *tituloTLibro(TLibro l)
{
    return l->titulo;
}

char *descripcionTLibro(TLibro l)
{
    return l->descripcion;
}

char *nombreAutorTLibro(TLibro l)
{
    return l->nombreAutor;
}

char *apellidoAutorTLibro(TLibro l)
{
    return l->apellidoAutor;
}

int idGeneroTLibro(TLibro l)
{
    return l->idGeneroLibro;
}

TFecha fechaEdicionTLibro(TLibro l)
{
    return l->fechaEdicion;
}

void imprimirTLibro(TLibro l)
{
    // Usamos %d para el tipo int,
    // y usamos %s para el tipo char.
    printf("Libro %d\n", l->isbn);
    printf("Título: %s\n", l->titulo);
    printf("Autor: %s %s\n", l->nombreAutor, l->apellidoAutor);
    printf("Descripción: %s\n", l->descripcion);
    printf("Género: %d\n", l->idGeneroLibro);
    printf("Fecha de edición: ");
    imprimirTFecha(l->fechaEdicion);
}

TLibro copiarTLibro(TLibro l)
{
    TLibro copia = new rep_libro;

    copia->isbn = l->isbn;
    strcpy(copia->titulo, l->titulo);
    strcpy(copia->nombreAutor, l->nombreAutor);
    strcpy(copia->apellidoAutor, l->apellidoAutor);
    strcpy(copia->descripcion, l->descripcion);
    copia->idGeneroLibro = l->idGeneroLibro;             // correccion en estos dos, llevan '=' no ',' da error si no los asignas
    copia->fechaEdicion = copiarTFecha(l->fechaEdicion); // Llama a la función copiarTFecha.

    return copia;
}
