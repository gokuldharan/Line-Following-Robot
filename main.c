#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include "constants.h"
#include "lcd.h"
#include "macros.h"
#include "main.h"




void main(void) {
    OSCCON = 0b01110000; // Force internal oscillator operation at 8MHz, Sleep mode causes device sleep (Bit 7)
    OSCTUNEbits.PLLEN = 1; // multiply to 32MHz
    
    TRISD = 0x00;
    initLCD();

    set_PWM_freq (3100);
    
    TRISC = 0xFF;
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0x00;  // bits 0-3 set RA0 and RA1 as analog inputs and the rest as digital
                    // bits 4-5 set usage of VDD and VSS
    CVRCON = 0x00; // Disable CCP reference voltage output
    CMCONbits.CIS = 0;
    ADFM = 1;
    
    
    PWM1_Start();
    PWM2_Start();
    TRISC = 0x00;
    set_PWM1_duty(512);
    set_PWM2_duty(512);
    setleftmotor(1);
    setrightmotor(1);
    TRISB = 0xFF;
    TRISA = 0b11101111;
    TRISE = 0b111;
    int error = 0;
    int speedDelta = 0;
    int lspeed = 710;
    int rspeed = 710;
    unsigned int position;
    calibrate(sensor_values);
    int lastError = 0;
    
    while(1){
        position = readLine(sensor_values);
        error = position - 3500; //find deviation from center
        speedDelta = KP * error + KD * (error - lastError);
        lspeed = BASESPEED - speedDelta;
        rspeed = BASESPEED + speedDelta;
        lastError = error;
        if(lspeed > 1023) {
                leftspeed(1023);
        } else {
            leftspeed(lspeed);            
        }
        if(rspeed > 1023) {
            rightspeed(1023);           
        } else {
            rightspeed(rspeed);            
        }
        __delay_ms(5);
    }
}
