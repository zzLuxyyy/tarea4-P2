#include "../include/prestamo.h"

struct rep_prestamo
{
  TSocio socio;
  TLibro libro;
  TFecha fechaDevolucion;
  TFecha fechaRetiro;
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro)
{
  TPrestamo nuevoprestamo = new rep_prestamo;
  nuevoprestamo->socio = socio;
  nuevoprestamo->libro = libro;
  nuevoprestamo->fechaRetiro = fechaRetiro;
  nuevoprestamo->fechaDevolucion = NULL;

  return nuevoprestamo;
}

void imprimirTPrestamo(TPrestamo prestamo)
{
  printf("Préstamo de libro %s a %s %s.\n",
         tituloTLibro(prestamo->libro),
         nombreTSocio(prestamo->socio),
         apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);

  if (fueRetornadoTPrestamo(prestamo))
  {
    imprimirTFecha(prestamo->fechaDevolucion);
  }
  else
  {
    printf("No retornado\n");
  }
}

void liberarTPrestamo(TPrestamo &prestamo)
{
  if (prestamo != NULL)
  {
    liberarTSocio(prestamo->socio);
    liberarTLibro(prestamo->libro);
    liberarTFecha(prestamo->fechaRetiro);
    if (prestamo->fechaDevolucion != NULL)
    {
      liberarTFecha(prestamo->fechaDevolucion);
    }
    delete prestamo;
    prestamo = NULL;
  }
}

TSocio socioTPrestamo(TPrestamo prestamo)
{
  return prestamo->socio;
}

TFecha fechaRetiroTPrestamo(TPrestamo prestamo)
{
  return prestamo->fechaRetiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo)
{
  return prestamo->fechaDevolucion;
}

TLibro libroTPrestamo(TPrestamo prestamo)
{
  return prestamo->libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo)
{
  return prestamo->fechaDevolucion != NULL;
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion)
{
  if (fueRetornadoTPrestamo(prestamo))
  {
    liberarTFecha(prestamo->fechaDevolucion);
  }
  prestamo->fechaDevolucion = fechaDevolucion;
  // liberarTFecha(fechaDevolucion); // No liberar aquí, responsabilidad del llamador
}

TPrestamo copiarTPrestamo(TPrestamo prestamo)
{
  TPrestamo copia = new rep_prestamo;

  copia->socio = copiarTSocio(prestamo->socio);
  copia->libro = copiarTLibro(prestamo->libro);
  copia->fechaRetiro = copiarTFecha(prestamo->fechaRetiro);

  if (fueRetornadoTPrestamo(prestamo))
  {
    copia->fechaDevolucion = copiarTFecha(prestamo->fechaDevolucion);
  }
  else
  {
    copia->fechaDevolucion = NULL;
  }
  return copia;
}

void liberarTPrestamoSoloEstructura(TPrestamo &prestamo)
{
  if (prestamo == NULL)
  {
    return;
  }

  if (prestamo->fechaRetiro != NULL)
  {
    liberarTFecha(prestamo->fechaRetiro);
    prestamo->fechaRetiro = NULL;
  }

  if (prestamo->fechaDevolucion != NULL)
  {
    liberarTFecha(prestamo->fechaDevolucion);
    prestamo->fechaDevolucion = NULL;
  }

  prestamo->socio = NULL;
  prestamo->libro = NULL;

  delete prestamo;
  prestamo = NULL;
}