
#include "Tlc5940.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(4,2); // RX, TX

byte buffer[5];


struct LED {
  bool X[8];//= {1,0,0,1};
  int R[8];// = {0,0,0,255}
  int G[8];// = {0,0,0,255};
  int B[8];// = {0,0,0,255}; 
};

//struct LED ledi1 = { {1,0,1,1,0,0,0,1}, {0,0,100,110,0,0,0,255}, {0,0,50,50,0,0,0,255}, {0,0,28,2,0,0,0,255} };

struct LED ledi1 = { {1,0,1,1,0,0,0,1}, {0,0,100,110,0,0,0,255}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0} };

//struct LED* ledi2 = &ledi1;

void valmisteleLedi(struct LED *l){
 Serial.println("valmisteleLedi");
 for(int i = 0; i < 8; i++) {
    if( l->X[i] == 1 ) { // This node already has RGB values set
       continue; 
    }
    // otherwise values must be calculated

    // now find the previuos node that was set
    int alkuIndex = 0;
    
    for(int j = i; i > 0; j--) {
        if( l->X[j] == 1 ) { // This is the previous node
           alkuIndex = j;
           break;
        }        
    }
    // now find the next node that is set
    int loppuIndex = 8;
    
    for(int j = i; i < 8; j++) {
        if( l->X[j] == 1 ) { // This is the previous node
           loppuIndex = j;
           break;
        }        
    }
   double k  = ((l->R[loppuIndex] - l->R[alkuIndex]) / (double)(loppuIndex - alkuIndex));
   l->R[i] = k * (i -  alkuIndex) + l->R[alkuIndex];
          k  = ((l->G[loppuIndex] - l->G[alkuIndex]) / (double)(loppuIndex - alkuIndex));
  // Serial.print("G:lle k:n arvo on ");
  // Serial.println(k);
   l->G[i] = k * (i -  alkuIndex) + l->G[alkuIndex];
          k  = ((l->B[loppuIndex] - l->B[alkuIndex]) / (double)(loppuIndex - alkuIndex));
   l->B[i] = k * (i -  alkuIndex) + l->B[alkuIndex];
   Serial.println("Valmisteltiin");
   Serial.println(l->R[0]);
   Serial.println(l->R[1]);
//   Serial.print("Valmisteltiin");
}
} 

void muutaRGBTila(int *R, int *G,int *B, int alkuNode, struct LED *led, int i, int iMax = 100) {
    int alku = alkuNode;      // alku on alkuNode
    int loppu = alkuNode + 1; // Loppuväli on alkuNode + 1
  /*
    Serial.println("____>");
    Serial.println( (( led->R[loppu] - led->R[alku] ) / (double) iMax ));
    Serial.println( (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ));
    Serial.println( (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ) + led->R[alku]);
    Serial.println(i);
    Serial.println(iMax);
    Serial.println("<___");
    */
//    Serial.println(R[in);
//struct LED2 ledi1 = { {1,  0,  1,    1,    0,  0,  0,  1}, 
//                R     {0,  0,  100,  150,  0,  0,  0,  255}, 

    *R = (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ) + led->R[alku];
    *G = (( led->G[loppu] - led->G[alku] ) / (double) iMax ) * ( i ) + led->G[alku];
    *B = (( led->B[loppu] - led->B[alku] ) / (double) iMax ) * ( i ) + led->B[alku];
    
//    Serial.println(*R);
//    Serial.println(*G);
  //  Serial.println(*B);
    
}

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

  Tlc.clear();
  
  Tlc.set(0, 2000);
  Tlc.set(1, 2000);
  Tlc.set(2, 1234);
 // Tlc.set(3, 234);

  Tlc.update();
  delay(5);
  valmisteleLedi(&ledi1);

}

int R[8] = {0,0,0,0,0,0,0,0};// = {1,2};
int G[8] = {0,0,0,0,0,0,0,0};// = {1,2};
int B[8] = {0,0,0,0,0,0,0,0};// = {1,2};

//int R,G,B;

