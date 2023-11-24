#include <ESP32Servo.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <DHTesp.h>
#include <PubSubClient.h>


// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";  // Substitua pelo sua senha

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "mafe_mqtt";
const char *TOPIC_PUBLISH_TEMP_HUMI = "FIAP/GS/TempHumi";
// Tópico para enviar as variáveis
const int trigPin = 5;
const int echoPin = 18;

// Configurações de Hardware
#define PIN_DHT 12
#define RED_LED 15
#define YELLOW_LED 21
#define GREEN_LED 2
#define PUBLISH_DELAY 2000
#define SERVO_1_PIN 26
#define SERVO_2_PIN 25
#define BUZZER_PIN 13

// Variáveis globais
Servo servoMotor1;
Servo servoMotor2;
WiFiClient espClient;
PubSubClient MQTT(espClient);
DHTesp dht;
unsigned long publishUpdate = 0;
TempAndHumidity sensorValues;
const int TAMANHO = 200;
long duration;
float distanceCm;
float distanceInch;
String stock;

// Protótipos de funções
void updateSensorValues();
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();

void updateSensorValues() {
  sensorValues = dht.getTempAndHumidity();
}

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);
  
  Serial.printf("Mensagem recebida via MQTT: %s do tópico: %s\n", msg.c_str(), topic);
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      //entrar no mqtt
      
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void)
{
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  servoMotor1.attach(SERVO_1_PIN);
  servoMotor2.attach(SERVO_2_PIN);
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(YELLOW_LED, OUTPUT);
  dht.setup(PIN_DHT, DHTesp::DHT22);
  initWiFi();
  initMQTT();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  if(sensorValues.temperature > 40){
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    servoMotor1.write(90);
    servoMotor2.write(90);
  }
  else if(sensorValues.temperature >= 35){
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    servoMotor1.write(90);
    servoMotor2.write(0);
  }
  else{
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    servoMotor1.write(0);
    servoMotor2.write(0);
  }

  checkWiFIAndMQTT();
  MQTT.loop();

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();
    updateSensorValues();

    if (!isnan(sensorValues.temperature) && !isnan(sensorValues.humidity)) {
      // Enviar umidade
      StaticJsonDocument<TAMANHO> doc_humidity;
      doc_humidity["humidity"] = sensorValues.humidity;

      char buffer_humidity[TAMANHO];
      serializeJson(doc_humidity, buffer_humidity);
      MQTT.publish(TOPIC_PUBLISH_TEMP_HUMI, buffer_humidity);
      Serial.println(buffer_humidity);

      // Enviar temperatura
      StaticJsonDocument<TAMANHO> doc_temperature;
      doc_temperature["temperature"] = sensorValues.temperature;
     

      char buffer_temperature[TAMANHO];
      serializeJson(doc_temperature, buffer_temperature);
      MQTT.publish(TOPIC_PUBLISH_TEMP_HUMI, buffer_temperature);
      Serial.println(buffer_temperature);

      // StaticJsonDocument<TAMANHO> doc_stock;
      // doc_stock["variable"] = stock;

  
      // Serial.println(buffer_stock);
    }
  }
}
