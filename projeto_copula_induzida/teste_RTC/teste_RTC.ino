#include "Wire.h" //biblioteca de manipulação i2c
#include "DS3231.h" //biblioteca do RTC
DS3231 rtc; //delarando o RTC
RTCDateTime dataehora; //configurando função

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  rtc.begin(); //inicia o RTC
  //UTILIZAR O COMANDO A SEGUIR APENAS UMA VEZ AO MÓDULO, DEPOIS APAGAR A LINHA
  //rtc.setDateTime(__DATE__, __TIME__); //configura o horário do rtc para o horário do computador
  
  
}

void loop() {
  dataehora = rtc.getDateTime();
  int hora = dataehora.hour;
  int minuto = dataehora.minute;
  int segundo = dataehora.second;
  // put your main code here, to run repeatedly:
  Serial.println("Hora: " + String(hora) + " Minuto: " + String(minuto) + " Segundo: " + String(segundo));
  //Serial.println("teste");
  delay(1000);
}
