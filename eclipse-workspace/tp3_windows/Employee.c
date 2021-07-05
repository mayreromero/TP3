#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"

Employee* employee_new(){
    Employee* nuevoEmpleado = NULL;
    nuevoEmpleado = (Employee*) malloc (sizeof(Employee));

    if(nuevoEmpleado != NULL){
        nuevoEmpleado->id = 0;
        strcpy(nuevoEmpleado->nombre, "");
        nuevoEmpleado->horasTrabajadas = 0;
        nuevoEmpleado->sueldo = 0;
    }

    return nuevoEmpleado;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo){
    Employee* nuevoEmpleado = employee_new();

    if(nuevoEmpleado != NULL){
        if(!(employee_setId(nuevoEmpleado, atoi(idStr)) && employee_setNombre(nuevoEmpleado, nombreStr) && employee_setHorasTrabajadas(nuevoEmpleado, atoi(horasTrabajadasStr)) && employee_setSueldo(nuevoEmpleado, atoi(sueldo)))){
            free(nuevoEmpleado);
            nuevoEmpleado = NULL;
        }

    }
    return nuevoEmpleado;
}

void employee_delete(Employee* this){
    if(this != NULL){
        free(this);
        this = NULL;
    }
}

int employee_setId(Employee* this,int id){
    int todoOk = 0;
    if(this != NULL && id > 0){
        this->id = id;
        todoOk = 1;
    }else{
        printf("EL ID NO ES VALIDO.\n");
    }
    return todoOk;
}

int employee_getId(Employee* this,int* id){
    int todoOk = 0;
    if(this != NULL && id > 0){
        *id = this->id;
        todoOk = 1;
    }
    return todoOk;
}

int employee_setNombre(Employee* this,char* nombre){
    int todoOk = 0;
    if(this != NULL && nombre != NULL){
        strcpy(this->nombre, nombre);
        todoOk = 1;
    }
    return todoOk;
}

int employee_getNombre(Employee* this,char* nombre){
    int todoOk = 0;
    if(this != NULL && nombre != NULL){
        strcpy(nombre, this->nombre);
        todoOk = 1;
    }else{
        printf("EL NOMBRE NO ES VALIDO \n");
    }
    return todoOk;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas){
    int todoOk = 0;
    if(this != NULL && horasTrabajadas >= 0){
        this->horasTrabajadas = horasTrabajadas;
        todoOk = 1;
    }else{
        printf("CANTIDAD DE HORAS NO SON VALIDAS\n");
    }
    return todoOk;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas){
    int todoOk = 0;
    if(this != NULL && horasTrabajadas >= 0){
        *horasTrabajadas = this->horasTrabajadas;
        todoOk = 1;
    }
    return todoOk;
}

int employee_setSueldo(Employee* this,int sueldo){
    int todoOk = 0;
    if(this != NULL && sueldo >= 0){
        this->sueldo = sueldo;
        todoOk = 1;
    }else{
        printf("EL SUELDO NO ES VALIDO .\n");
    }
    return todoOk;
}

int employee_getSueldo(Employee* this,int* sueldo){
    int todoOk = 0;
    if(this != NULL && sueldo >= 0){
        *sueldo = this->sueldo;
        todoOk = 1;
    }
    return todoOk;
}

void printEmployee(Employee* empleado){
    if(empleado != NULL){
        printf("  %04d %20s       %3dhs         $%6d\n",empleado->id, empleado->nombre, empleado->horasTrabajadas, empleado->sueldo);
    }
}

int employeeLastId(LinkedList* pArrayListEmployee){
    int tam = ll_len(pArrayListEmployee);
    int auxId;
    int ultimoId = 0;
    int flag = 0;
    Employee* pEmployee;

    if(pArrayListEmployee != NULL){
        for(int i = 0; i < tam; i++){
            pEmployee = (Employee*) ll_get(pArrayListEmployee,i);
            employee_getId(pEmployee, &auxId);

            if(auxId > ultimoId || flag == 0){
                ultimoId = auxId;
                flag = 1;
            }
        }
    }
    return ultimoId;
}

int findEmployeeById(LinkedList* pArrayListEmployee,int id){
    int indice = -1;
    int tam = ll_len(pArrayListEmployee);
    Employee* auxEmpleado;
    for(int i = 0; i < tam; i++){
        auxEmpleado = ll_get(pArrayListEmployee, i);
        if(auxEmpleado->id == id){
            indice = i;
            break;
        }
    }
    return indice;
}

int employeeSortByName(void* empleadoA, void* empleadoB){
    int retorno = 0;
    char nombreA[128];
    char nombreB[128];

    if(empleadoA != NULL && empleadoB != NULL){
        employee_getNombre((Employee*)empleadoA, nombreA);
        employee_getNombre((Employee*)empleadoB, nombreB);

        retorno = strcmpi(nombreA, nombreB);
    }
    return retorno;
}

int employeeSortById(void* empleadoA, void* empleadoB){
    int retorno = 0;
    int idA;
    int idB;

    if(empleadoA != NULL && empleadoB != NULL){
        employee_getId((Employee*)empleadoA, &idA);
        employee_getId((Employee*)empleadoB, &idB);

        if(idA == idB){
            retorno = 0;
        }else if(idA > idB){
            retorno = 1;
        }else{
            retorno = -1;
        }
    }
    return retorno;
}

int employeeSortByWorksHours(void* empleadoA, void* empleadoB){
    int retorno = 0;
    int horasA;
    int horasB;

    if(empleadoA != NULL && empleadoB != NULL){
        employee_getHorasTrabajadas((Employee*)empleadoA, &horasA);
        employee_getHorasTrabajadas((Employee*)empleadoB, &horasB);

        if(horasA == horasB){
            retorno = 0;
        }else if(horasA > horasB){
            retorno = 1;
        }else{
            retorno = -1;
        }
    }
    return retorno;
}

int employeeSortBySalary(void* empleadoA, void* empleadoB){
    int retorno = 0;
    int sueldoA;
    int sueldoB;

    if(empleadoA != NULL && empleadoB != NULL){
        employee_getSueldo((Employee*)empleadoA, &sueldoA);
        employee_getSueldo((Employee*)empleadoB, &sueldoB);

        if(sueldoA == sueldoB){
            retorno = 0;
        }else if(sueldoA > sueldoB){
            retorno = 1;
        }else{
            retorno = -1;
        }
    }
    return retorno;
}


