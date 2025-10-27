#include "../include/socio.h"

struct rep_socio {
};

TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta, nat rango){
    return NULL;
}

void imprimirTSocio(TSocio socio){
}

void liberarTSocio(TSocio &socio){
}

int ciTSocio(TSocio socio){
    return 0;
}

nat rangoTSocio(TSocio socio) {
  return 1;
}

char* nombreTSocio(TSocio socio){
    return NULL;
}

char* apellidoTSocio(TSocio socio){
    return NULL;
}

TFecha fechaAltaTSocio(TSocio socio){
    return NULL;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    return false;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){
    return 0;
}

TSocio copiarTSocio(TSocio socio){
    return NULL;
}
