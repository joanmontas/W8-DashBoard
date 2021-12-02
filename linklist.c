/***************************************************************/
/* Programmer: Joan Montas                                     */
/*                                                             */
/* Program 1: List data structure implementation               */
/*                                                             */
/* Approximate completion time:   15 minutes                   */
/***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

list* listInit(void){ //initialise a list
	list* ptr = (list*) malloc(sizeof(list));	
	ptr->size = 0;
	ptr->head = NULL;
	ptr->tail = NULL;
    ptr->print = listPrinter;
    ptr->destroy = listDestroyer;
	return ptr;
}
void listDestroyer(void* lista){ //destroy list
	list* ptr = (list*) lista;
	if((ptr->head) == NULL){ //if head is empty 
		free(ptr);	//just free list
		return;
	};
	cell* ptr1;
	// we will free from tail to head, tail will point to head once
	while(1){
		if(ptr-> tail == NULL){ //tail isempty
			free(ptr); //free the list
			return;
		}else{
			ptr1 = ptr->tail; //point to tail/ last node
			ptr->tail = (ptr->tail)->previous; //tail points to tail's previous
			free(ptr1); //free last node
		};
	};
}


void listAppend(void *lista, char strinG){ //add new node/cell at the end
	list* ptr = (list*) lista;
	if(ptr->head == NULL){ //if list is empty
		ptr->head = cellInit(strinG); //create new node
		ptr->tail = ptr->head; //tail points to new node
		ptr->size = ptr->size+1; //increase size by one
		return;
	};
	(ptr->tail)->next = cellInit(strinG); //add new cell
	((ptr->tail)->next)->previous = (ptr->tail); //new cell's previous
						    //points to previous
	ptr->tail = (ptr->tail)->next; //tail points to new cell
	ptr->size = ptr->size+1; //increase size by one
}

cell* cellInit(char ch){ //initialize a cell
	cell* ptr = (cell*)malloc(sizeof(cell)); //malloc space
	ptr->next = NULL; 
	ptr->previous = NULL;
	ptr->size = 0;
    ptr->color = -1; //default color
	ptr->capacity = 5;
	ptr->data = ch;
	return ptr;
}

void listPrinter(list* lista){ //print list from headto tail
	list* ptr = (list*) lista;
	if(ptr->size == 0){
		return;
	};

	cell* ptr1 = ptr->head; //point to head of lista
	while(ptr1->next != NULL){
      if(ptr1->data == '\n'){
        printf("\r\n");
      }else{
	    printf("%c",ptr1->data);
      };
		ptr1 = ptr1->next; //point to next node
	};
	printf("%c",ptr1->data);
}

void listInsert(list* lista,char strinG,int location){
	list* ptr = (list*) lista;
	if(location >= ptr->size ){
		printf("Index out of range failed to insert\n");
		return;
	};

	if(location == 0){ //if we are appending at the beginning
		cell* temp = cellInit(strinG);
		temp->next = (ptr->head);
		(ptr->head)->previous = temp;
		ptr->head = temp;
		ptr->size = ptr->size+1;
		return;
	};

	cell* temp = cellInit(strinG); //create new node
	cell* ptr1 = ptr->head; //pointer to iterate list
	for(int i = 0; i < location-1; i ++){ //look for the node to be poped
		ptr1 = ptr1->next;
	};

	if(ptr1->next == NULL){ //if we are inserting at the end of the linklist
		ptr1->next = temp;
		temp->previous = ptr1;
		ptr->size = ptr->size+1;
		temp->next = NULL;
		ptr->tail = temp;
		return;
	};

	temp->next = ptr1->next;     //if we are appending the middle
	(ptr1->next)->previous = temp;
	temp->previous = ptr1;
	ptr1->next = temp;
	ptr->size = ptr->size+1;
};

char listPop(list* lista, int location){ //pop the nth cell
    //it is up to the user that the list is valid!!!! 
	list* ptr = (list*) lista;
	char tmpChar =  (ptr->head)->data;

	if(location > (ptr->size)-1  || location < 0){
		printf("Noped, Not such index\n");
        exit(1);
	};
	if(location == 0 && (ptr->size) == 1){ //if we pop the only  one node
		free(ptr->head);
		ptr->head = NULL;
		ptr->tail = NULL;
		ptr->size = 0;
        return tmpChar;
	};
	cell* ptr1 = ptr->head; //cell pointer to head's cell
	for(int i = 0; i < location; i++){ //look for the node to be poped
		ptr1 = ptr1->next;
	};

    if(location == 0){ //head
      ptr->head = (ptr->head)->next;
      (ptr->head)->previous = NULL;
      free(ptr1);
    }else if(location == ptr->size-1){ //tail
      ptr->tail = (ptr->tail)->previous;
      (ptr->tail)->next = NULL;
      free(ptr1);
    }else{                              //if between
      (ptr1->next)->previous = ptr1->previous;
      (ptr1->previous)->next = ptr1->next;
      free(ptr1);
    };
    ptr->size = ptr->size - 1;
    return tmpChar;
};

char listGetIndexValue(list* lista, int index){
  	list* ptr = (list*) lista;
	if(ptr->size == 0){
      printf("Out Of Range!");
      exit(1);
	};

	cell* ptr1 = ptr->head; //point to head of lista
    for(int i = 0; i < index; i++){ //lets account
      ptr1 = ptr1->next;
    };
    return ptr1->data;

};

char listIndexUpdater( list* lista, char ch ,int index){
  list* ptr = (list*) lista;
  if(index >= lista->size){
    printf("Out Of Range!");
    exit(1);
  };

  cell* ptr1 = ptr->head; //point to head of lista
  for(int i = 0; i < index; i++){ //lets account
    ptr1 = ptr1->next;
  };
  char tmp = ptr1->data;
  ptr1->data = ch;
  return tmp;
};

cell* cellInitVoid(void* ch){ //initialize a cell
	cell* ptr = (cell*)malloc(sizeof(cell)); //malloc space
	ptr->next = NULL; 
	ptr->previous = NULL;
	ptr->size = 0;
    ptr->color = -1; //default color
	ptr->capacity = 5;
	ptr->data2 = ch;
	return ptr;
}

void listInsertVoid(list* lista, void* strinG,int location){
	list* ptr = (list*) lista;
	if(location >= ptr->size ){
		printf("Index out of range failed to insert\n");
		return;
	};

	if(location == 0){ //if we are appending at the beginning
		cell* temp = cellInitVoid(strinG);
		temp->next = (ptr->head);
		(ptr->head)->previous = temp;
		ptr->head = temp;
		ptr->size = ptr->size+1;
		return;
	};

	cell* temp = cellInitVoid(strinG); //create new node
	cell* ptr1 = ptr->head; //pointer to iterate list
	for(int i = 0; i < location-1; i ++){ //look for the node to be poped
		ptr1 = ptr1->next;
	};

	if(ptr1->next == NULL){ //if we are inserting at the end of the linklist
		ptr1->next = temp;
		temp->previous = ptr1;
		ptr->size = ptr->size+1;
		temp->next = NULL;
		ptr->tail = temp;
		return;
	};

	temp->next = ptr1->next;     //if we are appending the middle
	(ptr1->next)->previous = temp;
	temp->previous = ptr1;
	ptr1->next = temp;
	ptr->size = ptr->size+1;
};

void* listPopVoid(list* lista, int location){
	list* ptr = (list*) lista;
	void* tmpChar =  (ptr->head)->data2;

	if(location > (ptr->size)-1  || location < 0){
		printf("Noped, Not such index\n");
        exit(1);
	};
	if(location == 0 && (ptr->size) == 1){ //if we pop the only  one node
		free(ptr->head);
		ptr->head = NULL;
		ptr->tail = NULL;
		ptr->size = 0;
        return tmpChar;
	};
	cell* ptr1 = ptr->head; //cell pointer to head's cell
	for(int i = 0; i < location; i++){ //look for the node to be poped
		ptr1 = ptr1->next;
	};

    if(location == 0){ //head
      ptr->head = (ptr->head)->next;
      (ptr->head)->previous = NULL;
      free(ptr1);
    }else if(location == ptr->size-1){ //tail
      ptr->tail = (ptr->tail)->previous;
      (ptr->tail)->next = NULL;
      free(ptr1);
    }else{                              //if between
      (ptr1->next)->previous = ptr1->previous;
      (ptr1->previous)->next = ptr1->next;
      free(ptr1);
    };
    ptr->size = ptr->size - 1;
    return tmpChar;
};

void listAppendVoid(void *lista, void* strinG){
	list* ptr = (list*) lista;
	if(ptr->head == NULL){ //if list is empty
		ptr->head = cellInitVoid(strinG); //create new node
		ptr->tail = ptr->head; //tail points to new node
		ptr->size = ptr->size+1; //increase size by one
		return;
	};
	(ptr->tail)->next = cellInitVoid(strinG); //add new cell
	((ptr->tail)->next)->previous = (ptr->tail); //new cell's previous
						    //points to previous
	ptr->tail = (ptr->tail)->next; //tail points to new cell
	ptr->size = ptr->size+1; //increase size by one

};

void* listGetIndexValueVoid(list* lista, int index){
  list* ptr = (list*) lista;
	if(ptr->size == 0){
      printf("Out Of Range!");
      exit(1);
	};

	cell* ptr1 = ptr->head; //point to head of lista
    for(int i = 0; i < index; i++){ //lets account
      ptr1 = ptr1->next;
    };
    return ptr1->data2;
};

