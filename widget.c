#include "widget.h"
#include <math.h>
#include "linklist.h"
#include <stdio.h>

//TODO widget sizes are hardcoded

int howManyDecimal(int num){
  if(num < 10){ //hardcoded
    return 1;

  }else if(num < 100){
    return 2;
  }else if(num < 1000){
    return 3;
  }else{
    return 4;
  }
};

int circularNumber(int num){  //TODO hardcoded
  //return the continuation of a circular number serie
  if(num >= 10000){
    return -10000 + (num % 9990);
  }else if(num <= -10000){
    return 10000 + (num % 9990);
  };
  return num;
};

bar* barInit(int height,int width,int x,int y,int parentWidth,int parentHeight){ //initialise a list
  bar* ptr = (bar*) malloc(sizeof(bar));	
  ptr->dimention[0] = height;
  ptr->dimention[1] = width;
  ptr->position[0] = x;
  ptr->position[1] = y;
  ptr->destroy = barDestroyer;
  ptr->parentDimention[0] = parentHeight;
  ptr->parentDimention[1] = parentWidth;

  ptr->data = listInit();
  for(int i = 0; i <ptr->dimention[0]; i++){
    for(int j = 0; j < ptr->dimention[1]; j++){
      if(i == 0 || i == ptr->dimention[0]-1){
        listAppend(ptr->data, '=');
      }else if(j == 0 || j == ptr->dimention[1]-1){
        listAppend(ptr->data, '=');
      }else{
        listAppend(ptr->data, '_');
      };
    };
    listAppend(ptr->data,'\n');
  };
  return ptr;
}

void barDestroyer(void* barra){
  bar* ptr = (bar*) barra;
  listDestroyer(ptr->data);
  free(ptr);
}

void barPrinter(void* barra){
  bar* ptr = (bar*) barra;
  listPrinter(ptr->data);
  return;
};

lineBar* lineBarInit(int width,int height,int x, int y,int start, int stop ,int parentWidth,int parentHeight){ //initialise a list
  lineBar* ptr = (lineBar*) malloc(sizeof(lineBar));	
  //hard coded for now
  ptr->dimention[0] = width;//jused 1y
  ptr->dimention[1] = height;
  ptr->position[0] = x; //x
  ptr->position[1] = y; //y
  ptr->destroy = lineBarDestroyer;
  ptr->update = lineBarUpdater;
  ptr->parentDimention[0] = parentHeight;
  ptr->parentDimention[1] = parentWidth;
  ptr->start = start;
  ptr->stop = stop;
  ptr->arrow = 0;
  ptr->data = listInit();
  int i = 0;
  char widgetDrawing[] = {"|    100| \n|       | \n|       | \n|     80| \n|       | \n|       | \n|     60| \n|       | \n|       | \n|     40| \n|       | \n|       | \n|     20| \n|       | \n|       | \n|      0| \n"};
  while(widgetDrawing[i] != '\0'){
    listAppend(ptr->data,widgetDrawing[i]);
    i = i +1;
  };
  return ptr;
}
void lineBarDestroyer(void* lineBarra){
  lineBar* ptr = (lineBar*) lineBarra;
  listDestroyer(ptr->data);
  free(ptr);
};

void lineBarUpdater(void* lineBarra, int arrow){
  //TODO still some part are hard coded have a look
  lineBar* ptr = (lineBar*) lineBarra;
  int temp = ptr->arrow;
  if (temp >= ptr->stop){
    temp = 99;
  }else if(temp <= ptr->start){
    temp = 1;
  };
  ptr->arrow = arrow;
  temp = 100-temp;
  temp =(int)( ((ptr->dimention[0])+1)*(ptr->dimention[1]*(temp)/100) + ptr->dimention[0]-1);
  listIndexUpdater(ptr->data,' ',temp);

  temp =arrow;
  if (temp >= ptr->stop){
    temp = 99;
  }else if(temp  <= ptr->start){
    temp = 1;
  };

  temp = 100-temp;
  temp =(int)( ((ptr->dimention[0])+1)*(ptr->dimention[1]*(temp)/100) + ptr->dimention[0]-1);
  listIndexUpdater(ptr->data,'<',temp);
  return;
};