int nodeNyt = 0;
void loop()
{ 
  Serial.println("#########################");
  Serial.println(ledi1.R[0]);
  Serial.println(ledi1.R[0]);
  // Laske ensimmäisen välin eteneminen;
  // Tarvitaan  kullekkin Ledille R,G ja B -arvot, jotka silmukan lopussa lähetetään microcontrollerille
  // Nämä R,G ja B-arvot, lasketaan muuttujista ledi1 jne
  nodeNyt = 0;
  for(int oI = 0; oI < 7; oI++ ) {
    Serial.println("-------------------");
    for(int i = 0; i < 100; i++) {
        // Mennään for-loopissa kaikki ledit läpi
        // Lasketaan ensimmäisen (0 C:ssä) ledin tila kohdassa i
      //  muutaRGBTila(&R[0],&G[0],&B[0],nodeNyt,&ledi1,i,100);
        muutaRGBTila(&R[0],&G[0],&B[0],nodeNyt,&ledi1,i,100);
      // Nollataan vanha ja asetetaan uusi
      /*
      Serial.println(R[0]);
      Serial.println(G[0]);
      Serial.println(B[0]);
      */
      
      Serial.println(R[0]);
      Serial.println(G[0]);
      Serial.println(B[0]);
      
      
      
      Tlc.clear();
      Tlc.set(0,G[0] * 16);
      Tlc.set(1,B[0] * 16);
      Tlc.set(2,R[0] * 16);
      /*
      Tlc.set(3,G[1] * 16);
      Tlc.set(4,B[1] * 16);
      Tlc.set(5,R[1] * 16);
  */
      Tlc.update();
      delay(50);
     // Serial.println(R);
    }
    nodeNyt++;
  }
//  messageReady();
} // loop()
/*
void messageReady() {
  if( BT.available() >= 12 ) {
    char merkki = BT.read();
    if(merkki != 35) { // 35 is the ASCII value for '#'
      Serial.write("<Ei valmis.");
      Serial.write(merkki);
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
      
      bool alku = 0;
      Serial.write("Alku vs Loppu:");
      if( BT.read() == 'A') {
        alku = 1; 
        Serial.println("Alkuledien muunto");
      }
      else {
        Serial.println("Loppuledien muunto");
      }
      
      Serial.write("alku R Arvoon:");
      char hundreds = BT.read();
      char tens = BT.read();
      char ones = BT.read();
      int sadat = (hundreds - '0') * 100; // convert char to int
      int kymmenet = (tens - '0') * 10; 
      int yhdet = (ones - '0');
      int i = 16 * (sadat + kymmenet + yhdet);
      if( i < 4096 ) {
          Serial.print(i);
          if(alku) {
            led1.alkuR = (sadat + kymmenet + yhdet); }
          else {
            led1.loppuR = (sadat + kymmenet + yhdet); }
      
          Serial.println();
      }
      else {
        Serial.println("Anna luku arvo valilta 0 - 255"); 
      } 
      
      Serial.write("alku G Arvoon:");
      hundreds = BT.read();
      tens = BT.read();
      ones = BT.read();
      sadat = (hundreds - '0') * 100; // convert char to int
      kymmenet = (tens - '0') * 10; 
      yhdet = (ones - '0');
      i = 16 * (sadat + kymmenet + yhdet);
      if( i < 4096 ) {
          Serial.print(i);
          if(alku) {
            led1.alkuG = (sadat + kymmenet + yhdet); }
          else {
            led1.loppuG = (sadat + kymmenet + yhdet); }
      
          Serial.println();
      }
      else {
        Serial.println("Anna luku arvo valilta 0 - 255"); 
      } 
      
      Serial.write("alku B Arvoon:");
      hundreds = BT.read();
      tens = BT.read();
      ones = BT.read();
      sadat = (hundreds - '0') * 100; // convert char to int
      kymmenet = (tens - '0') * 10; 
      yhdet = (ones - '0');
      i = 16 * (sadat + kymmenet + yhdet);
      if( i < 4096 ) {
          Serial.print(i);
          if(alku) { 
            led1.alkuB = (sadat + kymmenet + yhdet); }
          else {
            led1.loppuB = (sadat + kymmenet + yhdet); }
      
          Serial.println();
      }
      else {
        Serial.println("Anna luku arvo valilta 0 - 255"); 
      }
    }   
  } // if( BT.available() >= 11 )
} // messageReady
// */
  
