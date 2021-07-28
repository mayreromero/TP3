#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "LinkedList.h"

int controller_loadFromText(char* path , LinkedList* pArrayList);
int controller_ListBicicletas(LinkedList* pArrayList);
int controller_filtrarBicicletas(LinkedList* pArrayList,LinkedList* pArrayListFilt);
int controller_saveAsText(char* path , LinkedList* pArrayList);
int controller_cargarTiempos(LinkedList* pArrayList,LinkedList* pArrayListTiemp);
int controller_ListPos(LinkedList* pArrayList,LinkedList* pArrayListOrd);


#endif /* CONTROLLER_H_ */
