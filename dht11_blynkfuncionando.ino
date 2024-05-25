#define BLYNK_TEMPLATE_ID "TMPL2hsYY6r5H"
#define BLYNK_TEMPLATE_NAME "Queimadas"
#define BLYNK_AUTH_TOKEN "u5IU6CbMG959NiatacEV6BX1ViAmF7CN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Variáveis corrigidas
char ssid[] = "iPhone da Camis";
char password[] = "CORINTHIANS1910";
char auth[] = BLYNK_AUTH_TOKEN;

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE); // Inicializa o sensor DHT

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando WiFi...");
  }

  Blynk.begin(auth, ssid, password);

  dht.begin();
}

void loop()
{
  Blynk.run(); // Executa Blynk

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print("°C, Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V0, humidity);
  Blynk.virtualWrite(V1, temperature);

  delay(5000); // Espera 5 segundos antes de enviar novos dados
}
