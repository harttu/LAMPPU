
#include "Tlc5940.h"
#include <SoftwareSerial.h>
 
#include <avr/pgmspace.h>
 
#define NODEJENLKM 5
#define VALIENLKM 4
#define LEDIENLKM 4

const uint32_t PROGMEM gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,
    2,  2,  2,  3,  3,  4,  4,  5,  5,  6,  7,  8,  8,  9, 10, 11,
   12, 13, 15, 16, 17, 18, 20, 21, 23, 25, 26, 28, 30, 32, 34, 36,
   38, 40, 43, 45, 48, 50, 53, 56, 59, 62, 65, 68, 71, 75, 78, 82,
   85, 89, 93, 97,101,105,110,114,119,123,128,133,138,143,149,154,
  159,165,171,177,183,189,195,202,208,215,222,229,236,243,250,258,
  266,274,282,290,298,306,315,324,332,341,351,360,370,379,389,399,
  409,419,430,441,451,462,473,485,496,508,520,532,544,556,569,582,
  595,608,621,634,648,662,676,690,705,719,734,749,764,780,795,811,
  827,843,859,876,893,910,927,944,962,980,998,1016,1035,1053,1072,1091,
  1111,1130,1150,1170,1190,1211,1231,1252,1273,1295,1316,1338,1360,1382,1405,1427,
  1450,1474,1497,1521,1545,1569,1593,1618,1643,1668,1693,1719,1745,1771,1797,1824,
  1851,1878,1905,1933,1960,1989,2017,2046,2075,2104,2133,2163,2193,2223,2254,2284,
  2315,2347,2378,2410,2442,2475,2507,2540,2573,2607,2641,2675,2709,2744,2779,2814,
  2849,2885,2921,2957,2994,3031,3068,3106,3144,3182,3220,3259,3298,3337,3376,3416,
  3457,3497,3538,3579,3620,3662,3704,3746,3789,3832,3875,3919,3962,4007,4051,4095 };

SoftwareSerial BT(4,2); // RX, TX

byte buffer[5];

struct LED {
  bool X[NODEJENLKM];//= {1,0,0,1};
  int R[NODEJENLKM];// = {0,0,0,255}
  int G[NODEJENLKM];// = {0,0,0,255};
  int B[NODEJENLKM];// = {0,0,0,255}; 
};

