#include "LiquidCrystal.h" //biblioteca do Diplay 16x2
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int valor = 0;
bool botao1_ativo = true; //botao solto
int valor2 = 0;
bool botao2_ativo = true; //botao solto
int miliseg = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //iniciando o Display 16x2
  escreverDisplay("SISTEMA DE", "COPULA INDUZIDA");
  delay(2000);

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
}

void calcularTempoRestante (int milisegs){
  // min = miliseg / 60000
  // seg = (miliseg - (min * 60000)) / 1000
  int min_rest = miliseg / 60000;
  int seg_rest = (miliseg - (min_rest * 60000)) / 1000;

  escreverDisplay(String(int(60000/milisegs)),"");

}

void escreverDisplay(String textoo, String textooo){
  String y;
  int x = (16 - textoo.length()) / 2;
  for (int i=0;i<x;i++){
    y = y + " ";
  }

  String z;
  int xx = (16 - textooo.length()) / 2;
  for (int i=0;i<xx;i++){
    z = z + " ";
  }

  lcd.clear();
  lcd.print(y + textoo);
  lcd.setCursor(0,1);
  lcd.print(z + textooo);
}


void loop() {
  int pushVermelho = digitalRead(1);
  int pushVerde = digitalRead(0);

  if (pushVermelho == LOW ){
    if (botao2_ativo == false){
        botao2_ativo = true; //botal apertado
        calcularTempoRestante(miliseg);
        miliseg += 60000;
    }
    
  } else {
    if (botao2_ativo == true){
      botao2_ativo = false;
    }
  }

  if (pushVerde == LOW ){
    if (botao1_ativo == false){
        botao1_ativo = true; //botal apertado
        valor += 1;
        lcd.clear();
        escreverDisplay("Verde = " + String(valor),"Vermelho = " + String(valor2));
    }
    
  } else {
    if (botao1_ativo == true){
      botao1_ativo = false;
    }
  }
  
  delay(50);
  
}
