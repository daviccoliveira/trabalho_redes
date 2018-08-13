#include <SimpleModbusSlave.h>

int LED1 = 8; //Definição das portas dos LEDs
int LED2 = 6;
int LED3 = 4;
int botao = 2;



enum //Enumera as variáveis  que serão utilizadas para comunicação com o Elipse E3
{
  BINARIO, // recebe o valor em decimal para ser convertido em binario
  LED_1, 
  LED_2, 
  LED_3,
  POTENCIOMETRO, //Recebe o valor do sensor LDR; primeiro componente que o E3 irá "reconhecer"(N4 = 01)
  SETPOINT, //Recebe o valor decimal; (N4 = 02)
  SETPOT,
  BOTAO,  
  HOLDING_REGS_SIZE //Identifica a quantidade de holdingRegs que estão sendo utilizados no programa.
};

unsigned int holdingRegs[HOLDING_REGS_SIZE]; //Variável criada para manipulação dos registradores que foram criados. 

int num = 0;
int setpoint;

void setup() {
  
modbus_configure(&Serial, 9600, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs); //Determina os parâmetros necessários para estabelecer a conexão via comunicação serial utilizando MODBUS.
//9600 = velocidade da transmissão dos dados; SERIAL_8N2 = formato do pacote utilizado no MODBUS; 1 = identificação do escravo.

modbus_update_comms(9600, SERIAL_8N2, 1); //Função também responsável pela comunicação via MODBUS; 

pinMode (LED1, OUTPUT); //Modos de operação dos LEDs (saída)
pinMode (LED2, OUTPUT);
pinMode (LED3, OUTPUT);
pinMode (botao, INPUT);
}


void loop() {
  
 modbus_update(); // Função utilizada para a atulização dos valores dos registradores declarados (V_LDR, V_LED...)
 
 holdingRegs[POTENCIOMETRO] = analogRead(A0); //Lê-se a informação presente na porta analógica A0 (Sensor LDR)
 setpoint = holdingRegs[SETPOINT];
 holdingRegs[SETPOT] = setpoint + analogRead(A0);
 holdingRegs[BOTAO] = digitalRead(botao);

  switch(holdingRegs[BINARIO]) {
   case 0:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      holdingRegs[LED_1] = 0;
      holdingRegs[LED_2] = 0;
      holdingRegs[LED_3] = 0;
   break;
   case 1:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      holdingRegs[LED_1] = 1;
      holdingRegs[LED_2] = 0;
      holdingRegs[LED_3] = 0;
   break;
   case 2:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      holdingRegs[LED_1] = 0;
      holdingRegs[LED_2] = 1;
      holdingRegs[LED_3] = 0;
   break;
    case 3:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      holdingRegs[LED_1] = 1;
      holdingRegs[LED_2] = 1;
      holdingRegs[LED_3] = 0;
   break;
    case 4:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      holdingRegs[LED_1] = 0;
      holdingRegs[LED_2] = 0;
      holdingRegs[LED_3] = 1;
   break;
    case 5:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      holdingRegs[LED_1] = 1;
      holdingRegs[LED_2] = 0;
      holdingRegs[LED_3] = 1;
   break;
    case 6:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      holdingRegs[LED_1] = 0;
      holdingRegs[LED_2] = 1;
      holdingRegs[LED_3] = 1;
   break; 
    case 7:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      holdingRegs[LED_1] = 1;
      holdingRegs[LED_2] = 1;
      holdingRegs[LED_3] = 1;
   break;
}
  
 
 
 }





 

