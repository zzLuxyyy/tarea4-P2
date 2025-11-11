#include "../include/socio.h"
#include <string.h> //strcpy
#include <stdio.h>
#include "fecha.h"

struct rep_socio
{
    int ci;
    char nombre[MAX_NOMBRE_SOCIO];
    char apellido[MAX_APELLIDO_SOCIO];
    TFecha fechaAlta;
    int generosFavoritos[MAX_GENEROS_FAVORITOS];
    int topeGeneros;
    nat rango;
};

TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta, nat rango)
{
    TSocio nuevoSocio = new rep_socio; // Faltaba agregar new

    nuevoSocio->ci = ci;
    strcpy(nuevoSocio->nombre, nombre);
    strcpy(nuevoSocio->apellido, apellido);
    nuevoSocio->fechaAlta = crearTFecha(diaAlta, mesAlta, anioAlta);
    nuevoSocio->topeGeneros = 0;
    nuevoSocio->rango = rango;

    return nuevoSocio; // Estabas retornando rep_socio lo cual es incorrecto porque es un struct.
}

// Función que imprime la información del socio en el siguiente formato
void imprimirTSocio(TSocio socio)
{
    printf("Socio %d: %s %s\n", socio->ci, socio->nombre, socio->apellido);

    printf("Fecha de alta: ");
    imprimirTFecha(socio->fechaAlta);
    printf("Géneros favoritos: ");

    for (int i = 0; i < socio->topeGeneros; i++)
    {
        printf("%d ", socio->generosFavoritos[i]);
    }

    printf("\n");
}

void liberarTSocio(TSocio &socio)
{
    liberarTFecha(socio->fechaAlta);
    delete socio;
    socio = NULL;
}

int ciTSocio(TSocio socio)
{
    return socio->ci;
}
nat rangoTSocio(TSocio socio)
{
    return socio->rango; 
}

char *nombreTSocio(TSocio socio)
{
    return socio->nombre;
}

char *apellidoTSocio(TSocio socio)
{
    return socio->apellido;
}

TFecha fechaAltaTSocio(TSocio socio)
{
    return socio->fechaAlta;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero)
{
    if (socio->topeGeneros < MAX_GENEROS_FAVORITOS)
    {
        socio->generosFavoritos[socio->topeGeneros] = idGenero;
        socio->topeGeneros++;
    }
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero)
{
    for (int i = 0; i < socio->topeGeneros; i++)
    {
        if (socio->generosFavoritos[i] == idGenero) // El error estaba en *tope*generosFavoritos.
        {
            return true;
        }
    }
    return false;
}

int cantidadGenerosFavoritosTSocio(TSocio socio)
{
    return socio->topeGeneros;
}

TSocio copiarTSocio(TSocio socio)
{
    if (socio == NULL)
        return NULL;

    // Crear copia sin usar crearTSocio para evitar leaks
    TSocio copia = new rep_socio;
    copia->ci = socio->ci;
    strcpy(copia->nombre, socio->nombre);
    strcpy(copia->apellido, socio->apellido);
    copia->fechaAlta = copiarTFecha(socio->fechaAlta); // Copia profunda
    copia->topeGeneros = socio->topeGeneros;

    for (int i = 0; i < socio->topeGeneros; i++)
    {
        copia->generosFavoritos[i] = socio->generosFavoritos[i];
    }

    return copia;
}
