#include "../include/ldePrestamos.h"

struct nodoDoble
{
    TPrestamo prestamo;
    nodoDoble *sig;
    nodoDoble *ant;
};

struct rep_ldePrestamos
{
    nodoDoble *primero;
    nodoDoble *ultimo;
    nat tope;
};

TLDEPrestamos crearTLDEPrestamosVacia()
{
    TLDEPrestamos nuevoPrestamo = new rep_ldePrestamos;
    nuevoPrestamo->primero = NULL;
    nuevoPrestamo->ultimo = NULL;
    nuevoPrestamo->tope = 0;
    return nuevoPrestamo;
}

void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo)
{
    nodoDoble *nuevo = new nodoDoble;
    nuevo->prestamo = prestamo;
    nuevo->sig = NULL;
    nuevo->ant = NULL;

    if (ldePrestamos->primero == NULL)
    {
        // el nuevo es el primero y el último
        ldePrestamos->primero = nuevo;
        ldePrestamos->ultimo = nuevo;
    }
    else
    {
        TFecha fechaNuevo = fechaRetiroTPrestamo(prestamo);
        nodoDoble *actual = ldePrestamos->primero;

        // buscco lugar donde insertarlo
        while (actual != NULL && compararTFechas(fechaNuevo, fechaRetiroTPrestamo(actual->prestamo)) >= 0)
        {
            actual = actual->sig;
        }

        if (actual == NULL)
        {
            ldePrestamos->ultimo->sig = nuevo;
            nuevo->ant = ldePrestamos->ultimo;
            ldePrestamos->ultimo = nuevo;
        }
        else
        {
            nuevo->sig = actual;
            nuevo->ant = actual->ant;
            if (actual->ant != NULL)
            {
                actual->ant->sig = nuevo;
            }
            else
            {
                ldePrestamos->primero = nuevo;
            }
            actual->ant = nuevo;
        }
    }
    ldePrestamos->tope++;
}

void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos)
{
    nodoDoble *actual = ldePrestamos->primero;
    while (actual != NULL)
    {
        nodoDoble *aBorrar = actual;
        actual = actual->sig;
        liberarTPrestamo(aBorrar->prestamo);
        delete aBorrar;
    }
    delete ldePrestamos;
    ldePrestamos = NULL;
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos)
{
    printf("LDE Préstamos:\n");
    nodoDoble *actual = ldePrestamos->primero;
    while (actual != NULL)
    {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->sig;
    }
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos)
{
    printf("LDE Préstamos:\n");
    nodoDoble *actual = ldePrestamos->ultimo;
    while (actual != NULL)
    {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->ant;
    }
}
nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos)
{
    return ldePrestamos->tope;
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos)
{
    return ldePrestamos->primero->prestamo;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos)
{
    if (ldePrestamos->ultimo == NULL)
        return NULL;
    return ldePrestamos->ultimo->prestamo;
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n)
{
    nodoDoble *actual = ldePrestamos->primero;
    int contador = 1;
    while (contador < n)
    {
        actual = actual->sig;
        contador++;
    }
    return actual->prestamo;
}

TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio)
{
    TLDEPrestamos filtrada = crearTLDEPrestamosVacia();
    nodoDoble *actual = ldePrestamos->primero;
    while (actual != NULL)
    {
        bool cumple = false;
        if (criterio == 0 && fueRetornadoTPrestamo(actual->prestamo))
        {
            cumple = true;
        }
        if (criterio == 1 && !fueRetornadoTPrestamo(actual->prestamo))
        {
            cumple = true;
        }
        if (cumple)
        {
            TPrestamo copia = copiarTPrestamo(actual->prestamo);
            insertarTLDEPrestamos(filtrada, copia);
        }
        actual = actual->sig;
    }
    return filtrada;
}

void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos)
{
    if (ldePrestamos == NULL) 
        return;

    nodoDoble *actual = ldePrestamos->primero;
    while (actual != NULL)
    {
        nodoDoble *aux = actual;
        actual = actual->sig;
        
        if (aux->prestamo != NULL)
        {
            liberarTPrestamoSoloEstructura(aux->prestamo);  
        }
        delete aux;
    }
    delete ldePrestamos;
    ldePrestamos = NULL;
}