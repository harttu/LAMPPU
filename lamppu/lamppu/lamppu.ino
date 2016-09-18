/*
#include <stdio.h> 
#include <stdbool.h>

struct LED2 {
  bool X[6];//= {1,0,0,1};
  int R[6];// = {0,0,0,255}
  int G[6];// = {0,0,0,255};
  int B[6];// = {0,0,0,255}; 
};

struct LED2 ledi1 = { {1,0,1,0,0,1}, {0,0,100,0,0,255}, {0,0,50,0,0,255}, {0,0,12,0,0,255} };

void valmisteleLedi(struct LED2 l){
 for(int i = 0; i < 6; i++) {
    if( l.X[i] == 1 ) { // This node already has RGB values set
       continue; 
    }
    // otherwise values must be calculated

    // now find the previuos node that was set
    int alkuIndex = 0;
    
    for(int j = i; i > 0; j--) {
        if( l.X[j] == 1 ) { // This is the previous node
           alkuIndex = j;
           break;
        }        
    }
    // now find the next node that is set
    int loppuIndex = 6;
    
    for(int j = i; i < 6; j++) {
        if( l.X[j] == 1 ) { // This is the previous node
           loppuIndex = j;
           break;
        }        
    }
   double k  = ((l.R[loppuIndex] - l.R[alkuIndex]) / (double)(loppuIndex - alkuIndex));
   l.R[i] = k * (i -  alkuIndex) + l.R[alkuIndex];
 printf("\n%i -> [%i],[%i], R:%i\n",i,alkuIndex,loppuIndex,l.R[i]); 
 }
} 

int main(void) 
{ 
valmisteleLedi(ledi1);

printf("\n[%i],[%i],[%i],[%i]\n",ledi1.X[0],ledi1.X[1],ledi1.X[2],ledi1.X[3]); 
printf("\n[%i],[%i],[%i],[%i]\n",ledi1.R[0],ledi1.R[1],ledi1.R[2],ledi1.R[3]); 
    return 0; 
}
*/




#include "Tlc5940.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(4,2); // RX, TX

byte buffer[5];

struct LED   { int alkuR; 
                 int alkuG; 
                 int alkuB; 
                 int loppuR; 
                 int loppuG; 
                 int loppuB; 
               };
LED led1 = { 1,1,1,255,255,255};
LED led2 = { 5,5,5,120,120,120};


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
//  attachInterrupt(0,messageReady,FALLING);
  delay(5);
}

struct LED2 {
  bool X[4];// = {1,0,0,1};
  int R[4];// = {0,0,0,255}
  int G[4];// = {0,0,0,255};
  int B[4];// = {0,0,0,255}; 
};

LED2 ledi1 = { {1,0,0,1}, {0,0,0,255}, {0,0,0,255}, {0,0,0,255} };

void valmisteleLedi(struct LED2 l){
for(int i = 0; i < 4; i++) {
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
    int loppuIndex = 4;
    
    for(int j = i; i < 4; j++) {
        if( l->X[j] == 1 ) { // This is the previous node
           loppuIndex = j;
           break;
        }        
    }

}

//int[] ledit = { {123,23,123},{12,23,34} } };
LED ledit[2] = { led1, led2 };

void muutaRGBTila(int R[], int G[],int B[], struct LED led1[2], int i,int index) {
    //Serial.println((( led1[index].loppuR - led1[index].alkuR ) / 100 ) * ( i ) + led1[index].alkuR );
    Serial.println("---------");
    Serial.println(R[index]);
    R[index] = (( led1[index].loppuR - led1[index].alkuR ) / 100 ) * ( i ) + led1[index].alkuR;
  //  Serial.println(*R[index]);
    G[index] = (( led1[index].loppuG - led1[index].alkuG ) / 100 ) * ( i ) + led1[index].alkuG;
    B[index] = (( led1[index].loppuB - led1[index].alkuB ) / 100 ) * ( i ) + led1[index].alkuB;
 // return {R,G,B};
}

/*
void muutaRGBTila(int (*R)[2], int (*G)[2],int (*B)[2], struct LED *led1, int i,int index) {
    *R[index] = (( led1->loppuR - led1->alkuR ) / 100 ) * ( i ) + led1->alkuR; 
    *G[index] = (( led1->loppuG - led1->alkuG ) / 100 ) * ( i ) + led1->alkuG;
    *B[index] = (( led1->loppuB - led1->alkuB ) / 100 ) * ( i ) + led1->alkuB;
 // return {R,G,B};
}*/
void loop()
{ 
  //Serial.println("----------------alku -> loppu --------");
 
  for(int i = 0; i < 100; i++) {
    int R[2] = {1,2};
    int G[2] = {1,2};
    int B[2] = {1,2};
    /*
    int *pR[2] = &R;
    int *pG[2] = &G;
    int *pB[2] = &B;
*/
    /* int (*pR)[2] = &R;// {0,0};
    int (*pG)[2] = &G;
    int (*pB)[2] = &B;*/
    muutaRGBTila(R,G,B,ledit,i,0);
    muutaRGBTila(R,G,B,ledit,i,1);
//    Serial.println(R[0]);
//    Serial.println(R[1]);
    Tlc.clear();
    Tlc.set(0,G[0] * 16);
    Tlc.set(1,B[0] * 16);
    Tlc.set(2,R[0] * 16);
    
    Tlc.set(3,G[1] * 16);
    Tlc.set(4,B[1] * 16);
    Tlc.set(5,R[1] * 16);

    Tlc.update();
    delay(45);
   // Serial.println(R);
  }
  messageReady();
//  Serial.println("----------------loppu -> alku --------");
/*
  for(int i = 100; i > 0; i--) {
    int R = (( led1.loppuR - led1.alkuR ) / 100 ) * ( i ) + led1.alkuR; 
    int G = (( led1.loppuG - led1.alkuG ) / 100 ) * ( i ) + led1.alkuG;
    int B = (( led1.loppuB - led1.alkuB ) / 100 ) * ( i ) + led1.alkuB;
    Tlc.clear();
    Tlc.set(0,G * 16);
    Tlc.set(1,B * 16);
    Tlc.set(2,R * 16);
    Tlc.update();
    delay(45);
  //  Serial.print(R);
  } */
  messageReady();  
} // loop()

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
  
  
