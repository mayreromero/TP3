#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "ctype.h"
#include "menu.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/


int main()
{
	setbuf(stdout, NULL);

    int rta;
    int flagTxt = 0;
    int flagBin = 0;
    int flagAdd = 0;
    char seguir = 's';
    char confirmacion;
    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
        switch(menu())
        {
            case 1:
                if(!controller_loadFromText("data.cvs",listaEmpleados)){
                    printf("Datos cargados con exito.\n");
                    flagTxt = 1;
                }else{
                    printf("Error al cargar los datos.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 2:
                if(!controller_loadFromBinary("data.bin",listaEmpleados)){
                    printf("Datos cargados con exito.\n");
                    flagBin = 1;
                }else{
                    printf("Error al cargar los datos.\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 3:
                if(!controller_addEmployee(listaEmpleados)){
                    flagAdd = 1;
                }else{
                    printf("Error en el alta.\n");
                }
                break;
            case 4:
                if(flagAdd == 1 || flagBin == 1 || flagTxt == 1){
                    rta = controller_editEmployee(listaEmpleados);
                    if(!rta){
                        printf("Modificacion realizada con exito.\n");
                    }else if(rta == 2){
                        printf("Modificacion cancelada por el usuario.\n");
                    }else{
                        printf("Error en la modificacion.\n");
                    }
                }else{
                    printf("Lista vacia,cargar la lista.\n");
                }
                break;
            case 5:
                if(flagAdd == 1 || flagBin == 1 || flagTxt == 1){
                    rta = controller_removeEmployee(listaEmpleados);
                    if(!rta){
                        printf("Baja realizada con exito.\n");
                    }else if(rta == 2){
                        printf("Baja cancelada por el usuario.\n");
                    }else{
                        printf("Error en la baja.\n");
                    }
                }else{
                    printf("Lista vacia,cargar la lista.\n");
                }
                break;
            case 6:
                if(controller_ListEmployee(listaEmpleados)){
                    printf("Error al mostrar la lista");
                }
                break;
            case 7:
                if(flagAdd == 1 || flagBin == 1 || flagTxt == 1){
                    rta = controller_sortEmployee(listaEmpleados);
                    if(!rta){
                        printf("Lista ordenada con exito.\n");
                    }else if(rta == 2){
                        printf("Ordenamiento cancelado por el usuario.\n");
                    }else{
                        printf("Error al ordenar la lista.\n");
                    }
                }else{
                    printf("Lista vacia,cargar la lista.\n");
                }
                break;
            case 8:
                if(!controller_saveAsText("data.cvs",listaEmpleados)){
                    printf("Datos guardados con exito.\n");
                }else{
                    printf("Error al guardar los datos.\n");
                }
                break;
            case 9:
                if(!controller_saveAsBinary("data.bin",listaEmpleados)){
                    printf("Datos guardados con exito.\n");
                }else{
                    printf("Error al guardar los datos.\n");
                }
                break;
            case 10:
                printf("Confirma la salida?(s/n)");
                fflush(stdin);
                scanf("%c", &confirmacion);
                confirmacion = tolower(confirmacion);
                if(confirmacion == 's'){
                seguir = 'n';
                ll_deleteLinkedList(listaEmpleados);
                }
                break;
            default:
                printf("Opcion invalida.\n");

        }
    system("pause");
    }while(seguir == 's');
    return 0;
}

