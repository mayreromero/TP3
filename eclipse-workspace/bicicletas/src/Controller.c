#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Parser.h"
#include "Bicicletas.h"

int controller_loadFromText(char* path , LinkedList* pArrayList)
{
    FILE* pFile;
    int estaOk = -1;
    int cantidad;
    if(path!=NULL && pArrayList!=NULL)
    {
        pFile=fopen(path,"r");
        if(pFile!=NULL)
        {
        	cantidad = parser_EmployeeFromText(pFile,pArrayList);
            if(cantidad!=-1)
            {
            	estaOk = cantidad;
            }
            fclose(pFile);
        }
    }
    return estaOk;
}

int controller_ListBicicletas(LinkedList* pArrayList)
{
    int estaOk=-1;
    if(pArrayList!=NULL)
    {
    	estaOk=listbicicletas(pArrayList);
    }

    return estaOk;
}

int controller_filtrarBicicletas(LinkedList* pArrayList,LinkedList* pArrayListFilt)
{
    int estaOk =-1;
    int opcion;
    if(pArrayList!=NULL && pArrayListFilt!=NULL)
    {
        printf("FILTRAR BICICLETAS POR TIPO ESPECIFICO .\n\n");
        printf("ELIJA UN TIPO DE BICICLETA: \n");
        printf("1-bmx\n");
        printf("2-playera\n");
        printf("3-mtb.\n");
        printf("4-paseo.\n");
        printf("INGRESE OPCION:: ");
        scanf("%d",&opcion);


        if(opcion==1)
        {
            pArrayListFilt=ll_filter(pArrayList,filtrarTipoBmx);
            controller_ListBicicletas(pArrayListFilt);
            controller_saveAsText("bicicletasBmx.csv",pArrayListFilt);
            estaOk=0;
        }
        else if(opcion==2)
        {
            pArrayListFilt=ll_filter(pArrayList,filtrarTipoPlayera);
            controller_ListBicicletas(pArrayListFilt);
            controller_saveAsText("bicicletasPlayeras.csv",pArrayListFilt);
            estaOk=0;
        }
        else if(opcion==3)
        {
            pArrayListFilt=ll_filter(pArrayList,filtrarTipoMtb);
            controller_ListBicicletas(pArrayListFilt);
            controller_saveAsText("bicicletasMtb.csv",pArrayListFilt);
            estaOk=0;
        }
        else if(opcion==4)
        {
            pArrayListFilt=ll_filter(pArrayList,filtrarTipoPaseo);
            controller_ListBicicletas(pArrayListFilt);
            controller_saveAsText("bicicletasPaseo.csv",pArrayListFilt);
        }
        else
        {
            printf("OPCION INCORRECTA.\n");
        }

    }
    return estaOk;
}


int controller_saveAsText(char* path , LinkedList* pArrayList)
{
    FILE* pFile;
    int estaOk =-1;
    eBicicleta* auxBicicleta;
    int tam;


    if(path!=NULL && pArrayList!=NULL)
    {
        pFile=fopen(path,"w");

        if(pFile!=NULL)
        {
            fprintf(pFile,"id_bike,nombre,tipo,tiempo\n");
            tam=ll_len(pArrayList);
            estaOk =0;
            for(int i=0; i<tam; i++)
            {
                auxBicicleta=((eBicicleta*)ll_get(pArrayList,i));
                if (auxBicicleta!=NULL)
                {
                    fprintf(pFile,"%d,%s,%s,%d\n",auxBicicleta->id_bike,auxBicicleta->nombre,auxBicicleta->tipo,auxBicicleta->tiempo);
                }
            }
            fclose(pFile);
        }
    }
    return estaOk;
}

int controller_cargarTiempos(LinkedList* pArrayList,LinkedList* pArrayListTiemp)
{
    int estaOk=-1;
    if(pArrayList!=NULL && pArrayListTiemp!=NULL)
    {
        pArrayListTiemp=ll_map(pArrayList,cargarTiempos);
        controller_ListBicicletas(pArrayListTiemp);
        estaOk=0;
    }
    return estaOk;
}

int controller_ListPos(LinkedList* pArrayList,LinkedList* pArrayListOrd)
{
    int estaOk=-1;
    if(pArrayList!=NULL && pArrayListOrd)
    {
        ll_sort(pArrayList,compararTiempos,0);
        controller_ListBicicletas(pArrayList);
        estaOk=0;
    }
    return estaOk;
}



