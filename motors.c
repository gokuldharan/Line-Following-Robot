#include "constants.h"
#include "main.h"
#include <xc.h>

void setleftmotor(unsigned int val) {   //1 forward, 2 reverse PWM2 left, PWM1 right
    if (val==1) {  
        LATCbits.LC0 = 1;
        LATCbits.LC3 = 0;
    } else if (val==2) {
        LATCbits.LC0 = 0;
        LATCbits.LC3 = 1;
    }
}

void setrightmotor(unsigned int val) {   //1 forward, 2 reverse PWM2 left, PWM1 right
    if (val==1) {
        LATCbits.LC4 = 1;
        LATCbits.LC5 = 0;
    } else if (val==2) {
        LATCbits.LC4 = 0;
        LATCbits.LC5 = 1;
    }
}

void leftspeed(unsigned int val) {
    set_PWM2_duty(val);
}
void rightspeed(unsigned int val) {
    set_PWM1_duty(val);
}
/*
void direction(unsigned char val) {//1 straight, 2 gentle left, 3 gentle right, 4 hard left, 5 hard right, 6 reverse
    if (val==0) {
        setleftmotor(1);
        setrightmotor(1);
        leftspeed(STOPCAR);
        rightspeed(STOPCAR);
        currDir = 0;
    } else if (val==1) {
        setleftmotor(1);
        setrightmotor(1);
        leftspeed(MIDSPEED);
        rightspeed(MIDSPEED);
        currDir = 1;
    } else if (val==2) {
        setleftmotor(1);
        setrightmotor(1);
        leftspeed(LOWSPEED);
        rightspeed(HIGHSPEED);
        currDir = 2;
    }  else if (val==3) {
        setleftmotor(1);
        setrightmotor(1);
        leftspeed(HIGHSPEED);
        rightspeed(LOWSPEED);
        currDir = 3;
    }   else if (val==4) {
        setleftmotor(2);
        setrightmotor(1);
        leftspeed(LOWSPEED);
        rightspeed(LOWSPEED);
        currDir = 4;
    }   else if (val==5) {
        setleftmotor(1);
        setrightmotor(2);
        leftspeed(LOWSPEED);
        rightspeed(LOWSPEED);
        currDir = 5;
    }   else if (val==6) {
        setleftmotor(2);
        setrightmotor(2);
        leftspeed(LOWSPEED);
        rightspeed(LOWSPEED);
        currDir = 6;
    }
}
*/