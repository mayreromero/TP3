#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Validaciones.h"

int validacionCadena(char* cadena){
    int flag = 0;
    int error = 0;
    int tamanio;

    tamanio = strlen(cadena);
    for(int i = 0; i < tamanio; i++){
        if(!((cadena[i] >= 65 && cadena[i] <= 90) || (cadena[i] >= 97 && cadena[i] <= 122))){
            flag = 1;
            error = 1;
        }
    }
    if(cadena[0] == '\0' || cadena[0] == ' '){
        flag = 1;
        error = 1;
    }
    if(flag == 1){
        printf("Ingrese cadena valida.\n");
    }
    return error;
}

void formatearCadena(char* cadena){
    strlwr(cadena);
    //int i = 0;
    cadena[0] = toupper(cadena[0]);
    /*while(cadena[i] != '\0'){
        if(cadena[i] == ' ' || cadena[i] == 39){
            cadena[i + 1] = toupper(cadena[i + 1]);
        }
        i++;
    }*/
}

