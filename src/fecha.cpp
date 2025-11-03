#include "../include/fecha.h"

struct rep_fecha
{
    nat dia, mes, anio;
};

TFecha crearTFecha(nat d, nat m, nat a)
{
    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = d;
    nuevaFecha->mes = m;
    nuevaFecha->anio = a;
    return nuevaFecha;
}

void liberarTFecha(TFecha &f)
{
    if (f != NULL)
    {
        delete f;
        f = NULL;
    }
}

void imprimirTFecha(TFecha f)
{
    printf("%u/%u/%u\n", f->dia, f->mes, f->anio);
}

TFecha copiarTFecha(TFecha f)
{
    if (f == NULL)
        return NULL;
    return crearTFecha(f->dia, f->mes, f->anio);
}

// Funciones auxiliares que voy a crear para aumentar Tfecha
bool esBisiesto(nat anio)
{
    if ((anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0))
        return true; // si es multiplo de 4 y no de 100, o de 400 es bisiesto

    return false;
}

static nat diasMes(nat m, nat a)
{
    switch (m)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return esBisiesto(a) ? 29 : 28;
    default:
        return 31;
    }
}

void aumentarTFecha(TFecha &f, nat d)
{
    f->dia += d;
    while (f->dia > diasMes(f->mes, f->anio))
    { // El error estaba en el while, cuando el d era muy grande el bucle se volvia infinito
        f->dia -= diasMes(f->mes, f->anio);
        f->mes++;
        if (f->mes > 12)
        {
            f->mes = 1;
            f->anio++;
        }
    }
}

int compararTFechas(TFecha f1, TFecha f2)
{
    if (f1->anio != f2->anio)
    {
        return f1->anio > f2->anio ? 1 : -1;
    }
    if (f1->mes != f2->mes)
    {
        return f1->mes > f2->mes ? 1 : -1;
    }
    if (f1->dia != f2->dia)
    {
        return f1->dia > f2->dia ? 1 : -1;
    }
    return 0;
}
