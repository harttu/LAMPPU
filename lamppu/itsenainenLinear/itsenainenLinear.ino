#include "Tlc5940.h"

void setup()
{
  Tlc.init();
}


void loop()
{
  struct LED   { int alkuR; 
                 int alkuG; 
                 int alkuB; 
                 int loppuR; 
                 int loppuG; 
                 int loppuB; 
               };
  LED led1 = { 0,0,0,255,255,0};
//  led1 = (LED){ 200,100,30,255,255,0}
  for(int i = 0; i < 100; i++) {
    int R = (( led1.loppuR - led1.alkuR ) / 100 ) * ( i ) + led1.alkuR; 
    int G = (( led1.loppuG - led1.alkuG ) / 100 ) * ( i ) + led1.alkuG;
    int B = (( led1.loppuB - led1.alkuB ) / 100 ) * ( i ) + led1.alkuB;
    Tlc.clear();
    Tlc.set(0,R * 16);
    Tlc.set(1,G * 16);
    Tlc.set(2,B * 16);
    Tlc.update();
    delay(75);
  }
}

