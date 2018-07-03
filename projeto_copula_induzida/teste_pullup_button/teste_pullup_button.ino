int valor = 0;
bool botao1_ativo = true; //botao solto
int valor2 = 0;
bool botao2_ativo = true; //botao solto

void setup() {
  Serial.begin(9600);

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
    }
    
  } else {
    if (botao1_ativo == true){
      botao1_ativo = false;
    }
  }
  
  delay(50);
  
}
