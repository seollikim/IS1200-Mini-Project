/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2023-03-02 by Andrej Miladinovic and Seolli Kim

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "blob.h"  /* Declatations for blob game */
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
// Starting point for the blob
int blobx = 15;
int bloby = 30;
// Starting point for candy
int candyx = 20;
int candyy = 15;
// direction of the blob
int direction = 4;
//x and y for random spawning
int rx = 0;
int ry = 0;

int i,j;

// starting point for bump
int bumpsx = 10;
int bumpsy = 50;

int bumpsx2 = 25;
int bumpsy2 = 100;

int bumpsx3 = 5;
int bumpsy3 = 10;




// arrays for the x and y cordinate for spawning random places for the candy after consumation
int randomarrayX[10] = {22, 40, 91, 90, 10, 65, 93, 74, 67, 13};
int randomarrayY[10] = {18, 7, 21, 16, 13, 14, 19, 17, 20, 15};


//Change of direction of the blob 
void set_direction(int n){ 
    switch (n) {
        case 1:
            bloby--;
            
            break;
        case 2:
            blobx--;
            
            break;
        case 3:
            blobx++;
            
            break;
        case 4:
            bloby++;
            
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

  // Starting place for blob
  blobx = 15;
  bloby = 30;

  // Starting point for candy
  candyx = 15;
  candyy = 60;

  return;
}

void clear_screen() { // clearing the screen
  for (i = 0; i < 32; i++) {
    for ( j = 0; j < 128; j++) {
      game[i][j] = 0;
    }
  }
}

/*void tail(blobx, bloby) {

 for(int j = position; j < length; j++){
  tailx[position] = blobx;
  taily[position] = bloby;
  game[taily][tailx] = 1;
 }

}*/




void blob(blobx, bloby) { 
  // initialization so that the blob is shown on the play
  
  game[blobx][bloby] = 1;
  game[blobx][bloby+1] = 1;
  game[blobx][bloby+2] = 1;
  game[blobx][bloby+3] = 1;
  game[blobx][bloby+4] = 1;

  game[blobx+1][bloby] = 1;
  game[blobx+1][bloby+1] = 1;
  game[blobx+1][bloby+2] = 1;
  game[blobx+1][bloby+3] = 1;
  game[blobx+1][bloby+4] = 1;

  game[blobx+2][bloby] = 1;
  game[blobx+2][bloby+1] = 1;
  game[blobx+2][bloby+2] = 1;
  game[blobx+2][bloby+3] = 1;
  game[blobx+2][bloby+4] = 1;

  game[blobx+3][bloby] = 1;
  game[blobx+3][bloby+1] = 1;
  game[blobx+3][bloby+2] = 1;
  game[blobx+3][bloby+3] = 1;
  game[blobx+3][bloby+4] = 1;

  game[blobx+4][bloby] = 1;
  game[blobx+4][bloby+1] = 1;
  game[blobx+4][bloby+2] = 1;
  game[blobx+4][bloby+3] = 1;
  game[blobx+4][bloby+4] = 1;

}

void bump (bumpsx, bumpsy) {
  game[bumpsx][bumpsy] = 1;
  game[bumpsx][bumpsy+1] = 1;
  game[bumpsx][bumpsy+2] = 1;
  game[bumpsx][bumpsy+3] = 1;
  game[bumpsx][bumpsy+4] = 1;

  game[bumpsx+1][bumpsy] = 1;
  game[bumpsx+1][bumpsy+1] = 1;
  game[bumpsx+1][bumpsy+2] = 1;
  game[bumpsx+1][bumpsy+3] = 1;
  game[bumpsx+1][bumpsy+4] = 1;

  game[bumpsx+2][bumpsy] = 1;
  game[bumpsx+2][bumpsy+1] = 1;
  game[bumpsx+2][bumpsy+2] = 1;
  game[bumpsx+2][bumpsy+3] = 1;
  game[bumpsx+2][bumpsy+4] = 1;

  game[bumpsx+3][bumpsy] = 1;
  game[bumpsx+3][bumpsy+1] = 1;
  game[bumpsx+3][bumpsy+2] = 1;
  game[bumpsx+3][bumpsy+3] = 1;
  game[bumpsx+3][bumpsy+4] = 1;

  game[bumpsx+4][bumpsy] = 1;
  game[bumpsx+4][bumpsy+1] = 1;
  game[bumpsx+4][bumpsy+2] = 1;
  game[bumpsx+4][bumpsy+3] = 1;
  game[bumpsx+4][bumpsy+4] = 1;

  game[bumpsx+5][bumpsy] = 1;
  game[bumpsx+5][bumpsy+1] = 1;
  game[bumpsx+5][bumpsy+2] = 1;
  game[bumpsx+5][bumpsy+3] = 1;
  game[bumpsx+5][bumpsy+4] = 1;

  game[bumpsx+6][bumpsy] = 1;
  game[bumpsx+6][bumpsy+1] = 1;
  game[bumpsx+6][bumpsy+2] = 1;
  game[bumpsx+6][bumpsy+3] = 1;
  game[bumpsx+6][bumpsy+4] = 1;
}

void candy(candyx, candyy){
  game[candyx][candyy+2] = 1;

   game[candyx+1][candyy+1] = 1;
   game[candyx+1][candyy+3] = 1;

   game[candyx+2][candyy] = 1;
   game[candyx+2][candyy+4] = 1;

   game[candyx+3][candyy+1] = 1;
   game[candyx+3][candyy+3] = 1;
   game[candyx+4][candyy+2] = 1;
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

  // making blob and candy
  blob(blobx, bloby);
  candy(candyx, candyy);
  bump(bumpsx, bumpsy);
  bump(bumpsx2, bumpsy2);
  bump(bumpsx3, bumpsy3);
  //bumps(bumpsx2, bumpsy2);
  //sbumps(bumpsx3, bumpsy3);

  // Movement of blob
  // moving left
  if (button1 & 0x01 && (blobx > 1) && direction != 4) {
    direction = 1;
  }
  // moving down
  if (buttons & 0x04 && (bloby > 1) && direction != 3) {
    direction = 2;
  }
  // moving up
  if (buttons & 0x02 && (bloby+4) < 126 && direction != 2) {
    direction = 3;
  }
  // moving right
  if (buttons & 0x01 && (blobx+4) < 30 && direction != 1) {
    direction = 4; 
  }

  set_direction(direction);

  // When blob goes to wall
  if ((bloby+4) >= 126 || bloby <= 1 || (blobx+4) >= 30 || blobx <= 1) {
    state = 4;
  }

  // When blob eats candy
  if (((blobx+2 <= candyx+4) && (blobx+2 >= candyx)) && ((bloby+2 <= candyy+4) && (bloby+2 >= candyy))) {
    candyy = randx();
    candyx = randy();
    pointscounter++;
  }

   //When blob hits bumps
  if (((blobx <= bumpsx+6) && (blobx+4 >= bumpsx)) && ((bloby <= bumpsy+6) && (bloby+4 >= bumpsy))) {
    state = 4;
  }

  if (((blobx <= bumpsx2+6) && (blobx+4 >= bumpsx2)) && ((bloby <= bumpsy2+6) && (bloby+4 >= bumpsy2))) {
    state = 4;
  }

  if (((blobx <= bumpsx3+6) && (blobx+4 >= bumpsx3)) && ((bloby <= bumpsy3+6) && (bloby+4 >= bumpsy3))) {
    state = 4;
  }

  display_pixel();


  }

 