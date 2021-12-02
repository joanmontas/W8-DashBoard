#ifndef LINKLIST_H
#define LINKLIST_H
struct Cell{ //vector instead of struct Vector
    char dataType[10]; //data type, so we know how to interact
	char data;   //modified to be character 
    int color; //default color is green
	int capacity;  //max capacity it can hold
	int size;      //current entire capacity
	struct Cell* next;
	struct Cell* previous;
    void* data2;

};
typedef struct Cell cell;

struct List{  //struct to keep track of underlying cell structure
  int size;
  cell* head;
  cell* tail;
  void (*print)(void * lista);
  void (*destroy)(void * lista);

};
typedef struct List list;

list* listInit(void);
void listDestroyer(void* lista);
void listAppend(void *lista,char strinG);
cell* cellInit(char ch);
void listPrinter(list* lista);
void listInsert(list* lista, char strinG,int location);
char listPop(list* lista, int location);
char listGetIndexValue(list* lista, int index);
char listIndexUpdater( list* lista, char ch ,int index);
//void pointer data2
void listInsertVoid(list* lista, void* strinG,int location);
void* listPopVoid(list* lista, int location);
void listAppendVoid(void *lista, void* strinG);
cell* cellInitVoid(void* ch);
void* listGetIndexValueVoid(list* lista, int index);
#endif
