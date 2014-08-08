#include <stdlib.h>
#include "list.h"

/*
* Crea una nueva lista y la inicializa en memoria
*
* return sllist     Retorna un puntero a la lista creada
*/
sllist *sllist_create() {

  sllist* list;

  // Aloja memoria para contener la lista
  list = (sllist *) malloc(sizeof(list));

  // Inicializa la lista
  list->count = 0;
  list->head = NULL;
  list->tail = NULL;
  pthread_mutex_init(&(list->mutex), NULL);

}

/*
* Libera una lista en memoria
*
* @param list       lista
*
* return void
*/
void sllist_free(sllist *list) {

  sllist_node *node;
  sllist_node *tmp_node;

  // Activa el mutex
  pthread_mutex_lock(&(list->mutex));

  // Si la lista no se encuentra vacia
  if(list != NULL) {

    node = list->head;

    // Libera los nodos en memoria uno a uno
    while(node != NULL) {

      tmp_node = node->next;
      free(node);
      node = tmp_node;

    }

  }

  // Desactiva el mutex y lo destruye
  pthread_mutex_unlock(&(list->mutex));
  pthread_mutex_destroy(&(list->mutex));

  // Libera la lista de memoria
  free(list);

}

/*
* Agrega un elemento a una lista pasada por parametro
*
* @param elem_ptr   Elemento a agregar a la lista
* @param lista      Lista a la cual se agrega el elemento
*
* return node       Nodo que contienen el elemento agregado
*/
sllist_node *sllist_add_last(void *elem_ptr, sllist* list) {

  sllist_node *node;

  // Activa el mutex
  pthread_mutex_lock(&(list->mutex));

  // Aloja memoria para el nuevo nodo
  node = (sllist_node *) malloc(sizeof(sllist_node));

  // Asigna el contenido del nodo
  node->value = elem_ptr;
  node->next = NULL;
  node->prev = list->tail;

  // Agrega el nodo al final de la lista
  if(list->tail == NULL) {

    list->head = list->tail = node;
  
  } else {

    list->tail = node;

  }

  // Incrementa la cantidad de nodos
  list->count++;

  // Desactiva el mutex
  pthread_mutex_unlock(&(list->mutex));

  return node;

}

/*
* Elimina un elemento de una lista pasada por parametro
*
* @param elem_ptr   Elemento a eliminar de la lista
* @param lista      Lista de la cual se elimina el elemento
*
* return ret        TRUE elemento eliminado; FALSE elemento no eliminado
*/
int sllist_remove(void *elem_ptr, sllist *list) {

  int ret = FALSE;
  sllist_node *node = NULL;

  // Activa el mutex
  pthread_mutex_lock(&(list->mutex));

  node = list->head;
  
  // Mientras no llegue al final de la lista
  while(node != NULL) {
  
    // Si es el nodo buscado
    if (node->value == elem_ptr) {
      
      if(node->prev == NULL) {
	list->head = node->next;
      } else {
	node->prev->next = node->next;
      }	
  
      if(node->next == NULL) {
	list->tail = node->prev;
      } else {
	node->next->prev = node->prev;
      }

      // Decrementa la cantidad de nodos de la lista
      list->count--;
  
      // Libera la memoria del nodo eliminado
      free(node);
      ret = TRUE;

      break;
  
    }

    // Siguiente nodo de la lista
    node = node->next;

  }

  // Desactiva el mutex
  pthread_mutex_unlock(&(list->mutex));
  
  return ret;

}
  
