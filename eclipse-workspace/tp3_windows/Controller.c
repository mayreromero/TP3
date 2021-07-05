#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "Validaciones.h"
#include "Controller.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int error = 1;
    FILE* pFile;

    pFile = fopen(path, "r");
    if(pFile != NULL){
        if(!parser_EmployeeFromText(pFile, pArrayListEmployee)){
            error = 0;
        }
    }

    fclose(pFile);

    return error;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int error = 1;
	FILE* pFile;

	pFile = fopen(path, "rb");

	if(pFile != NULL){
		if(!parser_EmployeeFromBinary(pFile, pArrayListEmployee)){
			error = 0;
		}

	}
	fclose(pFile);
    return error;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int error = 1;
    int validacion;
    int id;
    int horas;
    int sueldo;
    char nombre[128];
    Employee* auxEmpleado;

    auxEmpleado = employee_new();

    system("cls");
    printf("   *** ALTA DE EMPLEADOS ***   \n\n");

    if(pArrayListEmployee != NULL && auxEmpleado != NULL){
        id = employeeLastId(pArrayListEmployee);
        employee_setId(auxEmpleado, id + 1);
        do{
            printf("INGRESE NOMBRE: ");
            fflush(stdin);
            gets(nombre);
            formatearCadena(nombre);
            validacion = validacionCadena(nombre);
        }while(validacion == 1 || !employee_setNombre(auxEmpleado, nombre));
        do{
            printf("INGRESE HORAS TRABAJADAS: ");
            scanf("%d", &horas);
        }while(!employee_setHorasTrabajadas(auxEmpleado, horas));
        do{
            printf("INGRESE SUELDO: ");
            scanf("%d", &sueldo);
        }while(!employee_setSueldo(auxEmpleado, sueldo));

        ll_add(pArrayListEmployee, auxEmpleado);
        printf("\n ALTA EXITOSA!\n");
        error = 0;
    }else{
        free(auxEmpleado);
    }

    return error;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int indice;
    int validacion;
    int id;
    int horas;
    int sueldo;
    int opcion;
    char nombre[128];
    int error = 1;
    int flagSalir = 0;
    int flagDef = 0;
    char confirmacion;
    Employee* auxEmpleado = employee_new();
    Employee modificar;

    if(pArrayListEmployee != NULL && auxEmpleado != NULL){
        system("cls");

        printf("   *** MODIFICAR EMPLEADOS ***   \n\n");
        controller_ListEmployee(pArrayListEmployee);
        printf("INGRESE ID: ");
        scanf("%d", &id);
        indice = findEmployeeById(pArrayListEmployee, id);
        auxEmpleado = (Employee*) ll_get(pArrayListEmployee, indice);


        if(indice == -1){
            printf("NO EXISTE NINGUN EMPLEADO CON ESE D\n");
        }else{
            modificar = *auxEmpleado;

            printf("*** MODIFICAR EMPLEADOS ***\n\n");
            printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
            printf("-------------------------------------------------------\n");
            printEmployee(auxEmpleado);
            printf("-------------------------------------------------------\n\n");
            printf("1) MODIFICAR ID.\n");
            printf("2) MODIFICAR NOMBRE.\n");
            printf("3) MODIFICAR HORAS TRABAJADAS.\n");
            printf("4) MODIFICAR SUELDO.\n");
            printf("5) MENU ANTERIOR.\n");
            printf("SELECCIONE UN OPCION: ");
            fflush(stdin);
            scanf("%d", &opcion);

            switch(opcion){
            case 1:
                do{
                    printf("*** MODIFICAR EMPLEADOS ***\n\n");
                    printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
                    printf("-------------------------------------------------------\n");
                    printEmployee(auxEmpleado);
                    printf("-------------------------------------------------------\n\n");
                    printf("INGRESE NUEVO ID: ");
                    scanf("%d", &id);
                }while(!employee_setId(&modificar, id));
                break;
            case 2:
                do{
                    printf("*** MODIFICAR EMPLEADOS ***\n\n");
                    printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
                    printf("-------------------------------------------------------\n");
                    printEmployee(auxEmpleado);
                    printf("-------------------------------------------------------\n\n");
                    printf("INGRESE NUEVO NOMBRE: ");
                    fflush(stdin);
                    gets(nombre);
                    formatearCadena(nombre);
                    validacion = validacionCadena(nombre);
                }while(validacion == 1 || !employee_setNombre(&modificar, nombre));
                break;
            case 3:
                do{
                    printf("*** MODIFICAR EMPLEADOS ***\n\n");
                    printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
                    printf("-------------------------------------------------------\n");
                    printEmployee(auxEmpleado);
                    printf("-------------------------------------------------------\n\n");
                    printf("INGRESE NUEVAS HORAS TRABAJADAS: ");
                    scanf("%d", &horas);
                }while(!employee_setHorasTrabajadas(&modificar, horas));
                break;
            case 4:
                do{
                    printf("*** MODIFICAR EMPLEADOS ***\n\n");
                    printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
                    printf("-------------------------------------------------------\n");
                    printEmployee(auxEmpleado);
                    printf("-------------------------------------------------------\n\n");
                    printf("INGRESE NUEVO SUELDO: ");
                    scanf("%d", &sueldo);
                }while(!employee_setSueldo(&modificar, sueldo));
                break;
            case 5:
                flagSalir = 1;
                error = 2;
                break;
            default:
                flagDef = 1;
                printf("OPCION NO VALIDA\n");
                break;
            }
            if(!flagSalir && !flagDef){
                printf("CONFIRMA LA MODIFICACION(S/N)? ");
                fflush(stdin);
                scanf("%c", &confirmacion);
                if(confirmacion == 's'){
                    auxEmpleado->id = modificar.id;
                    strcpy(auxEmpleado->nombre,modificar.nombre);
                    auxEmpleado->horasTrabajadas = modificar.horasTrabajadas;
                    auxEmpleado->sueldo = modificar.sueldo;
                    error = 0;
                }else{
                    error = 2;
                }
            }
        }
    }
    return error;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int indice;
    int id;
    int error = 1;
    char confirmacion;
    Employee* auxEmpleado = employee_new();

    if(pArrayListEmployee!= NULL && auxEmpleado != NULL){

        printf("   *** BAJA DE EMPLEADOS ***   \n\n");
        controller_ListEmployee(pArrayListEmployee);
        printf("INGRESE ID: ");
        scanf("%d", &id);
        indice = findEmployeeById(pArrayListEmployee, id);
        auxEmpleado = (Employee*) ll_get(pArrayListEmployee, indice);

        if(indice == -1){
            printf("NO EXISTE NINGUN EMPLEADO CON ESE ID\n");
        }else{


            printf("   *** BAJA DE EMPLEADOS ***   \n\n");
            printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
            printf("-------------------------------------------------------\n");
            printEmployee(auxEmpleado);
            printf("-------------------------------------------------------\n\n");
            printf("INGRESE NUEVAS HORAS TRABAJADAS ");
            printf("CONFIRMA LA BAJA(S/N)? ");
            fflush(stdin);
            scanf("%c", &confirmacion);

            if(confirmacion == 's'){
                ll_remove(pArrayListEmployee, indice);
                error = 0;
            }else{
                error = 2;
            }
        }
    }

    return error;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int error = 1;
    int tam = ll_len(pArrayListEmployee);
    Employee* auxEmpleado;


    printf("   ***LISTA DE EMPLEADOS***   \n\n");

    if(pArrayListEmployee != NULL){
        printf("  ID         NOMBRE          HS TRABAJADAS       SUELDO\n");
        printf("-------------------------------------------------------\n");
        for(int i = 0; i < tam; i++){
            auxEmpleado = ll_get(pArrayListEmployee, i);
            if(auxEmpleado != NULL){
                printEmployee(auxEmpleado);
                printf("-------------------------------------------------------\n");
            }
        }
        error = 0;
    }
    if(tam == 0){
        printf("NO HAY EMPLEADOS EN LA LISTA\n");
    }
    printf("\n");
    return error;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int error = 1;
    int opcion;
    int flagSalir = 0;
    int flagDef = 0;

    if(pArrayListEmployee != NULL){


        printf("   *** ORDENAR EMPLEADOS ***   \n\n");
        printf("1) ORDENAR POR ID.\n");
        printf("2) ORDENAR POR NOMBRE.\n");
        printf("3) ORDENAR POR HORAS TRABAJADAS.\n");
        printf("4) ORDENAR POR SUELDOS.\n");
        printf("5) MENU ANTERIOR.\n");
        printf("Seleccione un opcion: ");
        fflush(stdin);
        scanf("%d", &opcion);

        switch(opcion){
            case 1:
                printf("   *** ORDENAR EMPLEADOS POR ID***   \n\n");
                printf("1) ORDEN ASCENDENTE\n");
                printf("2) ORDEN DESCENDENTE\n");
                printf("SELECCIONE UN OPCION: ");
                fflush(stdin);
                scanf("%d", &opcion);
                if(opcion == 1){
                    ll_sort(pArrayListEmployee,employeeSortById,1);
                }else if(opcion == 2){
                    ll_sort(pArrayListEmployee,employeeSortById,0);
                }else{
                    printf("OPCION NO VALIDA\n");
                    error = 2;
                }
                break;
            case 2:
                printf("   *** ORDENAR EMPLEADOS POR NOMBRE***   \n\n");
                printf("1) ORDEN ASCENDENTE\n");
                printf("2) ORDEN DESCENDENTE\n");
                printf("SELECCIONE UN OPCION: ");
                fflush(stdin);
                scanf("%d", &opcion);
                if(opcion == 1){
                    ll_sort(pArrayListEmployee,employeeSortByName,1);
                }else if(opcion == 2){
                    ll_sort(pArrayListEmployee,employeeSortByName,0);
                }else{
                    printf("OPCION NO VALIDA.\n");
                    error = 2;
                }
                break;
            case 3:
                printf("   *** ORDENAR EMPLEADOS POR HS TRABAJADAS***   \n\n");
                printf("1) ORDEN ASCENDENTE\n");
                printf("2) ORDEN DESCENDENTE\n");
                printf("SELECCIONE UN OPCION: ");
                fflush(stdin);
                scanf("%d", &opcion);
                if(opcion == 1){
                    ll_sort(pArrayListEmployee,employeeSortByWorksHours,1);
                }else if(opcion == 2){
                    ll_sort(pArrayListEmployee,employeeSortByWorksHours,0);
                }else{
                    printf("OPCION NO VALIDA.\n");
                    error = 2;
                }
                break;
            case 4:
                printf("   *** ORDENAR EMPLEADOS POR SALARIO***   \n\n");
                printf("1) ORDEN ASCENDENTE\n");
                printf("2) ORDEN DESCENDENTE\n");
                printf("SELECCIONE UN OPCION: ");
                fflush(stdin);
                scanf("%d", &opcion);
                if(opcion == 1){
                    ll_sort(pArrayListEmployee,employeeSortBySalary,1);
                }else if(opcion == 2){
                    ll_sort(pArrayListEmployee,employeeSortBySalary,0);
                }else{
                    printf("OPCION NO VALIDA.\n");
                    error = 2;
                }
                break;
            case 5:
                flagSalir = 1;
                error = 2;
                break;
            default:
                flagDef = 1;
                printf("OPCION NO VALIDA.\n");
                break;
            }
            if(!flagSalir && !flagDef && error != 2){
                error = 0;
            }else{
                error = 2;
            }

    }
    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int error = 1;
    int tam;
    int auxId;
    int auxHora;
    int auxSalario;
	char auxNombre[128];
	FILE* pFile;
	Employee* auxEmpleado;

    tam = ll_len(pArrayListEmployee);

	if(pArrayListEmployee != NULL && path != NULL){
		pFile = fopen(path, "w");
		if(pFile != NULL){
			for(int i = 0; i < tam ; i++){
				auxEmpleado = ll_get(pArrayListEmployee, i);
				if((employee_getId(auxEmpleado, &auxId) && employee_getNombre(auxEmpleado, auxNombre) && employee_getHorasTrabajadas(auxEmpleado, &auxHora)&& employee_getSueldo(auxEmpleado, &auxSalario))){
					fprintf(pFile, "%d,%s,%d,%d\n", auxId, auxNombre, auxHora, auxSalario);
					error = 0;
				}
			}
			fclose(pFile);
		}
	}
    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int error = 1;
	FILE* pFile;
	Employee* auxEmpleado;

	if(pArrayListEmployee != NULL && path != NULL){
		pFile = fopen(path, "wb");

		for(int i = 1; i < ll_len(pArrayListEmployee); i++){
			auxEmpleado = (Employee*) ll_get(pArrayListEmployee, i);
			fwrite(auxEmpleado, sizeof(Employee), 1, pFile);
		}

		fclose(pFile);
		error = 0;
	}
    return error;
}
