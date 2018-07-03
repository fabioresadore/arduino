#include "LiquidCrystal.h" //biblioteca do Diplay 16x2
LiquidCrystal lcd(2, 4, 6, 7, 8, 11); //declarando o Display 16x2
#include "Wire.h" //biblioteca de manipulação i2c
#include "DS3231.h" //biblioteca do RTC
DS3231 rtc; //delarando o RTC
RTCDateTime dataehora; //configurando função
#include "IRremote.h" //biblioteca de led IR
IRsend irsend; //declara a função

int state = 10; 
//0=esperando inicio
//1=editando horário
//2=fase escura
//3=fase piscando
int ciclo = 0; //ciclo atual
int hora = 18;//hora padrão para início
int minuto = 0;//minuto padrão para início
bool com_ir = false;//verifica se o comando para mudar temperatura do ar foi acionado
bool dis_esc = false;//verifica se pode mandar comando para o display
int atu_hora; //horario atual
int atu_min; //minuto atual
int ter_hora = 19; //horario de termino
int ter_min = 20; //minuto de termino
long temp_decorr;
bool men_certz = false;
int temp_pisc = 0; //padrão
int interv_pisc = 500; //milisegundos
int tempo_ar = 5; //minutos
bool botao1_ativo = false; //botao solto
bool botao2_ativo = false; //botao solto
int cont_regr = 60; //segundos para começar o programa

