
#include "../include/reserva.h"

struct rep_reserva
{
  TSocio socio;
  TLibro libro;
};

TReserva crearTReserva(TSocio socio, TLibro libro)
{
  TReserva nueva_res = new rep_reserva;
  nueva_res->libro = libro;
  nueva_res->socio = socio;

  return nueva_res;
}

void imprimirTReserva(TReserva reserva)
{
  printf("Reserva de libro %s por %s %s.\n",
         tituloTLibro(reserva->libro),
         nombreTSocio(reserva->socio),
         apellidoTSocio(reserva->socio));
}

void liberarTReserva(TReserva &reserva)
{
  if (reserva != NULL)
  {
    liberarTLibro(reserva->libro);
    liberarTSocio(reserva->socio);
  }
  delete reserva;
  reserva = NULL;
}

TSocio socioTReserva(TReserva reserva)
{
  return reserva->socio;
}

TLibro libroTReserva(TReserva reserva)
{
  return reserva->libro;
}

TReserva copiarTReserva(TReserva reserva)
{
  TReserva copia_res = new rep_reserva;
  copia_res->libro = copiarTLibro(reserva->libro);
  copia_res->socio = copiarTSocio(reserva->socio);

  return copia_res;
}

void liberarTReservaSoloEstructura(TReserva &reserva)
{
  if (reserva != NULL)
  {
    reserva->socio = NULL;
    reserva->libro = NULL;

    delete reserva;
    reserva = NULL;
  }
}
