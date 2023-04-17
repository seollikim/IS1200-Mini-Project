#include <stdint.h>
#include <pic32mx.h>
#include "snake.h"  /* Declatations for snake game */
// This file created 2023-03-02 by Andrej Miladinovic and Seolli Kim
int getsw(void)
{
    int sw = (PORTD >> 8) &0x000f; // bits 11-8 reads value on sw 
    return sw;
}

int getbtns(void)
{
    int btns = (PORTD >> 5) & 0x07; // reading bits 5-7
    return btns;
}

int getbtn1(void){ //For use of using button 1
    
    return ((PORTF >> 1) & 0x1);
}