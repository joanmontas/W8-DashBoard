/***************************************************************/
/* Programmer: Joan Montas                                     */
/*                                                             */
/* Program 1: A stupid little vector w8 inspired system monitor*/
/*                                                             */
/* Approximate completion time:   15 minutes                   */
/***************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "linklist.h"
#include "widget.h"
#include <time.h>
#include <termios.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  //This function disable cannonical aka coocked mode...so no Enter is required
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1){
    die("tcgetattr");
  };
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0; //minimum number of byte needed before read
  raw.c_cc[VTIME] = 1; //maximum amount of time to wait before read(); ... 1/10 of a second aka 100 millisecond
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){ 
    die("tcsetattr");
  };
}

void yellow() { //normal color
  printf("\033[1;33m");
}

void red () { //incognito color
  printf("\033[1;31m");
}

void resetColor() {
  printf("\033[0m");
}

void handler(int num){
  printf("Closing %d\n",num);
};

struct getInputParam{
  /* The character to print.  */
  screen* screenDisplay;/* The number of times to print it.  */
  list* keyboardInput;
  int finish;
  int cursor;
};

void* getInputThread(void* parameters){
  //should receive voidLinkList with all variables that we need to operate on
  struct getInputParam* p = (struct getInputParam*) parameters;
  while(p->finish == 0){
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){ //if keyboard was pressed and no error occured
      die("read");
    };

    if (iscntrl(c)) { //handle for keyboard command.
      if(c == 127 && (p->keyboardInput)->size > 1 ){ //backspace
        listPop(p->keyboardInput,p->cursor-1);
        p->cursor--;
        system("clear");
        listPrinter(p->screenDisplay->data);
        printf("\r\n");
        listPrinter(p->keyboardInput);
        printf("\r\n");
      }else{ //else if handle for enter... clear the buffer and check if the command is present

      };
    } else { //handle keyboard
        if(c == 91 ){ //handle arrow... arrow are composed of 2 char
          if( (p->keyboardInput)->size > 2){
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){ //get the following char indicating which bottom
              die("read");
            };
            printf("xxxxxxxxxxxxxxxxxxxxx%d \r\n",p->cursor);
            if(c == 68 ){ //handle for cursor != 0
              system("clear");
              listPop(p->keyboardInput,p->cursor);
              listInsert(p->keyboardInput,'|',p->cursor-1);
              p->cursor--;
              listPrinter(p->screenDisplay->data);
              printf("\r\n");
              listPrinter(p->keyboardInput);
              printf("\r\n");
            }else if(c == 67 && p->cursor < (p->keyboardInput)->size){ //handle for cursor != size of buffer + 1
              system("clear");
              listPop(p->keyboardInput,p->cursor);
              listInsert(p->keyboardInput,'|',p->cursor+1);
              p->cursor++;
              listPrinter(p->screenDisplay->data);
              printf("\r\n");
              listPrinter(p->keyboardInput);
              printf("\r\n");
            };
          }else{
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){ //get the following char indicating which bottom
              die("read");
            };
          };
        }else{
          system("clear");
          listInsert(p->keyboardInput,c,p->cursor);
          p->cursor++;
          listPrinter(p->screenDisplay->data);
          printf("\r\n");
          listPrinter(p->keyboardInput);
          printf("\r\n");
          printf("xxxxxxxxxxxxxxxxxxxxx%d \r\n",p->cursor);
          printf("\r\n");
        };
    }

    //handle for simple command onced complex command has been activated
    if (c == 'r'){
      red();
    };

    if (c == 'y'){
      yellow();
    };

    if (c == 'q'){
      break;
    };

  };
  printf("finishing...");
  p->finish = 1;
};

int main(int argc,char *argv[]){
  //rsignal(SIGUSR1,hadler);  // kill -SIGSR1 PID

  int i = 0;
  int cursor = 0;

  int dimention[] = {120,30};

  genericWidget* ptr;

  //screen and keyboard and widget
  screen* screenView = screenInit(dimention[0],dimention[1]);
  list* keyboardDisplay = listInit();
  list* widgetList = listInit();

  listAppend(keyboardDisplay,'|');

  //parameter for the input thread
  struct getInputParam InputParameters;
  InputParameters.screenDisplay = screenView;
  InputParameters.keyboardInput = keyboardDisplay;
  InputParameters.finish = 0;
  InputParameters.cursor = 0;

  //initialize basic widget
  listAppendVoid(widgetList,lineCycleInit(10,16,0,0));
  listAppendVoid(widgetList,lineCycleInit(10,16,15,0));
  listAppendVoid(widgetList,lineCycleInit(10,16,30,0));
  listAppendVoid(widgetList,lineCycleInit(10,16,45,0));
  listAppendVoid(widgetList,lineCycleInit(10,16,45,0));
  listAppendVoid(widgetList,lineBarInit(10,16,60,0,0,100,10,10));

  enableRawMode();
  yellow();

  //run the input thread
  pthread_t thread1_id;
  pthread_create (&thread1_id, NULL, &getInputThread, &InputParameters);

  while(InputParameters.finish == 0){

    //loop and update all widget
    for(int ii = 0; ii < widgetList->size ; ii++ ){
      ptr = (genericWidget*) listGetIndexValueVoid(widgetList,ii);
      ptr->update(ptr,i);
      screenRenderer(listGetIndexValueVoid(widgetList,ii),screenView);
    };

    //display
    system("clear");
    listPrinter(screenView->data);
    printf("\r\n");
    listPrinter(keyboardDisplay);
    printf("\r\n");
    i++;
    sleep(1);
  };

  //end input thread.. and wait for it to finish
  InputParameters.finish = 1;
  pthread_join (thread1_id, NULL);

  //loop through all widget and destroy
  for(int ii = 0; ii < widgetList->size ; ii++ ){
    ptr = (genericWidget*) listGetIndexValueVoid(widgetList,ii);
    ptr->destroy(ptr);
  };

  listDestroyer(keyboardDisplay);
  screenDestroyer(screenView);
  listDestroyer(widgetList);

  //reset color and keyboard
  resetColor();

  disableRawMode();

  return 0;
}