//---------------------------------------------------------------------------------------------------------------------------
void setup() {
  lcd.begin(16, 2); //iniciando o Display 16x2

  rtc.begin(); //inicia o RTC
  //UTILIZAR O COMANDO A SEGUIR APENAS UMA VEZ AO MÓDULO, DEPOIS APAGAR A LINHA
  //rtc.setDateTime(__DATE__, __TIME__); //configura o horário do rtc para o horário do computador

  //declarando pinos
  pinMode(0, INPUT_PULLUP); //botão push verde
  pinMode(1, INPUT_PULLUP); //botão push vermelho

  //pinos dos leds brancos
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(5,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  //PORTA 3 RESERVADA PARA IR

  //pino do led do Display 16x2
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  //ESCREVE UMA MENSAGEM DE BEM VINDO NO DISPLAY
  escreverDisplay("SISTEMA DE", "COPULA INDUZIDA");
  delay(2000);
  escreverDisplay("BEM VINDO!"," ");
  delay(1000);
  //armazena horário atual
  dataehora = rtc.getDateTime();
  atu_hora = dataehora.hour;
  atu_min = dataehora.minute;

  escreverEspera();
  state = 0;
}



//---------------------------------------------------------------------------------------------------------------------------
bool verificarHor(int horaa, int minutoo){
    
  if ((int) dataehora.hour != horaa || (int) dataehora.minute != minutoo){
    return false;
  }
  else if ((int) dataehora.hour == horaa && (int) dataehora.minute == minutoo){
    return true;
  }
}

//---------------------------------------------------------------------------------------------------------------------------
void escreverEspera(){
  
  if (atu_hora == hora && atu_min == (minuto - 1)){
    if (cont_regr > 0){
      cont_regr = cont_regr - 1;
      escreverDisplay("RELOGIO: " + String(atu_hora) + ":" + arrumarMinuto(atu_min),"INICIA EM: " + String(cont_regr) + "seg"); 
      delay(950); //junto com o delay de 50 do loop fica igual a 1 segundo
    }
  } else {
    escreverDisplay("RELOGIO: " + String(atu_hora) + ":" + arrumarMinuto(atu_min),"INICIO: " + String(hora) + ":" + arrumarMinuto(minuto)); 
  }
}

//---------------------------------------------------------------------------------------------------------------------------
void ligarLeds(){
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
}

//---------------------------------------------------------------------------------------------------------------------------
void desligarLeds(){
  digitalWrite(5,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

//---------------------------------------------------------------------------------------------------------------------------
String arrumarMinuto(int valoor){
  if (valoor < 10){
    return "0" + String(valoor);
  } else {
    return String(valoor);
  }
}

//---------------------------------------------------------------------------------------------------------------------------
void escreverModific(){
  escreverDisplay("INICIAR EM",String(hora) + ":" + arrumarMinuto(minuto));
}

//---------------------------------------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------------------------------------
void calcularTempoRestante (String textinho,int miliseg){
  // min = miliseg / 60000
  // seg = (miliseg - (min * 60000)) / 1000
  int min_rest = miliseg / 60000;
  int seg_rest = (miliseg - (min_rest * 60000)) / 1000;

  escreverDisplay(textinho,"0" + String(min_rest) + ":" + arrumarMinuto(seg_rest));

}

//---------------------------------------------------------------------------------------------------------------------------
void verificaMudancaPrograma(){
  //ciclo 0 a 4
  //0=parado, 1=primeiro ciclo, 4=ultimo ciclo
  //state 2 e 3
  //2=escuro, 3=flash
  if (state == 2){
    if (ciclo == 1){
      if (millis() > (temp_decorr + 600000)){
        state = 3;
        temp_pisc = millis();
      }
      else{
        calcularTempoRestante("Ciclo 1: Escura",millis() - temp_decorr);
      }
    }
    else if (ciclo == 2){
      if (millis() > (temp_decorr + 1800000)){
        state = 3;
        temp_pisc = millis();
      } else{
        calcularTempoRestante("Ciclo 2: Escura",millis() - temp_decorr - 1200000);
      }
    }
    else if (ciclo == 3){
      if (millis() > (temp_decorr + 3000000)){
        state = 3;
        temp_pisc = millis();
        
      } else {
        calcularTempoRestante("Ciclo 3: Escura",millis() - temp_decorr - 2400000);
      }
    }
    else if (ciclo == 4){
      if (millis() > (temp_decorr + 4200000)){
        state = 3;
        temp_pisc = millis();
      } else {
        calcularTempoRestante("Ciclo 4: Escura",millis() - temp_decorr - 3600000);
      }
    }
  }
  else if (state == 3){
    if (ciclo == 1){
      if (millis() > (temp_decorr + 1200000)){
        ciclo = 2;
        state = 2;
      }
      else{ 
      calcularTempoRestante("Ciclo 1: Flashs",millis() - temp_decorr - 600000);
      }
    }
    else if (ciclo == 2){
      if (millis() > (temp_decorr + 2400000)){
        ciclo = 3;
        state = 2;
      } else{
        calcularTempoRestante("Ciclo 2: Flashs",millis() - temp_decorr - 1800000);
      }
    }
    else if (ciclo == 3){
      if (millis() > (temp_decorr + 3600000)){
        ciclo = 4;
        state = 2;
      } else {
        calcularTempoRestante("Ciclo 3: Flashs",millis() - temp_decorr - 3000000);
      }
    }
    else if (ciclo == 4){
      if (millis() > (temp_decorr + 4800000)){
        //escrever finalização
        //envia sinal para voltar a temperatura do ar condicionado
        finalizarPrograma();
      } else {
        calcularTempoRestante("Ciclo 4: Flashs",millis() - temp_decorr - 4200000);
      }
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------
void adicionarMeiaHora(){
 
  if (minuto < 30){
    minuto = 30;
  } 
  else if (minuto >= 30) {
    minuto = 0;
    if (hora == 23){
      hora = 0;
    } else {
      hora = hora + 1;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------
void baixarTempAr(){
        int khz = 38; //declara a frequencia do protocolo NEC
        unsigned int irSignal[] = {}; //envia o código HEX entre as chaves
        irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //envia o comando IR
        com_ir = true;//comando para mudar temperatura do ar enviado
}

//---------------------------------------------------------------------------------------------------------------------------
void aumentarTempAr(){
        int khz = 38; //declara a frequencia do protocolo NEC
        unsigned int irSignal[] = {}; //envia o código HEX entre as chaves
        irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //envia o comando IR
        com_ir = false;
}

//---------------------------------------------------------------------------------------------------------------------------
void iniciarPrograma(){
  digitalWrite(12, LOW);
  ciclo = 1;
  temp_decorr = millis();
  state = 2;
}

//---------------------------------------------------------------------------------------------------------------------------
void finalizarPrograma(){
  //aumentarTempAr();
  ter_hora = dataehora.hour;
  ter_min = dataehora.minute;
  escreverDisplay("Finalizado em:",String(ter_hora) + ":" + arrumarMinuto(ter_min));
  dis_esc = true;
  temp_decorr = millis();
  digitalWrite(12, HIGH);
  cont_regr = 60;
  ciclo = 0;
  state = 0;
}

//---------------------------------------------------------------------------------------------------------------------------
void loop() {
  dataehora = rtc.getDateTime(); //armazena hora atual
  
  //VERIFICA SE ESTÁ NO ESTADO DE ESPERA
  if (state == 0){

    //verifica tempo para mostrar mensagem de término do programa
    if (dis_esc && millis() > (temp_decorr + 600000)){
      dis_esc = false;
      ter_hora = 0;
      ter_min = 0;
      temp_decorr = 0;
    }
    //VERIFICA SE PODE ESCREVER NO DISPLAY O HORÁRIO
    if (!men_certz && !dis_esc && !verificarHor(atu_hora,atu_min)){
      atu_hora = dataehora.hour;
      atu_min = dataehora.minute;
      //escreve o horário no display
      escreverEspera();
    }

    //----------------------------------------------------
      if (atu_hora == hora && atu_min == minuto){
        iniciarPrograma();
      }

     //---------------------------------------------------------
      //VERIFICA SE ESTÁ PRONTO PARA MUDAR TEMPERATURA
      if (minuto >= tempo_ar && atu_hora == hora && atu_min == (minuto - tempo_ar) && com_ir == false){
        //baixarTempAr();
      } else if (minuto < tempo_ar && hora != 0 && atu_hora == (hora - 1) && atu_min == (59 - ((tempo_ar - 1) - minuto)) && com_ir == false){
        //baixarTempAr();
      } else if (minuto < tempo_ar && hora == 0 && atu_hora == 23 && atu_min == (59 - ((tempo_ar - 1) - minuto)) && com_ir == false){
        //baixarTempAr();
      }

//VERIFICA SE OS BOTÕES FORAM APERTADOS
  if (cont_regr >= 60){
    int pushVermelho = digitalRead(1);
    int pushVerde = digitalRead(0);
  
      if (pushVermelho == LOW ){ //verfica se botao vermelho foi pressionado
        if (botao2_ativo == false){
            botao2_ativo = true;
            //SCRIPT A SER FEITO
            if (dis_esc == false){ //verifica se pode mudar horario
              if (men_certz == false){ //verifica se a mensagem de certeza de inicio não está aparecendo
                escreverModific();
                state = 1;
              } else {
                escreverEspera();
                men_certz = false; //cancela confirmação
              }
            } else {
              escreverDisplay("NAO PODE MUDAR","HORARIO AGORA");
              delay(1500);
              escreverDisplay("Finalizado em:",String(ter_hora) + ":" + arrumarMinuto(ter_min));
            }
            
        }
        
      } else {
        if (botao2_ativo == true){
          botao2_ativo = false;
        }
      }
  
    if (pushVerde == LOW ){ //verifica se botao verde foi pressionado
      if (botao1_ativo == false){
          botao1_ativo = true; //botal apertado
          if (dis_esc == false){ //verifica se pode iniciar
            if (men_certz == false){ //verifica se não está aparecendo a mensagem para confirmar inicio
              escreverDisplay("INICIAR PROGRAMA?","");
              men_certz = true;
            } else {
              iniciarPrograma();
              men_certz = false;
            }
          } else {
            escreverDisplay("NAO PODE","INICAR AGORA");
            delay(1500);
            escreverDisplay("Finalizado em:",String(ter_hora) + ":" + arrumarMinuto(ter_min));
          }
      }
      
    } else {
      if (botao1_ativo == true){
        botao1_ativo = false;
      }
    }
  }
}

  //VERIFICA SE ESTÁ NO ESTADO DE MODIFICAR HORARIO
  else if (state == 1){
    int pushVermelho = digitalRead(1);
    int pushVerde = digitalRead(0);
      
    if (pushVermelho == LOW ){
      if (botao2_ativo == false){
          botao2_ativo = true; //botal apertado
          escreverEspera();
          //VERIFICA SE PASSOU DO HORÁRIO DE INCIO
          state = 0;
      }
      
    } else {
      if (botao2_ativo == true){
        botao2_ativo = false;
      }
    }
  
    if (pushVerde == LOW ){
      if (botao1_ativo == false){
          botao1_ativo = true; //botal apertado
          //adiciona meia hora ao horário programado
          adicionarMeiaHora();
          escreverModific();
      }
      
    } else {
      if (botao1_ativo == true){
        botao1_ativo = false;
      }
    }
  }
  
  //VERIFICA SE O PROGRAMA ESTÁ NA FASE ESCURA
  else if (state == 2){
    verificaMudancaPrograma();
  }

  //VERIFICA SE O PROGRAMA ESTÁ NA FASE DE PISCAR
  else if (state == 3){
    if (millis() < (temp_pisc + interv_pisc)){
      ligarLeds();
    }
    else if (millis > (temp_pisc + interv_pisc) && millis() < (temp_pisc + (interv_pisc * 2))){
      desligarLeds();
    }
    
    else if (millis > (temp_pisc + (interv_pisc * 2))){
      temp_pisc = millis();
      ligarLeds();
    }
    verificaMudancaPrograma();
  }

  delay(50);
}
