/*
Title: Simple Humidity and Temperature program using DHT11
Author: David Elmo Ross
Date:  Sat Feb 8th 2025
Description: This program takes a reading from the DHT11 every 2 seconds.
             The DHT11 is only accurate to the nearest % for humidity and
             the nearest degree (C) for temperature.
             ANSI escape sequences are used for screen formatting
*/

#include "arduino.h"                 // include arduino.h Library
#include <dht11.h>                   // include dht11.h library
#define DHT11PIN 4                   // DHT11 Data pin connected to Pin 4

dht11 DHT11;                         // declare DHT11 to be of class dht11

short read_DHT11;                    // GLOBAL read_DHT11 used to start conversion
float humid,temp,fahr;               // GLOBAL float humid, temp, and fahr

void  setup()
{
  Serial.begin(9600);                // set serial baud rate to 9600 baud
  pinMode(DHT11PIN,INPUT_PULLUP);    // 10K pullup or use pinmode INPUT_PULLUP
}

void loop()
{
                                      // Screen Title (%%) gives % on screen
 printf("\e[1;1H\e[2J\e[12;23HHumid(%%) (degC)  (degF)");
 for(;;)
  {
  read_DHT11 = DHT11.read(DHT11PIN);  // reads 40 bit format
                                      // high 8 bits humid & low 8 bits humid 
                                      // high 8 bits temp & low 8 bits temp
                                      // plus 8 bit parity given by adding
                                      // all 32 bits together 8 bits at a time
                                      // typically low 8 bits humid
                                      // and low 8 low 8 bits temp are 0
                                      // since the DHT11 has accuracy only
                                      // to the nearest % for humidity and
                                      // to the nearest degree for temp
  humid=(float)DHT11.humidity;        // humid gets float of humidity value
  temp=(float)DHT11.temperature;      // temp gets float of %C temperature
  fahr=(9.0/5.0)*(temp)+32.0;         // fahr is calculated from temp
  printf("\e[13;25H");                // Put cursor at (13,32)
                                      // print humidity temp(C) temp(F)) to 1 dec place        
   printf("%4.1f\t%4.1f\t%4.1f",
            humid,temp,fahr);
   delay(2000);                       // wait 2 seconds between each reading
  }
}