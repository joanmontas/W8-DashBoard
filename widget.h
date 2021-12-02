#ifndef WIDGET_H
#define WIDGET_H
#include <stdlib.h>
#include "linklist.h"
#include <math.h>
//dimention = shape of widget
//position = location in screen
//data = the thing being render in the screen
struct GenericWidget{ //used as a template for unkown widgets
  int dimention[2]; //x,y... width,height
  int position[2];  //x,y... width,height
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
};
typedef struct GenericWidget genericWidget;

struct Bar{ //vector instead of struct Vector
  int dimention[2];
  int position[2];
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
  int parentDimention[2];
  void* next;//could be use inthe future as parant and child iwdget
  void* previous;
};
typedef struct Bar bar;
bar* barInit(int height,int width,int x,int y,int parentWidth,int parentHeight);
void barDestroyer(void* barra);
void barPrinter(void* barra);

struct LineBar{
  int dimention[2];
  int position[2];
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
  int parentDimention[2];
  void* next;//could be use inthe future as parant and child iwdget
  void* previous;
  int start;
  int stop;
  int arrow;
};
typedef struct LineBar lineBar;
lineBar* lineBarInit(int width,int height,int x, int y,int start, int stop ,int parentWidth,int parentHeight);
void lineBarDestroyer(void* lineBarra);
void lineBarUpdater(void* lineBarra, int arrow);

struct LineBarCycle{
  int dimention[2];
  int position[2];
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
  int parentDimention[2];
  void* next;//could be use inthe future as parant and child iwdget
  void* previous;
  int array;
  double arrow;
};
typedef struct LineBarCycle lineCycle;
lineCycle* lineCycleInit(int width, int height, int x, int y);
void lineCycleDestroyer(void* lineCyclo);
void lineCycleUpdater(void* lineCyclo, int arrow);


struct FuelWidget{
  int dimention[2];
  int position[2];
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
};
typedef struct FuelWidget fuelWidget;
fuelWidget* fuelWidgetInit(int width, int height, int x, int y);
void fuelWidgetDestroyer(void* widget); 

struct Screen{
  int dimention[2];
  int position[2];
  list *data;
  void (*destroy)(void* widget);
  void (*update)(void* widget, int arrow);
};
typedef struct Screen screen;
screen* screenInit(int width, int height);
void screenDestroyer(void* screen);
void screenClearer(void* screenG);
void screenRenderer(void* widget, void* screenG);
void screenWidgetClearer(void* widget, void* screenG);
#endif

