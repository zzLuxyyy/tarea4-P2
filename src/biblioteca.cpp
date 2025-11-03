#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca
{
  TABBLibros libros;       // Árbol ABB de libros de la biblioteca
  TLSESocios socio;        // Lista simplemente enlazada de socios de la biblioteca
  TAGGeneros generos;      // Árbol general de géneros de la biblioteca
  TColaReservas reservas;  // Cola de reservas de la biblioteca
  TLDEPrestamos prestamos; // Lista doblemente enlazada de préstamos de la biblioteca
};

TBiblioteca crearTBiblioteca()
{
  TBiblioteca nueva = new rep_biblioteca;
  nueva->libros = crearTABBLibrosVacio();
  nueva->socio = crearTLSESociosVacia();
  nueva->generos = crearTAGGeneros();
  nueva->reservas = crearTColaReservas();
  nueva->prestamos = crearTLDEPrestamosVacia();

  return nueva;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro)
{
  insertarLibroTABBLibros(biblioteca->libros, libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio)
{
  insertarTLSESocios(biblioteca->socio, socio);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo)
{
  if (biblioteca == NULL)
  {
    return;
  }

  TSocio s1 = obtenerSocioTLSESocios(biblioteca->socio, ciSocio);
  TLibro l1 = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);
  TPrestamo p1 = crearTPrestamo(s1, l1, fechaPrestamo);

  insertarTLDEPrestamos(biblioteca->prestamos, p1);
}

bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro)
{
  if (biblioteca == NULL)
    return false;

  if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro))
  {
    return false;
  }

  nat cantidadPrestamos = cantidadTLDEPrestamos(biblioteca->prestamos);

  for (nat i = 1; i <= cantidadPrestamos; i++)
  {
    TPrestamo presta = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);

    TLibro libro = libroTPrestamo(presta);

    if (isbnTLibro(libro) == isbnLibro && !fueRetornadoTPrestamo(presta))
    {
      return false;
    }
  }

  return true;
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro)
{
  // Verificar que el socio existe
  if (!existeSocioTLSESocios(biblioteca->socio, ciSocio))
  {
    return;  // Socio no existe, no hacer nada
  }
  
  TSocio socio = obtenerSocioTLSESocios(biblioteca->socio, ciSocio);
  
  // Verificar que el libro existe
  if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro))
  {
    return;  // Libro no existe, no hacer nada
  }
  
  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro);

  if (!disponibleLibroTBiblioteca(biblioteca, isbnLibro))
  {
    TReserva reserva = crearTReserva(socio, libro); 
    encolarTColaReservas(biblioteca->reservas, reserva); 
  }
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion)
{
  nat cantidadPrestamos = cantidadTLDEPrestamos(biblioteca->prestamos);

  for (nat i = 1; i <= cantidadPrestamos; i++)
  {
    TPrestamo presta = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, i);

    if (ciTSocio(socioTPrestamo(presta)) == ciSocio &&
        isbnTLibro(libroTPrestamo(presta)) == isbnLibro &&
        compararTFechas(fechaRetiroTPrestamo(presta), fechaPrestamo) == 0)
    {
      actualizarFechaDevolucionTPrestamo(presta, fechaDevolucion);
    }
  }
}

void imprimirSociosTBiblioteca(TBiblioteca biblioteca)
{
  if (biblioteca == NULL)
  {
    return;
  }
  imprimirTLSESocios(biblioteca->socio);
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca)
{
  if (biblioteca == NULL)
  {
    return;
  }
  imprimirTABBLibros(biblioteca->libros);
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca)
{
  if (biblioteca == NULL)
  {
    return;
  }
  imprimirTColaReservas(biblioteca->reservas);
}

void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca)
{
  if (biblioteca == NULL)
  {
    return;
  }
  imprimirTLDEPrestamos(biblioteca->prestamos);
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE])
{
  insertarGeneroTAGGeneros(biblioteca->generos, idGeneroPadre, idGenero, nombreGenero);
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero)
{

  TAGGeneros subArbolGeneros = obtenerSubarbolTAGGeneros(biblioteca->generos, idGenero);

  if (subArbolGeneros == NULL)
  {
    return crearTABBLibrosVacio();
  }
  TABBLibros nuevo = crearTABBLibrosVacio();

  int cantidad = cantidadTABBLibros(biblioteca->libros);

  for (int i = 1; i <= cantidad; i++)
  {
    TLibro libro = obtenerNesimoLibroTABBLibros(biblioteca->libros, i);
    if (libro != NULL)
    {
      int idGeneroLibro = idGeneroTLibro(libro);

      if (existeGeneroTAGGeneros(subArbolGeneros, idGeneroLibro))
      {
        TLibro copia = copiarTLibro(libro);
        insertarLibroTABBLibros(nuevo, copia);
      }
    }
  }
  return nuevo;
}

void liberarTBiblioteca(TBiblioteca &biblioteca)
{
  liberarTLDEPrestamosSoloEstructura(biblioteca->prestamos);
  liberarTColaReservasSoloEstructura(biblioteca->reservas);
  liberarTAGGeneros(biblioteca->generos);
  liberarTABBLibros(biblioteca->libros);
  liberarTLSESocios(biblioteca->socio);
  delete biblioteca;
  biblioteca = NULL;
}