lineCycle* lineCycleInit(int width, int height, int x, int y){
  lineCycle* ptr = (lineCycle*) malloc(sizeof(lineCycle));	
  //hard coded for now
  ptr->dimention[0] = width;
  ptr->dimention[1] = height;
  ptr->position[0] = x;
  ptr->position[1] = y;
  ptr->destroy = lineCycleDestroyer;
  ptr->update = lineCycleUpdater;
  ptr->arrow = 0.0;
  ptr->data = listInit();
  int i = 0;
  //TODO dynamically draw this widget drawing as it is hard coded
  char widgetDrawing[] = {"|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n|  |====||\n|<[00000||\n|  |====||\n|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n"};
  while(widgetDrawing[i] != '\0'){
    listAppend(ptr->data,widgetDrawing[i]);
    i = i +1;
  };
  return ptr;
};

void lineCycleDestroyer(void* lineCyclo){
  lineCycle* ptr = (lineCycle*) lineCyclo;
  listDestroyer(ptr->data);
  free(ptr);
  return;
};

void lineCycleUpdater(void* lineCyclo, int arrow){
  //TODO still some part are hard coded have a look
  lineCycle* ptr = (lineCycle*) lineCyclo;
  int position = 8; //location of arrow.. where  we put number //position hard coded
  int result;
  int skip = 0;
  int bars;
  int isNegative = 1; //-1 means it is negative, 1 means its positive
  int decrementModuloDecimal;

  for(int j = 0; j < ptr->dimention[1];j++){ //clear widget
    if(j == position-1 || j == position+1){
      //do not overwite the lineCycle's feature
    }else{
      for(int i = 0; i < 5; i++){
        listIndexUpdater(ptr->data,' ', j*(ptr->dimention[0]+1)+ 3+i);
      };
    };
  };
  //=======get circular number of the arrow and assign the design
  arrow = circularNumber(arrow);
  if(arrow < 0){
    isNegative = -1;
    listIndexUpdater(ptr->data,'-', position*(ptr->dimention[0]+1)+ 3);
    arrow = arrow*-1;
  };
  decrementModuloDecimal = pow(10,howManyDecimal(arrow));
  result = arrow;
  for(int i = 1; i < howManyDecimal(arrow)+1; i++){
    result =(int)(result % decrementModuloDecimal);
    decrementModuloDecimal = decrementModuloDecimal /10;
    listIndexUpdater(ptr->data,result/decrementModuloDecimal+'0', position*(ptr->dimention[0]+1)+ 3+i);
  };
  arrow = arrow*isNegative;
  isNegative = 1;

  if(arrow<0){
    bars = circularNumber( arrow - (( arrow % 10))+ 40);
    if(arrow % 10 <= -5){
      skip = 1;
      bars = circularNumber(bars - 10);
    };
  }else{
    bars = circularNumber(arrow - (( arrow % 10))+ 40);
    if(arrow % 10 >= 5){
      skip = 1;
    };
  };

  for(int i = skip; i < ptr->dimention[1];i = i+2){ //Populate the rest of the bar
    if(i == position || i == position-1 || i == position+1){ //do not populate the widget designed
    }else{//populate the spaces
      //====
      if(bars < 0){
        isNegative = -1;
        listIndexUpdater(ptr->data,'-', i*(ptr->dimention[0]+1)+ 3);
        bars = bars*-1;
      };
      decrementModuloDecimal = pow(10,howManyDecimal(bars));
      result = bars;
      for(int j = 1; j < howManyDecimal(bars)+1; j++){
        result =circularNumber((int)(result % decrementModuloDecimal));
        decrementModuloDecimal = decrementModuloDecimal /10;
        listIndexUpdater(ptr->data,result/decrementModuloDecimal+'0', i*(ptr->dimention[0]+1)+ 3+j);
      };
      bars = bars*isNegative;
      isNegative = 1;
      //====
    };
    bars = circularNumber(bars - 10);
  };
};

