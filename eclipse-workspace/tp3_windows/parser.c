#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int error = 1;
    int cant;
    char buffer[4][128];
    Employee* auxEmpleado;

    if(pFile != NULL){
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
        while(!feof(pFile)){
            cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

            if(cant == 4){
                auxEmpleado = employee_newParametros(buffer[0], buffer[1], buffer[2], buffer[3]);
                ll_add(pArrayListEmployee, auxEmpleado);
            }else{
                break;
            }

        }
        error = 0;
    }
    return error;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int error = 1;
    Employee* auxEmpleado;
    if(pFile != NULL){
        do{
			auxEmpleado = employee_new();
			if(fread(auxEmpleado, sizeof(Employee), 1, pFile) == 1){
				ll_add(pArrayListEmployee, auxEmpleado);
				error = 0;
			}
		}while(!feof(pFile));
	}

    return error;
}
