#include <stdio.h>
#include <stdlib.h>
#include "Controller.h"
#include "LinkedList.h"
#include "Bicicletas.h"
#include "time.h"


int menu();

int main()
{
	setbuf(stdout, NULL);

    LinkedList* listaBicicletas=ll_newLinkedList();
    LinkedList* listaBicicletasFilt=ll_newLinkedList();
    LinkedList* listaBicicletasTiempos=ll_newLinkedList();
    LinkedList* listaBicicletasOrdenadas=ll_newLinkedList();
    char seguir='s';
    char confirma;
    int cantidad;
    srand(time(NULL));
    int flag=0,flag2=0;;
    char nombreArchivo[10];
    do
    {
        switch(menu())
        {
            case 1:
                {
                    printf("CARGAR DATOS DE LAS BICICLETAS.\n");
                    printf("INGRESA EL NOMBRE DEL ARCHIVO( puedes utilizar bicicletas.csv): ");
                    fflush(stdin);
                    gets(nombreArchivo);
                    cantidad =controller_loadFromText(nombreArchivo,listaBicicletas);
                    if(cantidad ==-1)
                    {
                        printf("PRBLEMAS PARA CARGAR LAS BICICLETAS.\n");
                    }
                    else
                    {
                        printf("BICICLETAS CARGADAS CORRECTAMENTE \n");
                        flag=1;
                    }
                    break;
                }

            case 2:
                {
                    if(flag==0)
                    {
                        printf("AUN NO HAY BICICLETAS CARGADAS.\n");
                    }
                    else
                    {
                        printf("LISTAR BICICLETAS.\n");
                        if(controller_ListBicicletas(listaBicicletas))
                        {
                            printf("PROBLEMAS PARA LISTAR LAS BICICLETAS.\n");
                        }
                        else
                        {
                            printf("BICICLETAS LISTADAS CORRECTAMENTE.\n");
                        }
                    }
                    break;
                }
            case 3:
                {
                    if(flag==0)
                    {
                        printf("AUN NO HAY BICICLETAS CARGADAS.\n");
                    }
                    else
                    {
                        printf("ASIGNAR TIEMPOS.\n");
                        if(controller_cargarTiempos(listaBicicletas,listaBicicletasTiempos))
                        {
                            printf("PROBLEMAS PARA CARGAR TIEMPOS DE LAS BICICLETAS.\n");
                        }
                        else
                        {
                            printf("TIEMPOS CARGADOS CORRECTAMENTE.\n");
                            flag2=1;
                        }
                    }
                    break;
                }
            case 4:
                {
                    if(flag==0)
                    {
                        printf("AUN NO HAY BICICLETAS CARGADAS.\n");
                    }
                    else
                    {
                        if(controller_filtrarBicicletas(listaBicicletas,listaBicicletasFilt))
                        {
                            printf("PROBLEMAS PARA FILTRAR BICICLETAS.\n");
                        }
                        else
                        {
                            printf("BICICLETAS CARGADAS CORRECTAMENTE.\n");
                        }
                    }
                    break;
                }
            case 5:
                {
                    if(flag==0 || flag2==0)
                    {
                        printf("AUN NO HAY BICICLETAS CARGADAS O TIEMPOS ASIGNADOS.\n");
                    }
                    else
                    {
                        printf("MOSTRAR POSICIONES.\n");
                        if(controller_ListPos(listaBicicletas,listaBicicletasOrdenadas))
                        {
                            printf("PROBLEMAS PARA LISTAR LAS POSICIONES.\n");
                        }
                        else
                        {
                            printf("POSICIONES LISTADAS CORRECTAMENTE.\n");
                        }
                    }
                    break;
                }
            case 6:
                {
                    if(flag==0|| flag2==0)
                    {
                        printf("AUN NO HAY BICICLETAS CARGADAS O TIEMPOS ASIGNADOS.\n");
                    }
                    else
                    {
                        printf("GUARDAR POSICIONES.\n");
                        if(controller_saveAsText("bicicletasPosiciones.csv",listaBicicletas))
                        {
                            printf("PROBLEMAS PARA LISTAR POSICIONES.\n");
                        }
                        else
                        {
                            printf("POSICIONES LISTADAS CORRECTAMENTE.\n");
                        }
                    }
                    break;
                }
            case 7:
                {
                    printf("DESEA SALIR ( s / n ): ");
                    fflush(stdin);
                    scanf("%c", &confirma);
                    if(confirma=='s')
                    {
                        seguir='n';
                    }
                    break;
                }

            default:
                {
                    printf("LA OPCION NO ES CORRECTA.\n");
                    break;

                }
        }
    system("pause");
    }while(seguir=='s');
    return 0;
}

int menu()
{
    int opc;
    printf("----------------*** BICICLETAS ***--------------------\n");
    printf("1. CARGAR LOS DATOS DE LAS BICICLETAS.\n");
    printf("2. LISTAR BICICLETAS.\n");
    printf("3. ASIGNAR TIEMPOS.\n");
    printf("4. FILTRAR BICICLETAS POR TIPO.\n");
    printf("5. MOSTRAR POSICIONES.\n");
    printf("6. GUARDAR POSICIONES.\n");
    printf("7. SALIR DEL PROGRAMA.\n");
    printf("INGRESE OPCION: ");
    scanf("%d",&opc);
    return opc;
}
