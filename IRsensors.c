#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "configBits.h"
#include "lcd.h"
#include "constants.h"
#include "macros.h"

/*
 * Written by Ben Schmidel et al., October 4, 2010.
 * Copyright (c) 2008-2012 Pololu Corporation. For more information, see
 *
 *   http://www.pololu.com
 *   http://forum.pololu.com
 *   http://www.pololu.com/docs/0J19
 *
 * You may freely modify and share this code, as long as you keep this
 * notice intact (including the two links above).  Licensed under the
 * Creative Commons BY-SA 3.0 license:
 *
 *   http://creativecommons.org/licenses/by-sa/3.0/
 *
 * Disclaimer: To the extent permitted by law, Pololu provides this work
 * without any warranty.  It might be defective, in which case you agree
 * to be responsible for all resulting costs and damages.
 */

void calibrate(unsigned int * sensor_values) {
    int i, j;
    unsigned int calsensor_values[8];
    unsigned int max_values[8];
    unsigned int min_values[8];

    for(j=0;j<10;j++) {
        read(calsensor_values);
        for(i=0;i<8;i++) {
            if(j == 0 || max_values[i] < calsensor_values[i])
                max_values[i] = calsensor_values[i];

            if(j == 0 || min_values[i] > calsensor_values[i])
                min_values[i] = calsensor_values[i];
        }
    }   
    for(i=0;i<8;i++) {
        /*
        calibratedMaximum[i] = min_values[i];
        calibratedMinimum[i] = max_values[i];*/
        calibratedMaximum[i] = 1023;
        calibratedMinimum[i] = 512;
    }
}




// Returns values calibrated to a value between 0 and 1000, where
// 0 corresponds to the minimum value read by calibrate() and 1000
// corresponds to the maximum value.  Calibration values are
// stored separately for each sensor, so that differences in the
// sensors are accounted for automatically.
void readCalibrated(unsigned int * sensor_values) {
    int i;
    read(sensor_values);
    
    for(i=0;i<8;i++)
    {
        unsigned int calmin,calmax;
        unsigned int denominator;
        calmax = calibratedMaximum[i];
        calmin = calibratedMinimum[i];
        
        denominator = calmax - calmin;

        signed int x = 0;
        if(denominator != 0) {
            x = (((signed long)sensor_values[i]) - calmin)*1000/denominator;
        }
        if(x < 0) {
            x = 0;
        } else if(x > 1000) {
            x = 1000;
        }
        sensor_values[i] = x;
    }
}

void read(unsigned int * sensor_values) {
    unsigned int off_values[8];
    unsigned char i;
    
    EMITTER = 1;
    __delay_us(100);
    readValues(sensor_values);
    EMITTER = 0;
}

void readValues(unsigned int * sensor_values) {
    unsigned char i, j;
    for(i=0;i<8;i++) {
        sensor_values[i] = 0;
    }
    for(j=0;j<4;j++) {
        for(i=0;i<8;i++) {
            sensor_values[i] += ADCread(i);
        }
    }
    for (i=0;i<8;i++) {
        sensor_values[i] = sensor_values[i] / 4;
    }
}
// Operates the same as read calibrated, but also returns an
// estimated position of the robot with respect to a line. The
// estimate is made using a weighted average of the sensor indices
// multiplied by 1000, so that a return value of 0 indicates that
// the line is directly below sensor 0, a return value of 1000
// indicates that the line is directly below sensor 1, 2000
// indicates that it's below sensor 2000, etc.  Intermediate
// values indicate that the line is between two sensors.  The
// formula is:
//
//    0*value0 + 1000*value1 + 2000*value2 + ...
//   --------------------------------------------
//         value0  +  value1  +  value2 + ...
//
// By default, this function assumes a dark line (high values)
// surrounded by white (low values).  If your line is light on
// black, set the optional second argument white_line to true.  In
// this case, each sensor value will be replaced by (1000-value)
// before the averaging.
unsigned int readLine(unsigned int * sensor_values) {
    long avg, i;
    unsigned int sum;
    unsigned int lastValue;
    unsigned int val;
    
    readCalibrated(sensor_values);
    avg = 0;
    sum = 0;
    for(i=0;i<8;i++) {
        val = sensor_values[i];
        if(val>50) {
            avg+=(long)(val) * (i*1000);
            sum += val;
        }
    }
    lastValue = avg/sum;
    return lastValue;
}
