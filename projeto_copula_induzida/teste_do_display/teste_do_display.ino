#include "LiquidCrystal.h" //biblioteca do Diplay 16x2
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); //iniciando o Display 16x2
  escreverDisplay("SISTEMA DE", "COPULA INDUZIDA");
  delay(2000);
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
  
  lcd.clear();
  lcd.print(millis() / 1000);
  delay(10);
}
