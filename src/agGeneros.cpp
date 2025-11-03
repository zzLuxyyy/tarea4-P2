#include "../include/agGeneros.h"
#include <assert.h>
#include <string.h>

struct rep_agGeneros
{
  int idGenero;
  rep_agGeneros *pH;
  rep_agGeneros *sH;
  char nombreGenero[MAX_NOMBRE];
};

TAGGeneros crearTAGGeneros()
{
  TAGGeneros nuevo = new rep_agGeneros;
  nuevo->idGenero = 0;
  nuevo->pH = NULL;
  nuevo->sH = NULL;
  nuevo->nombreGenero[0] = '\0';
  return nuevo;
}

TAGGeneros buscarNodo(TAGGeneros nodo, int id)
{
  if (nodo == NULL || nodo->idGenero == 0)
  {
    return NULL;
  }

  if (nodo->idGenero == id)
  {
    return nodo;
  }

  TAGGeneros encontrado = buscarNodo(nodo->pH, id);
  if (encontrado != NULL)
  {
    return encontrado;
  }
  return buscarNodo(nodo->sH, id);
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE])
{
  TAGGeneros nuevoGenero = new rep_agGeneros;
  nuevoGenero->idGenero = idGenero;
  nuevoGenero->pH = NULL;
  nuevoGenero->sH = NULL;
  strcpy(nuevoGenero->nombreGenero, nombreGenero);

  if (idGeneroPadre == -1)
  {
    arbolGeneros->idGenero = idGenero;
    strcpy(arbolGeneros->nombreGenero, nombreGenero);
    delete nuevoGenero;
    return;
  }

  TAGGeneros padre = buscarNodo(arbolGeneros, idGeneroPadre);

  if (padre != NULL)
  {

    nuevoGenero->sH = padre->pH;
    padre->pH = nuevoGenero;
  }
}

void imprimirTAGGenerosAux(TAGGeneros nodo, int nivel)
{
  if (nodo == NULL || nodo->idGenero == 0)
  {
    return;
  }

  // Imprimir espacios
  for (int i = 0; i < nivel; i++)
  {
    printf("    ");
  }

  // Imprimir el nodo actual
  printf("%d - %s\n", nodo->idGenero, nodo->nombreGenero);

  imprimirTAGGenerosAux(nodo->pH, nivel + 1);

  imprimirTAGGenerosAux(nodo->sH, nivel);
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros)
{
  printf("Árbol de géneros:\n");
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return;
  }
  imprimirTAGGenerosAux(arbolGeneros, 0);
}

void liberarTAGGeneros(TAGGeneros &arbolGeneros)
{
  if (arbolGeneros != NULL)
  {
    liberarTAGGeneros(arbolGeneros->pH);
    liberarTAGGeneros(arbolGeneros->sH);
    delete arbolGeneros;
    arbolGeneros = NULL;
  }
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return false;
  }

  if (idGenero == arbolGeneros->idGenero)
  {
    return true;
  }

  if (existeGeneroTAGGeneros(arbolGeneros->pH, idGenero))
  {
    return true;
  }

  return existeGeneroTAGGeneros(arbolGeneros->sH, idGenero);
}

char *nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return NULL;
  }

  if (idGenero == arbolGeneros->idGenero)
  {
    return arbolGeneros->nombreGenero;
  }

  char *res = nombreGeneroTAGGeneros(arbolGeneros->pH, idGenero);
  if (res != NULL)
  {
    return res;
  }

  return nombreGeneroTAGGeneros(arbolGeneros->sH, idGenero);
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return 0;
  }

  nat alturaConHijos = 1 + alturaTAGGeneros(arbolGeneros->pH);
  nat alturaHermanos = alturaTAGGeneros(arbolGeneros->sH);
  return alturaConHijos > alturaHermanos ? alturaConHijos : alturaHermanos;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return 0;
  }

  return 1 + cantidadTAGGeneros(arbolGeneros->pH) + cantidadTAGGeneros(arbolGeneros->sH);
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return;
  }

  if (arbolGeneros->idGenero == idGenero)
  {
    liberarTAGGeneros(arbolGeneros->pH);
    arbolGeneros->idGenero = 0;
    arbolGeneros->pH = NULL;
    strcpy(arbolGeneros->nombreGenero, "");
    return;
  }

  // Buscar en los hijos
  if (arbolGeneros->pH != NULL)
  {
    if (arbolGeneros->pH->idGenero == idGenero)
    {
      TAGGeneros aRemover = arbolGeneros->pH;
      arbolGeneros->pH = aRemover->sH;
      aRemover->sH = NULL;
      liberarTAGGeneros(aRemover);
      return;
    }
    else
    {
      removerGeneroTAGGeneros(arbolGeneros->pH, idGenero);
    }
  }

  if (arbolGeneros->sH != NULL)
  {
    if (arbolGeneros->sH->idGenero == idGenero)
    {
      TAGGeneros aRemover = arbolGeneros->sH;
      arbolGeneros->sH = aRemover->sH;
      aRemover->sH = NULL;
      liberarTAGGeneros(aRemover);
      return;
    }
    else
    {
      removerGeneroTAGGeneros(arbolGeneros->sH, idGenero);
    }
  }
}

TAGGeneros copiarSubarbol(TAGGeneros nodo)
{
  if (nodo == NULL || nodo->idGenero == 0)
  {
    return NULL;
  }

  TAGGeneros copia = new rep_agGeneros;
  copia->idGenero = nodo->idGenero;
  strcpy(copia->nombreGenero, nodo->nombreGenero);
  copia->pH = copiarSubarbol(nodo->pH);
  copia->sH = copiarSubarbol(nodo->sH);

  return copia;
}

TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero)
{
  TAGGeneros nodo = buscarNodo(arbolGeneros, idGenero);
  return nodo;  
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros)
{
  if (arbolGeneros == NULL || arbolGeneros->idGenero == 0)
  {
    return -1;
  }

  int maxActual = arbolGeneros->idGenero;
  int maxHijos = obtenerMaxTAGGeneros(arbolGeneros->pH);
  int maxHermanos = obtenerMaxTAGGeneros(arbolGeneros->sH);

  if (maxHijos > maxActual)
  {
    maxActual = maxHijos;
  }

  if (maxHermanos > maxActual)
  {
    maxActual = maxHermanos;
  }

  return maxActual;
}

void llenarConjunto(TAGGeneros nodo, TConjuntoGeneros &conjunto)
{
  if (nodo == NULL || nodo->idGenero == 0)
  {
    return;
  }

  insertarTConjuntoGeneros(conjunto, nodo->idGenero);
  llenarConjunto(nodo->pH, conjunto);
  llenarConjunto(nodo->sH, conjunto);
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero)
{
  TAGGeneros nodo = buscarNodo(arbolGeneros, idGenero);
  if (nodo == NULL)
  {
    return crearTConjuntoGeneros(1);
  }

  int maxId = obtenerMaxTAGGeneros(arbolGeneros);
  TConjuntoGeneros conjunto = crearTConjuntoGeneros(maxId + 1);

  insertarTConjuntoGeneros(conjunto, nodo->idGenero);
  llenarConjunto(nodo->pH, conjunto);

  return conjunto;
}