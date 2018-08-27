#include <IRremote.h>

IRsend irsend;

int valor = 0;
bool botao1_ativo = true; //botao solto
int valor2 = 0;
bool botao2_ativo = true; //botao solto

void setup() {
  //Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  int pushVermelho = digitalRead(1);
  int pushVerde = digitalRead(0);
    
  if (pushVermelho == LOW ){
    if (botao2_ativo == false){
        botao2_ativo = true; //botal apertado
        //SCRIPT A SER FEITO
        int khz = 38; // 38kHz carrier frequency for the NEC protocol
        unsigned int irSignal[] = {8900, -4100, 600, -550, 600, -550, 550, -600, 600, -600, 550, -600, 600, -600, 550, -1650, 550, -1700, 600, -1650, 600, -550, 600, -600, 550, -600, 550, -600, 600, -550, 600, -550, 600, -550, 600, -600, 550, -1700, 550, -600, 600, -1650, 550, -1700, 550, -600, 550, -600, 600, -550, 600, -550, 600, -550, 600, -1700, 550, -600, 550, -600, 600, -1650, 550, -600, 550, -600, 550}; //AnalysIR Batch Export (IRremote) - RAW
  
        irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
    }
    
  } else {
    if (botao2_ativo == true){
      botao2_ativo = false;
    }
  }

  if (pushVerde == LOW ){
    if (botao1_ativo == false){
        botao1_ativo = true; //botal apertado
        //SCRIPT A SER FEITO
        int khz = 38; // 38kHz carrier frequency for the NEC protocol
        unsigned int irSignal[] = {8950, -4000, 550, -600, 550, -550, 600, -600, 600, -550, 600, -600, 600, -550, 600, -1700, 600, -1650, 550, -1650, 600, -550, 600, -550, 600, -600, 550, -600, 550, -550, 600, -600, 600, -550, 600, -550, 600, -550, 600, -550, 600, -1700, 600, -1650, 600, -550, 550, -550, 600, -550, 600, -550, 600, -1650, 550, -1650, 600, -550, 550, -600, 600, -1700, 550, -600, 550, -600, 550}; //AnalysIR Batch Export (IRremote) - RAW
  
        irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
    }
    
  } else {
    if (botao1_ativo == true){
      botao1_ativo = false;
    }
  }
  
  delay(50);
  
}
