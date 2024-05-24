#define BLYNK_TEMPLATE_ID           "TMPL2l62GmY9g"
#define BLYNK_TEMPLATE_NAME         "Sensor de enchentes"
#define BLYNK_AUTH_TOKEN            "dTCA-Aj2AkhLQ2wvxufM5lCmY-iLlRLv"
#define BLYNK_PRINT Serial

//BIBLIOTECAS
#include <WiFi.h>
//#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <dummy.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Inicializando o objeto timer do tipo BlynkTimer
BlynkTimer timer; 


// DEFINE O NUMERO DE COLUNAS E LINHAS DO LCD
//#define col 16 //numero de colunas
//#define lin 2 
// número de linhas 
//#define ende 0x3F 
//define o endereço do display 

#define TRIGGER_PIN  23
#define ECHO_PIN     18


LiquidCrystal_I2C lcd(0x27,16,2); 
//Cria o objeto lcd passando como parâmetros o endereço, o nº de colunas e o nº de linhas



// WIFI E SENHA
char auth[] = "dTCA-Aj2AkhLQ2wvxufM5lCmY-iLlRLv";
char ssid[] = "Wi-Fi ACS07";
char pass[] = "195f791ab816";


// VARIÁVEIS
int verde = 13;
int amarelo = 12;
int vermelho = 14;
int sirene = 17;

// SETUP 
void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(sirene, OUTPUT);
  lcd.init();
//inicializa a comunicação com o display ja conectado 
//lcd.clear(); //limpa a tela do display
lcd.backlight(); //Aciona a luz de fundo do display

// INICIALIZANDO O BLYNK
Blynk.begin(auth, ssid, pass);

}


void loop() {
  
// CHAMA A FUNÇÃO Blynk.run()
  Blynk.run(); 

// CHAMA A FUNÇÃO timer.run()
  timer.run(); 
  
  long duration, distance;
  
  // LIMPA O PINO DE TRIGGER
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  
  // ENVIA UM PULSO DE 10 MICROSSEGUNDOS NO PINO DE TRIGGER
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  // LÊ A DURAÇÃO DO PULSO NO PINO DE ECO
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // CALCULA A DISTÂNCIA EM CENTÍMETROS
  distance = duration * 0.034 / 2;
  
  // EXIBE A DISTÂNCIA NO MONITOR SERIAL
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

// ESCREVE NO PINO VIRTUAL V1 O VALOR DA VARIÁVEL (DISTANCE)
  Blynk.virtualWrite(V1, distance);
  


  delay(1000); // Espera 1 segundo antes de realizar a próxima leitura

  //lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
  //lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
  // LEITURA DOS LED'S

   if (distance>=25 && distance<=38)
     { 
      digitalWrite(verde, HIGH);
      lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
       lcd.print(" AVISO: ");  //BAIXAS CHANCES!
       lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
       lcd.print(" OBSERVACAO "); // BAIXAS CHANCES
       delay(1000);
       //lcd.clear();
      
     }

   else 
   {
    digitalWrite(verde, LOW);
    lcd.clear();
   }

   if (distance >=15 && distance <=25)
     { 
      
      digitalWrite(amarelo, HIGH);
      lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
       lcd.print(" AVISO: ");  //BAIXAS CHANCES!
       lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
       lcd.print(" CUIDADO "); // BAIXAS CHANCES
      delay(1000);
      lcd.clear();
     }

   else
   {
    digitalWrite(amarelo, LOW);
   
   }
     
   if(distance >=1 && distance <=15)
   {
      digitalWrite(vermelho,HIGH);
      lcd.setCursor(0, 0); //Coloca o cursor do display na coluna 1 e linha 1
       lcd.print(" AVISO: ");  //BAIXAS CHANCES!
       lcd.setCursor(0, 1); //Coloca o cursor do display na coluna 1 e linha 2
       lcd.print(" PERIGO "); // BAIXAS CHANCES
      delay(1000);
      lcd.clear();
   }
   else 
     {
      digitalWrite(vermelho, LOW);
     }      
      
// PARTE DO BUZZER

    if(distance >=1 && distance <=15)
    {
     digitalWrite(sirene,HIGH); 
    }

    else 
     {
      digitalWrite(sirene, LOW);

     } 
}
