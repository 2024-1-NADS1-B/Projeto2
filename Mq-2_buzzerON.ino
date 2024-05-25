// Definindo os pinos
const int pinSensor = A0;   // Pino analógico para o sensor MQ-2
const int pinBuzzer = 8;    // Pino digital para o buzzer
const int pinLed = 13;      // Pino digital para o LED

// Definindo as constantes
const int limiteGas = 60;  // Limite de concentração de gás

void setup() {
  Serial.begin(9600);       // Inicia a comunicação serial
  pinMode(pinSensor, INPUT);  // Configura o pino do sensor como entrada
  pinMode(pinBuzzer, OUTPUT); // Configura o pino do buzzer como saída
  pinMode(pinLed, OUTPUT);    // Configura o pino do LED como saída
}

void loop() {
  // Lê o valor do sensor
  int valorSensor = analogRead(pinSensor);

  // Exibe o valor lido no monitor serial
  Serial.print("Valor do sensor: ");
  Serial.println(valorSensor);

  // Verifica se o valor do sensor ultrapassou o limite
  if (valorSensor > limiteGas) {
    // Se ultrapassou, ativa o buzzer e acende o LED
    digitalWrite(pinBuzzer, HIGH);
    digitalWrite(pinLed, HIGH);
    Serial.println("Perigo! Concentração de gás alta!");
  } else {
    // Caso contrário, desativa o buzzer e apaga o LED
    digitalWrite(pinBuzzer, LOW);
    digitalWrite(pinLed, LOW);
  }

  // Aguarda um curto período antes de repetir o loop
  delay(1000);
}
