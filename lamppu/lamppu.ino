/*
    Basic Pin setup:
    ------------                                  ---u----
    ARDUINO   13|-> SCLK (pin 25)           OUT1 |1     28| OUT channel 0
              12|                           OUT2 |2     27|-> GND (VPRG)
              11|-> SIN (pin 26)            OUT3 |3     26|-> SIN (pin 11)
              10|-> BLANK (pin 23)          OUT4 |4     25|-> SCLK (pin 13)
               9|-> XLAT (pin 24)             .  |5     24|-> XLAT (pin 9)
               8|                             .  |6     23|-> BLANK (pin 10)
               7|                             .  |7     22|-> GND
               6|                             .  |8     21|-> VCC (+5V)
               5|                             .  |9     20|-> 2K Resistor -> GND
               4|                             .  |10    19|-> +5V (DCPRG)
               3|-> GSCLK (pin 18)            .  |11    18|-> GSCLK (pin 3)
               2|                             .  |12    17|-> SOUT
               1|                             .  |13    16|-> XERR
               0|                           OUT14|14    15| OUT channel 15
    ------------                                  --------

    -  Put the longer leg (anode) of the LEDs in the +5V and the shorter leg
         (cathode) in OUT(0-15).
    -  +5V from Arduino -> TLC pin 21 and 19     (VCC and DCPRG)
    -  GND from Arduino -> TLC pin 22 and 27     (GND and VPRG)
    -  digital 3        -> TLC pin 18            (GSCLK)
    -  digital 9        -> TLC pin 24            (XLAT)
    -  digital 10       -> TLC pin 23            (BLANK)
    -  digital 11       -> TLC pin 26            (SIN)
    -  digital 13       -> TLC pin 25            (SCLK)
    -  The 2K resistor between TLC pin 20 and GND will let ~20mA through each
       LED.  To be precise, it's I = 39.06 / R (in ohms).  This doesn't depend
       on the LED driving voltage.
    - (Optional): put a pull-up resistor (~10k) between +5V and BLANK so that
                  all the LEDs will turn off when the Arduino is reset.

    If you are daisy-chaining more than one TLC, connect the SOUT of the first
    TLC to the SIN of the next.  All the other pins should just be connected
    together:
        BLANK on Arduino -> BLANK of TLC1 -> BLANK of TLC2 -> ...
        XLAT on Arduino  -> XLAT of TLC1  -> XLAT of TLC2  -> ...
    The one exception is that each TLC needs it's own resistor between pin 20
    and GND.

    This library uses the PWM output ability of digital pins 3, 9, 10, and 11.
    Do not use analogWrite(...) on these pins.

    This sketch does the Knight Rider strobe across a line of LEDs.

    Alex Leone <acleone ~AT~ gmail.com>, 2009-02-03 */

#include "Tlc5940.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(4,2); // RX, TX

byte buffer[5];

void setup()
{
  Tlc.init(1600);
  
  Serial.begin(9600);
  BT.begin(9600);
  byte luku = 3;
  int luku2 = luku;
  Serial.write("Serial toimii");
  Serial.print(9);
  Serial.write(luku);

  struct LED   { int alkuR; 
                 int alkuG; 
                 int alkuB; 
                 int loppuR; 
                 int loppuG; 
                 int loppuB; 
               };
  LED led1 = { 0,0,0,255,255,0};



  Tlc.clear();

  
  Tlc.set(0, 2000);
  Tlc.set(1, 2000);
  Tlc.set(2, 1234);
 // Tlc.set(3, 234);


  Tlc.update();

  delay(5);


}

void loop()
{
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

  
  if( BT.available() >= 5 ) {
    char merkki = BT.read();
//    Serial.write(merkki);
    if(merkki != 35) { // 35 is the ASCII value for '#'
      Serial.write("<Ei valmis.");
      Serial.println();
    }
    else {
      Serial.write("Valmis.");
      Serial.println();
      Serial.write("Muutetaan LEDia:");
      char ledNumber = BT.read();
      int ledNumero = ledNumber - 48; // another way to convert to int
      Serial.print(ledNumero);
      Serial.println();
      
      Serial.write("Arvoon:");
      char hundreds = BT.read();
      char tens = BT.read();
      char ones = BT.read();
/*      Serial.println("Sadat:");
      Serial.write(hundreds);
      Serial.println("\nKymmenet:");
      Serial.write(tens);
      Serial.println("\nYhdet:");
      Serial.write(ones);
      Serial.println(); */
      int sadat = (hundreds - '0') * 100; // convert char to int
      int kymmenet = (tens - '0') * 10; 
      int yhdet = (ones - '0');
   /*   Serial.println("Sadat\n");
      Serial.print(sadat);
      Serial.println();
      Serial.println("Kymmenet\n");
      Serial.print(kymmenet);
      Serial.println("Yhdet\n");
      Serial.print(yhdet);
      Serial.println("Koko luku\n"); */
      int i = 16 * (sadat + kymmenet + yhdet);
      Serial.print(i);

      Tlc.clear();
  
      
      Tlc.set(0, i);
      Tlc.set(1, i);
      Tlc.set(2, i);
      Tlc.set(3, i);
  
    
      Tlc.update();
      Serial.println();
    }
  }

  // 67#1R255#2G120#5B088
  //    |          |
} // loop()
  
  
