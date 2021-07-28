#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Bicicletas.h"

int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayList)
{
    char buffer [10][2000];
    int retorno=-1;
    eBicicleta* auxBicicleta;
    int cant;
    if(pFile!=NULL&&pArrayList!=NULL)
    {
        //LECTURA DEL ENUNCIADO
        cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
        while(!feof(pFile))
        {
            cant=fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
            if(cant==4)
            {
                auxBicicleta=bicicleta_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]);
                ll_add(pArrayList,auxBicicleta);
                retorno=auxBicicleta->id_bike;
            }
            else
            {
                break;
            }
        }
    }
    return retorno;
}

