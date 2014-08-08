#ifndef LIST_H_
#define LIST_H_

#include <pthread.h>

#define TRUE 1
#define FALSE 0

/*
*Implementacion de lista simplemente enlazada
*/
typedef struct sllist_node {

  void *value;                  // Contenido del nodo
  struct sllist_node *prev;     // Direccion en memoria del nodo anterior
  struct sllist_node *next;     // Direccion en memoria del nodo siguiente

} sllist_node;

typedef struct sllist {

  int count;                    // Cantidad de nodos
  sllist_node *head;            // Primer nodo de la lista
  sllist_node *tail;            // Ultimo nodo de la lista
  pthread_mutex_t mutex;        // Semaforo mutex 

} sllist;

#endif