fuelWidget* fuelWidgetInit(int width, int height, int x, int y){
  /*
  fuelWidget* ptr = (fuelWidget*) malloc(sizeof(fuelWidget));	
  //hard coded for now
  ptr->dimention[0] = width; //x
  ptr->dimention[1] = height; //y
  ptr->position[0] = x;
  ptr->position[1] = y;
  ptr->arrow = 0.0;
  ptr->data = listInit();
  int i = 0;
  //TODO dynamically draw this widget drawing as it is hard coded
  char widgetDrawing[] = {"|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n|  |====||\n|<[00000||\n|  |====||\n|        |\n|        |\n|        |\n|        |\n|        |\n|        |\n"};
  while(widgetDrawing[i] != '\0'){
    listAppend(ptr->data,widgetDrawing[i]);
    i = i +1;
  };
  return ptr;*/

};

screen* screenInit(int width, int height){
  screen* ptr = (screen*) malloc(sizeof(screen));
  ptr->dimention[0]= width;
  ptr->dimention[1] = height;
  ptr->data = listInit();
  ptr->destroy = screenDestroyer;
  for(int i = 0;i < ptr->dimention[1]; i++){
    for(int j = 0; j < ptr->dimention[0]; j++){
      if (i == 0 || j == 0 || i == ptr->dimention[1]-1 || j == ptr->dimention[0]-1){
        listAppend(ptr->data,'x');
      }else{
        listAppend(ptr->data,'_');
      };
    };
      listAppend(ptr->data,'\n');
  };
  return ptr;
};

void screenDestroyer(void* screenG){
  screen* ptr = (screen*) screenG;
  listDestroyer(ptr->data);
  free(ptr);
};

void screenClearer(void* screenG){ //clear all widget
  screen* ptr = (screen*) screenG;
  for(int i = 1;i < ptr->dimention[1]-1; i++){
    for(int j = 1; j < ptr->dimention[0]-1; j++){
      listIndexUpdater(ptr->data,' ',(i*(ptr->dimention[0]+1)+j));
    };
  };
};

void screenRenderer(void* widget, void* screenG){ //display widget into the screen
  genericWidget* ptrWidget = (genericWidget*) widget;
  screen* ptrScreen = (screen*) screenG;
  for(int i = 0; i < ptrWidget->dimention[1]; i++){
    for(int j = 0; j < ptrWidget->dimention[0]; j++){
      if( listGetIndexValue(ptrWidget->data,i*(ptrWidget->dimention[0]+1)+j) != '\n' &&  
          listGetIndexValue(ptrScreen->data,i*(ptrScreen->dimention[0]+1)+j) != '\n'){
        listIndexUpdater(ptrScreen->data,listGetIndexValue(ptrWidget->data,i*(ptrWidget->dimention[0]+1)+j),
            ((i+ptrWidget->position[1]+1)*(ptrScreen->dimention[0]+1)+(j+(ptrWidget->position[0])+1)));
      };
    };
  };
};
 
void screenWidgetClearer(void* widget, void* screenG){ //clear the specified widget
  genericWidget* ptrWidget = (genericWidget*) widget;
  screen* ptrScreen = (screen*) screenG;
  for(int i = 0; i < ptrWidget->dimention[1]; i++){
    for(int j = 0; j < ptrWidget->dimention[0]; j++){
      if( listGetIndexValue(ptrWidget->data,i*(ptrWidget->dimention[0]+1)+j) != '\n' &&  
          listGetIndexValue(ptrScreen->data,i*(ptrScreen->dimention[0]+1)+j) != '\n'){
        listIndexUpdater(ptrScreen->data,' ',
            ((i+ptrWidget->position[1]+1)*(ptrScreen->dimention[0]+1)+(j+(ptrWidget->position[0])+1)));
      };
    };
  };
};
 
