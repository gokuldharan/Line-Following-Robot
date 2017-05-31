/* 
 * File:   main.h
 * Author: Gokul
 *
 * Created on February 24, 2017, 10:34 PM
 */
//<editor-fold defaultstate="collapsed" desc="Variable Defs">
long freq; // Selected PWM Frequency
unsigned char currDir;
//</editor-fold>
void main(void);
int PWM_Max_Duty(void);
void set_PWM_freq(long fre);
void set_PWM1_duty(unsigned int duty);
void set_PWM2_duty(unsigned int duty);
void PWM1_Start(void);
void PWM2_Start(void);
void PWM1_Stop(void);
void PWM2_Stop(void);
void direction(unsigned char val);
void calibrate(unsigned int * sensor_values);
void readCalibrated(unsigned int * sensor_values);
void read(unsigned int * sensor_values);
void readValues(unsigned int * sensor_values);
unsigned int readLine(unsigned int * sensor_values);
unsigned int ADCread(unsigned char channel);
void setleftmotor(unsigned int val);
void setrightmotor(unsigned int val);
void leftspeed(unsigned int val);
void rightspeed(unsigned int val);

unsigned int sensor_values[8];
unsigned int calibratedMaximum[8];
unsigned int calibratedMinimum[8];
