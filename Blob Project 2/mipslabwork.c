/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2023-03-02 by Andrej Miladinovic and Seolli Kim

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "snake.h"  /* Declatations for snake game */
#include <stdio.h>
#include <stdlib.h>

int mytime = 0x5957;
volatile int *led = (volatile int*) 0xbf886100;
volatile int *port = (volatile int*) 0xbf886110;
int timeoutcount = 0;
int count = 0;

char textstring[] = "text, more text, and even more text!";

//Written by Andrej and Seolli
// global variables
int pointscounter = 0; // counting for points
// Starting point for the snake
int snakex = 15;
int snakey = 30;
// Starting point for apple
int applex = 20;
int appley = 15;
// direction of the snake
int direction = 4;
//x and y for random spawning
int rx = 0;
int ry = 0;

int i,j;

// arrays for the x and y cordinate for spawning random places for the apple after consumation
int randomarrayX[10] = {22, 47, 103, 99, 10, 55, 93, 74, 67, 13};
int randomarrayY[10] = {22, 9, 3, 16, 13, 14, 19, 21, 5, 7};


//Change of direction of the snake 
void set_direction(int n){ // 
    switch (n) {
        case 1:
            snakey--;
            break;
        case 2:
            snakex--;
            break;
        case 3:
            snakex++;
            break;
        case 4:
            snakey++;
            break;
            
        default:
            break;
    }
}



/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

int randx(void) { 
  int r;
  if (rx == 10) {
    rx = 0;
  }
  if (rx < 10) {
    r = randomarrayX[rx];
  }
  rx++;

  return r;
}

int randy(void) {
  int r;
  if (ry == 10) {
    ry = 0;
  }
  if (ry < 10) {
    r = randomarrayY[ry];
  }
  ry++;

  return r;
}

/* Lab-specific initialization goes here */
void labinit( void ) //From lab 3
{
  *led &= 0xffffff00;
  *port &= 0xffffff00;

  TRISD &= 0xfe0; // inputs 

  // resetting the variables
  i = 0;
  j= 0;
  
  pointscounter = 0;

  direction = 4;

  // Starting place for snake
  snakex = 15;
  snakey = 30;

  // Starting point for apple
  applex = 15;
  appley = 60;

  return;
}

void clear_screen() { // clearing the screen
  for (i = 0; i < 32; i++) {
    for ( j = 0; j < 128; j++) {
      game[i][j] = 0;
    }
  }
}

void snake(snakex, snakey) { // initialization so that the snake is shown on the play
  game[snakex][snakey] = 1;
  game[snakex][snakey+1] = 1;
  game[snakex][snakey+2] = 1;
  game[snakex][snakey+3] = 1;
  game[snakex][snakey+4] = 1;

  game[snakex+1][snakey] = 1;
  game[snakex+1][snakey+1] = 1;
  game[snakex+1][snakey+2] = 1;
  game[snakex+1][snakey+3] = 1;
  game[snakex+1][snakey+4] = 1;

  game[snakex+2][snakey] = 1;
  game[snakex+2][snakey+1] = 1;
  game[snakex+2][snakey+2] = 1;
  game[snakex+2][snakey+3] = 1;
  game[snakex+2][snakey+4] = 1;

  game[snakex+3][snakey] = 1;
  game[snakex+3][snakey+1] = 1;
  game[snakex+3][snakey+2] = 1;
  game[snakex+3][snakey+3] = 1;
  game[snakex+3][snakey+4] = 1;

  game[snakex+4][snakey] = 1;
  game[snakex+4][snakey+1] = 1;
  game[snakex+4][snakey+2] = 1;
  game[snakex+4][snakey+3] = 1;
  game[snakex+4][snakey+4] = 1;
}

void apple(applex, appley){
  game[applex][appley+2] = 1;

   game[applex+1][appley+1] = 1;
   game[applex+1][appley+3] = 1;

   game[applex+2][appley] = 1;
   game[applex+2][appley+4] = 1;

   game[applex+3][appley+1] = 1;
   game[applex+3][appley+3] = 1;
   game[applex+4][appley+2] = 1;
}

void wall() { // the edges for the game, we basically make a frame for the edges so that it is easier to see the playing
  for (i = 0; i< 32; i++) {
    game[i][0] = 1;
    game[i][127] = 1;
  }
  for (j = 0; j < 128; j++) {
    game[0][j] = 1;
    game[31][j] = 1;
  }
}
/* This function is called repetitively from the main program */
void labwork( void )
{
  delay (50);
  clear_screen();

  int buttons = getbtns();
  int button1 = getbtn1();

  wall(); // Drawing the walls 

  // making snake and apple
  snake(snakex, snakey);
  apple(applex, appley);

  // Movement of snake
  // moving left
  if (button1 & 0x01 && (snakex > 1) && direction != 4) {
    direction = 1;
  }
  // moving down
  if (buttons & 0x04 && (snakey > 1) && direction != 3) {
    direction = 2;
  }
  // moving up
  if (buttons & 0x02 && (snakey+4) < 126 && direction != 2) {
    direction = 3;
  }
  // moving right
  if (buttons & 0x01 && (snakex+4) < 30 && direction != 1) {
    direction = 4; 
  }

  set_direction(direction);

  // When snake goes to wall
  if ((snakey+4) >= 126 || snakey <= 1 || (snakex+4) >= 30 || snakex <= 1) {
    state = 4;
  }

  // When snake eats apple
  if (((snakex+2 <= applex+4) && (snakex+2 >= applex)) && ((snakey+2 <= appley+4) && (snakey+2 >= appley))) {
    appley = randx();
    applex = randy();
    pointscounter++;
  }

  display_pixel();


  }

 