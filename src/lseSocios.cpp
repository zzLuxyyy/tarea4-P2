
#include "../include/lseSocios.h"

struct nodo
{
	TSocio socio;
	nodo *sig;
};

struct rep_lseSocios
{
	nodo *primero;
	nat cantidad;
};

TLSESocios crearTLSESociosVacia()
{
	TLSESocios nueva = new rep_lseSocios;
	nueva->primero = NULL;
	nueva->cantidad = 0;
	return nueva;
}

bool esVaciaTLSESocios(TLSESocios lseSocios)
{
    return lseSocios->primero == NULL;
}

void imprimirTLSESocios(TLSESocios lseSocios)
{	
    printf("Lista de Socios:\n");
	nodo* actual = lseSocios->primero;
    while (actual != NULL) {
        imprimirTSocio(actual->socio);
        actual = actual->sig;
    }
}

void liberarTLSESocios(TLSESocios &lseSocios)
{
	nodo *actual = lseSocios->primero;
	while (actual != NULL)
	{
		nodo *aBorrar = actual;
		actual = actual->sig;
		liberarTSocio(aBorrar->socio);
		delete aBorrar;
	}
	delete lseSocios;
	lseSocios = NULL;
}

void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio) {
    nodo* nuevo = new nodo;
    nuevo->socio = socio;
    nuevo->sig = NULL;

    if (lseSocios->primero == NULL || compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(lseSocios->primero->socio)) == -1) {
        // la lista está vacia o el nuevo socio va al principio
        nuevo->sig = lseSocios->primero;
        lseSocios->primero = nuevo;
    } else {
        // el socio va en el medio o al final
        nodo* actual = lseSocios->primero;
        while (actual->sig != NULL && compararTFechas(fechaAltaTSocio(socio), fechaAltaTSocio(actual->sig->socio)) >= 0) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
    lseSocios->cantidad++;
}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci) {
    nodo* actual = lseSocios->primero;
    while (actual != NULL) {
        if (ciTSocio(actual->socio) == ci) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci) {
    nodo* actual = lseSocios->primero;
    while (actual != NULL && ciTSocio(actual->socio) != ci) {
        actual = actual->sig;
    }
    if (actual != NULL) {
        return actual->socio;
    }
    return NULL;  
}

TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n) {
    nodo* actual = lseSocios->primero;
    for (int i = 1; i < n; i++) {
        actual = actual->sig;
    }
    return actual->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios) {
	return lseSocios->cantidad;
}

void removerSocioTLSESocios(TLSESocios &lseSocios, int ci)
{
	nodo *actual = lseSocios->primero;
	nodo *anterior = NULL;

	while (actual != NULL && ciTSocio(actual->socio) != ci)
	{
		anterior = actual;
		actual = actual->sig;
	}

	if (actual != NULL)
	{
		if (anterior == NULL)
		{
			lseSocios->primero = actual->sig;
		}
		else
		{
			anterior->sig = actual->sig;
		}

		liberarTSocio(actual->socio);
		delete actual;
		lseSocios->cantidad--;
	}
}