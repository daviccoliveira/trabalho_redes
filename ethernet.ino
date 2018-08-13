

#include <SPI.h> 
#include <Ethernet.h>
#include "Mudbus.h"

Mudbus Mb;
//Function codes 1(read coils), 3(read registers), 5(write coil), 6(write register)
//signed int Mb.R[0 to 125] and bool Mb.C[0 to 128] MB_N_R MB_N_C
//Port 502 (defined in Mudbus.h) MB_PORT

int botao = 8;
int LED1 = 7; //Definição das portas dos LEDs
int LED2 = 6;
int LED3 = 5;
int setpoint;


void setup(){
  uint8_t mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 };
  uint8_t ip[]      = { 192, 168, 1, 10 };
  uint8_t gateway[] = { 192, 168, 1, 1 };
  uint8_t subnet[]  = { 255, 255, 255, 0 };
  Ethernet.begin(mac, ip,gateway, subnet);
  //With the last update of Industrial Shields boards it's not necessary to use function pinMode() 

  
  pinMode (LED1, OUTPUT); //Modos de operação dos LEDs (saída)
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (botao, INPUT);
}

void loop(){
  Mb.Run(); //Update the values of Mb.R and Mb.C every loop cycle

  switch(Mb.R[0]) {
   case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      Mb.R[1] = 0;
      Mb.R[2] = 0;
      Mb.R[3] = 0;
   break;
   case 1:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      Mb.R[1] = 1;
      Mb.R[2] = 0;
      Mb.R[3] = 0;
   break;
   case 2:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      Mb.R[1] = 0;
      Mb.R[2] = 1;
      Mb.R[3] = 0;
   break;
    case 3:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      Mb.R[1] = 1;
      Mb.R[2] = 1;
      Mb.R[3] = 0;
   break;
    case 4:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      Mb.R[1] = 0;
      Mb.R[2] = 0;
      Mb.R[3] = 1;
   break;
    case 5:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      Mb.R[1] = 1;
      Mb.R[2] = 0;
      Mb.R[3] = 1;
   break;
    case 6:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      Mb.R[1] = 0;
      Mb.R[2] = 1;
      Mb.R[3] = 1;
   break; 
    case 7:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
       Mb.R[1] = 1;
       Mb.R[2] = 1;
       Mb.R[3] = 1;
   break;
}
  
 
  Mb.R[4] = analogRead(A0);
  setpoint = Mb.R[5];
  
  Mb.R[6] = Mb.R[4] + setpoint;

//  if( digitalRead(botao)){
//
//    Mb.R[7] = 1;
//  }
//  else{
//    Mb.R[7] = 0;
//  }
  Mb.R[7] = digitalRead(botao);
  

  }

