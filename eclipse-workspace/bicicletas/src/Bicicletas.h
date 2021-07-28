#ifndef BICICLETAS_H_
#define BICICLETAS_H_

typedef struct
{
    int id_bike;
    char nombre[20];
    char tipo[20];
    int tiempo;
}eBicicleta;

eBicicleta* bicicleta_new();
eBicicleta* bicicleta_newParametros(char* id_bikeStr,char* nombreStr,char* tipoStr,char* tiempoStr);
int listBicicleta(eBicicleta* this);
int listbicicletas(LinkedList* lista);
int filtrarTipoBmx(void* unaBicicleta);
int filtrarTipoPaseo(void* unaBicicleta);
int filtrarTipoMtb(void* unaBicicleta);
int filtrarTipoPlayera(void* unaBicicleta);
void cargarTiempos(void* unaBicicleta);
int compararTiempos(void* tiempo1,void* tiempo2);



#endif /* BICICLETAS_H_ */
