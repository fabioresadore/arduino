#include "Wire.h" //biblioteca de manipulação i2c
#include "DS3231.h" //biblioteca do RTC
DS3231 rtc; //delarando o RTC
RTCDateTime dataehora; //configurando função
int segundoinicial = 0;
int minutoinicial = 0

#include "LiquidCrystal.h" //biblioteca do Diplay 16x2
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //Serial.begin(9600);
  // put your setup code here, to run once:
  rtc.begin(); //inicia o RTC
  //UTILIZAR O COMANDO A SEGUIR APENAS UMA VEZ AO MÓDULO, DEPOIS APAGAR A LINHA
  //rtc.setDateTime(__DATE__, __TIME__); //configura o horário do rtc para o horário do computador
  dataehora = rtc.getDateTime();
  int segundoinicial = dataehora.second;
  int minutoinicial = dataehora.minute;
  lcd.begin(16, 2); //iniciando o Display 16x2
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
  dataehora = rtc.getDateTime();
  int hora = dataehora.hour;
  int minuto = dataehora.minute;
  int segundo = dataehora.second;
  // put your main code here, to run repeatedly:
  escreverDisplay("Segundos:",String(segundo - segundoinicial));
  //Serial.println("teste");
  delay(1000);
}
