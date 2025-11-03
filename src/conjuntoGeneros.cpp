#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros
{
  int *ids;
  int cardinal;
  int capacidad;
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax)
{
  TConjuntoGeneros nuevo = new rep_conjuntogeneros;
  nuevo->ids = new int[cantMax];

  for (int i = 0; i < cantMax; i++)
  {
    nuevo->ids[i] = 0;
  }

  nuevo->cardinal = 0;
  nuevo->capacidad = cantMax;
  return nuevo;
}

bool esVacioTConjuntoGeneros(TConjuntoGeneros c)
{
  return c->cardinal == 0;
}

void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id)
{
  if (id >= 0 && id < c->capacidad)
  {
    if (c->ids[id] == 0)
    {
      c->ids[id] = 1;
      c->cardinal++;
    }
  }
}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id)
{
  if(id >= 0 && id < c->capacidad)
  {
    if(c->ids[id] == 1)
    {
      c->ids[id] = 0;
      c->cardinal--;
    }
  }
}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id)
{
  if (id >= 0 && id < c->capacidad)
  {
    return c->ids[id] == 1;
  }
  return false;
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c)
{
  return c->cardinal;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c)
{
  return c->capacidad;
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c)
{
  bool primer_elemento = true; // Flag para el primer elemento

  for (int i = 0; i < c->capacidad; i++) // Respeta el O(n) siendo n la cantMax
  {
    if (c->ids[i] == 1) // Si el id pertenece al conjunto
    {
      if (!primer_elemento) // Si no es el primer elemento
      {                     // Imprime espacio antes del elemento
        printf(" ");
      }
      printf("%d", i); // Imprime el id
      primer_elemento = false;
    }
  }
  printf("\n");
}

void liberarTConjuntoGeneros(TConjuntoGeneros &c)
{
  delete[] c->ids;
  delete c;
  c = NULL;
}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2)
{
  int cantMax = c1->capacidad;
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->capacidad);

  for (int i = 0; i < cantMax; i++)
  {
    if (c1->ids[i] == 1 || c2->ids[i] == 1)
    {
      res->ids[i] = 1;
      res->cardinal++;
    }
  }
  return res;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2)
{
  int cantMax = c1->capacidad;
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->capacidad);

  for (int i = 0; i < cantMax; i++)
  {
    if(c1->ids[i] == 1 && c2->ids[i] == 1)
    {
      res->ids[i] = 1;
      res->cardinal++;
    }
  }
  return res;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2)
{
  int cantMax = c1->capacidad;
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->capacidad);
  
  for (int i = 0; i < cantMax; i++)
  {
    if(c1->ids[i] == 1 && c2->ids[i] == 0)
    {
      res->ids[i] = 1;
      res->cardinal++;
    }
  }
  return res;
}