struct LED ledi1 = { {1,1,1,1,1}, {0,255,0,255,0}, {0,0,0,0,0}, {0,0,0,0,0} };
struct LED ledi2 = { {1,1,1,1,1}, {255,0,255,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };
struct LED ledi3 = { {1,1,1,1,1}, {0,255,50,100,0}, {0,0,0,0,0}, {0,0,0,0,0} };
struct LED ledi4 = { {1,1,1,1,1}, {0,255,50,100,0}, {0,0,0,0,0}, {0,0,0,0,0} };

struct LED ledit[4] = { ledi1, ledi2, ledi3, ledi4 };

//struct LED* ledi2 = &ledi1;

void valmisteleLedi(struct LED *l){
 Serial.println("valmisteleLedi");
 for(int i = 0; i < NODEJENLKM; i++) {
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
    int loppuIndex = NODEJENLKM;
    
    for(int j = i; i < NODEJENLKM; j++) {
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
//    Serial.println(R[in);
//struct LED2 ledi1 = { {1,  0,  1,    1,    0,  0,  0,  1}, 
//                R     {0,  0,  100,  150,  0,  0,  0,  255}, 

    *R = (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ) + led->R[alku];
    *G = (( led->G[loppu] - led->G[alku] ) / (double) iMax ) * ( i ) + led->G[alku];
    *B = (( led->B[loppu] - led->B[alku] ) / (double) iMax ) * ( i ) + led->B[alku];
}


void muutaRGBTila2(int *R, int *G,int *B, int alkuNode, struct LED *led, int i, int iMax = 100) {
    int alku = alkuNode;      // alku on alkuNode
    int loppu = alkuNode + 1; // Loppuväli on alkuNode + 1
//    Serial.println(R[in);
//struct LED2 ledi1 = { {1,  0,  1,    1,    0,  0,  0,  1}, 
//                R     {0,  0,  100,  150,  0,  0,  0,  255}, 

    *R = (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ) + led->R[alku];
    *G = (( led->G[loppu] - led->G[alku] ) / (double) iMax ) * ( i ) + led->G[alku];
    *B = (( led->B[loppu] - led->B[alku] ) / (double) iMax ) * ( i ) + led->B[alku];
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

int R[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};
int G[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};
int B[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};

//int R,G,B;

int nodeNyt = 0;
void loop()
{ 
//  Serial.println("#########################");
//  Serial.println(ledi1.R[0]);
//  Serial.println(ledi1.R[0]);
  // Laske ensimmäisen välin eteneminen;
  // Tarvitaan  kullekkin Ledille R,G ja B -arvot, jotka silmukan lopussa lähetetään microcontrollerille
  // Nämä R,G ja B-arvot, lasketaan muuttujista ledi1 jne
  if(0){
  for(int i = 0; i < 255; i++ ) { 
        Serial.print("i:");
        Serial.println(i);
        Serial.print("Taulukosta:");
        Serial.println(pgm_read_word_near(&gamma[i]));
        Tlc.clear();
       
        Tlc.set(0, pgm_read_word_near(&gamma[i])  );
        Tlc.set(1, pgm_read_word_near(&gamma[i]) );
        Tlc.set(2, pgm_read_word_near(&gamma[i]) );
      
      /*
      Tlc.set(0, oGamma[i] );
        Tlc.set(1, oGamma[i] );
        Tlc.set(2, oGamma[i] );
      */
        Tlc.update();
        delay(100);  

}}

  Serial.println("------------------------");
  if(1) {
    nodeNyt = 0;
    for(int oI = 0; oI < VALIENLKM; oI++ ) {
      messageReady();
      Serial.println("R arvot:");
      for(int t = 0;t < NODEJENLKM; t++) {
        Serial.print("  t:n arvo :");
        Serial.println(t);
        Serial.print("    X:n arvo :");
        Serial.println(ledi1.X[t]);
        Serial.print("    R:n arvo :");
        Serial.println(ledi1.R[t]);
      }
      Serial.print("------------------- nodeNyt:");
      Serial.println(nodeNyt);
      for(int i = 0; i < 100; i++) {
        // Mennään for-loopissa kaikki ledit läpi
        // Lasketaan ensimmäisen (0 C:ssä) ledin tila kohdassa i
   //     Tlc.clear();
        for( int e = 0; e < LEDIENLKM; e++ ) {
          muutaRGBTila2(&R[e],&G[e],&B[e],nodeNyt,&ledit[e],i,100);
          
          Serial.print("        indexi (e) :");
          Serial.println(e);
          Serial.print("          ledin jalka :");
          Serial.println(3*e+2);
          Serial.print("              signaali :");
          Serial.println(pgm_read_word_near(&gamma[R[e]]));
        
          Tlc.set(3 * e + 0, pgm_read_word_near(&gamma[G[e]]) );
          Tlc.set(3 * e + 1, pgm_read_word_near(&gamma[B[e]]) );
          Tlc.set(3 * e + 2, pgm_read_word_near(&gamma[R[e]]) );  
         
        }
        Serial.println("-------Paivitetaan-----------");
        Tlc.update();
        delay(50);
       /*   muutaRGBTila2(&R[e],&G[0],&B[0],nodeNyt,&ledi1,i,100);
          Tlc.clear();
          Tlc.set(0, pgm_read_word_near(&gamma[G[0]]) );
          Tlc.set(1, pgm_read_word_near(&gamma[B[0]]) );
          Tlc.set(2, pgm_read_word_near(&gamma[R[0]]) );  
          Tlc.update();*/
      }
      nodeNyt++;
    }
  }
  messageReady();
} // loop()


/*
struct LED {
  bool X[8];//= {1,0,0,1};
  int R[8];// = {0,0,0,255}
  int G[8];// = {0,0,0,255};
  int B[8];// = {0,0,0,255}; 
};
*/
 
//struct LED ledi1 = { {1    ,1      ,1    ,1      ,0    ,1    ,0    ,1}, 
//                     {0    ,255    ,50   ,100    ,0    ,0    ,0    ,255}, 
//                     {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0} };

// protokolla -> (1 aloitusmerkki #)(1 ledinNumero:1,2,3,4...)(1 komennon tyyppi X tai R,G,B)(8 varikoodi/koodi muodossa ### )
// eli yhteensä 1 + 1 + 1 + 3 * 8 = 27 merkkiä
// esim #1X001000001001000000000...
// esim #1R255000255125000255000...


void messageReady() {
  if( BT.available() >= 12 ) {
    char merkki = BT.read();
    if(merkki != 35) { // 35 is the ASCII value for '#'
      Serial.write("Ei valmis. Merkki oli:");
      Serial.write(merkki);
      Serial.println();
    }
    else {
      Serial.write("Valmis.");
      Serial.println();
      Serial.write("Muutetaan LEDia:");
      char ledNumber = BT.read();
      int ledinNumero = ledNumber - 48; // another way to convert to int
      Serial.print(ledinNumero);
      Serial.println();
      
      bool komento = 0;
      bool Rvalittu = 0;
      bool Gvalittu = 0;
      bool Bvalittu = 0;
      
      Serial.write("Ohjauksen tyyppi:");
      char ohjausMerkki = BT.read();
      if( ohjausMerkki == 'X') {
        komento = 1; 
        Serial.println("Komento");
      }
      else if( ohjausMerkki == 'R' ) {
        Rvalittu = 1; 
        Serial.println("R");
        Serial.print(" Merkki:>");
        Serial.println(ohjausMerkki);

      }
      else if( ohjausMerkki == 'G' ) {
        Gvalittu = 1; 
        Serial.println("G");
      } 
      else if( ohjausMerkki == 'B' ) {
        Bvalittu = 1; 
        Serial.println("B");
      }
      else {
        Serial.println("!Komentoa ei tunnistettu");
      }
      
      int RGBXbuffer[8];
      Serial.write("Arvot:\n");
      
      for(int i = 0; i < 5; i++) 
      {
        Serial.println("Uusi kierros");
        char hundreds = BT.read();
        char tens = BT.read();
        char ones = BT.read();
        int sadat = (hundreds - '0') * 100; // convert char to int
        int kymmenet = (tens - '0') * 10; 
        int yhdet = (ones - '0');
        int summa = (sadat + kymmenet + yhdet);
      
//      Serial.print(hundreds);
        Serial.println(sadat);
        Serial.println(kymmenet);
        Serial.println(yhdet);
        
        if( summa < 257  && summa >= 0) {
          Serial.print("Hyvaksyttiin:");
          Serial.println(summa);
          RGBXbuffer[i] = summa;
        }
        else {
         Serial.print("Ei hyvaksytty:");
         Serial.println(summa);
         RGBXbuffer[i] = 0; 
        }
        Serial.println("Kierros valmis");
      }
      Serial.print("<----");
      
      if( ledinNumero == 1 || ledinNumero == 2 || ledinNumero == 3 || ledinNumero == 4 ) {
            
            if( komento ) {
              Serial.println("Asetan X arvot");
              for( int i = 0; i < NODEJENLKM ; i++ ) {
                ledit[ledinNumero].X[i] = RGBXbuffer[i];    
              }
            }
            else if( Rvalittu ) {
              Serial.println("Asetan R arvot");
              for( int i = 0; i < NODEJENLKM ; i++ ) {
                ledit[ledinNumero].R[i] = RGBXbuffer[i];    
              }
            }
            else if( Gvalittu ) {
              Serial.println("Asetan G arvot");
              for( int i = 0; i < NODEJENLKM ; i++ ) {
                ledit[ledinNumero].G[i] = RGBXbuffer[i];    
                Serial.print("ledi1.G[");
                Serial.print(i);
                Serial.println("]");
              }
            }
            else if( Bvalittu ) {
              Serial.println("Asetan B arvot");
              for( int i = 0; i < NODEJENLKM ; i++ ) {
                ledit[ledinNumero].B[i] = RGBXbuffer[i];    
              }
            }
            else {
              Serial.println("Skipataan tama kierros. Komentoa ei tunnistettu");
      
          } 
          valmisteleLedi(&ledi1);
      } // if( ledinNumero === 1 || ....
//    if(
    } 
  } // if( BT.available() >= 11 )
} // messageReady

// */

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
*/


/*
=================================================

#include "Tlc5940.h"
#include <SoftwareSerial.h>

#define NODEJENLKM 8
#define VALIENLKM 7

SoftwareSerial BT(4,2); // RX, TX

byte buffer[5];

struct LED {
  bool X[NODEJENLKM];//= {1,0,0,1};
  int R[NODEJENLKM];// = {0,0,0,255}
  int G[NODEJENLKM];// = {0,0,0,255};
  int B[NODEJENLKM];// = {0,0,0,255}; 
};

struct LED ledi1 = { {1,1,1,1,0,1,0,1}, {0,255,50,100,0,0,0,255}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0} };

//struct LED ledi1 = { {1,1,1,1,0,1,0,1}, {0,255,50,100,0,0,0,255}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0} };


//struct LED* ledi2 = &ledi1;

void valmisteleLedi(struct LED *l){
 Serial.println("valmisteleLedi");
 for(int i = 0; i < NODEJENLKM; i++) {
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
    int loppuIndex = NODEJENLKM;
    
    for(int j = i; i < NODEJENLKM; j++) {
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
//    Serial.println(R[in);
//struct LED2 ledi1 = { {1,  0,  1,    1,    0,  0,  0,  1}, 
//                R     {0,  0,  100,  150,  0,  0,  0,  255}, 

    *R = (( led->R[loppu] - led->R[alku] ) / (double) iMax ) * ( i ) + led->R[alku];
    *G = (( led->G[loppu] - led->G[alku] ) / (double) iMax ) * ( i ) + led->G[alku];
    *B = (( led->B[loppu] - led->B[alku] ) / (double) iMax ) * ( i ) + led->B[alku];
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

int R[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};
int G[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};
int B[NODEJENLKM];// = {0,0,0,0,0,0,0,0};// = {1,2};

//int R,G,B;

int nodeNyt = 0;
void loop()
{ 
//  Serial.println("#########################");
//  Serial.println(ledi1.R[0]);
//  Serial.println(ledi1.R[0]);
  // Laske ensimmäisen välin eteneminen;
  // Tarvitaan  kullekkin Ledille R,G ja B -arvot, jotka silmukan lopussa lähetetään microcontrollerille
  // Nämä R,G ja B-arvot, lasketaan muuttujista ledi1 jne
  if(1) {
    nodeNyt = 0;
    for(int oI = 0; oI < VALIENLKM; oI++ ) {
      messageReady();

      Serial.println("-------------------");
      for(int i = 0; i < 100; i++) {
          // Mennään for-loopissa kaikki ledit läpi
          // Lasketaan ensimmäisen (0 C:ssä) ledin tila kohdassa i
        //  muutaRGBTila(&R[0],&G[0],&B[0],nodeNyt,&ledi1,i,100);
          muutaRGBTila(&R[0],&G[0],&B[0],nodeNyt,&ledi1,i,100);
        // Nollataan vanha ja asetetaan uusi
        
        Tlc.clear();
        Tlc.set(0,G[0] * 16);
        Tlc.set(1,B[0] * 16);
        Tlc.set(2,R[0] * 16);
        
        Tlc.update();
        delay(50);
       // Serial.println(R);
      }
      nodeNyt++;
    }
  }
  messageReady();
} // loop()


 
//struct LED ledi1 = { {1    ,1      ,1    ,1      ,0    ,1    ,0    ,1}, 
//                     {0    ,255    ,50   ,100    ,0    ,0    ,0    ,255}, 
//                     {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0} };

// protokolla -> (1 aloitusmerkki #)(1 ledinNumero:1,2,3,4...)(1 komennon tyyppi X tai R,G,B)(8 varikoodi/koodi muodossa ### )
// eli yhteensä 1 + 1 + 1 + 3 * 8 = 27 merkkiä
// esim #1X001000001001000000000...
// esim #1R255000255125000255000...


void messageReady() {
  if( BT.available() >= 9 ) {
    char merkki = BT.read();
    if(merkki != 35) { // 35 is the ASCII value for '#'
      Serial.write("Ei valmis. Merkki oli:");
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
      
      bool komento = 0;
      Serial.write("Ohjauksen tyyppi:");
      if( BT.read() == 'X') {
        komento = 1; 
        Serial.println("Komento");
      }
      else {
        Serial.println("Varimuunto");
      }
      
      int RGBXbuffer[8];
      Serial.write("Arvot:\n");
      
      for(int i = 0; i < 4; i++) 
      {
        Serial.println("Uusi kierros");
        char hundreds = BT.read();
        char tens = BT.read();
        char ones = BT.read();
        int sadat = (hundreds - '0') * 100; // convert char to int
        int kymmenet = (tens - '0') * 10; 
        int yhdet = (ones - '0');
        int summa = (sadat + kymmenet + yhdet);
      
//      Serial.print(hundreds);
        Serial.println(sadat);
        Serial.println(kymmenet);
        Serial.println(yhdet);
        
        if( summa < 257  && summa >= 0) {
          Serial.print("Hyvaksyttiin:");
          Serial.println(summa);
          RGBXbuffer[i] = summa;
        }
        else {
         Serial.print("Ei hyvaksytty:");
         Serial.println(summa);
         RGBXbuffer[i] = 0; 
        }
        Serial.println("Kierros valmis");
      }
      Serial.print("<----");
    }   
  } // if( BT.available() >= 11 )
} // messageReady

// */

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
*/

