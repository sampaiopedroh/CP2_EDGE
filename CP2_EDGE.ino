#include "DHT.h"
#include <LiquidCrystal.h> 
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#define PINO_DHT 5 // Pino do sensor DHT11
#define TIPO_DHT DHT11 
DHT sensor_dht(PINO_DHT, TIPO_DHT);

String cor; 
const int PINO_RS = 11; // Pino RS do LCD
const int PINO_E = 10; // Pino EN do LCD 
const int PINO_D4 = 8; // Pino D4 do LCD
const int PINO_D5 = 9; // Pino D5 do LCD
const int PINO_D6 = 6; // Pino D6 do LCD  
const int PINO_D7 = 7; // Pino D7 do LCD

LiquidCrystal lcd(PINO_RS, PINO_E, PINO_D4, PINO_D5, PINO_D6, PINO_D7); 

int PINO_AZUL = 2; // Pino do LED azul
int PINO_VERDE = 1; // Pino do LED verde
int PINO_VERMELHO = 3; // Pino do LED vermelho
int PINO_LDR = A5; // Pino do sensor LDR
int valor_ldr = 0; // Valor lido do sensor LDR
int intensidade_luz; // Intensidade da luz
#define PINO_BUZZER 4 // Pino do buzzer

int tempo = 150;

const unsigned long intervalo_evento = 2000; 
unsigned long tempo_previo = 0;
int estado_display = 0; 

void setup() {
  Serial.begin(9600); 

  sensor_dht.begin(); 
  lcd.begin(16,2); 

  pinMode(PINO_AZUL, OUTPUT); 
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_VERMELHO, OUTPUT);
  pinMode(PINO_LDR, INPUT); 
  digitalWrite(PINO_LDR, LOW); 
  pinMode(PINO_BUZZER, OUTPUT); 

  lcd.clear();
  lcd.print("L");
  delay(200);
  lcd.clear();
  lcd.print("LO");
  delay(200);
  lcd.clear();
  lcd.print("LOA");
  delay(200);
  lcd.clear();
  lcd.print("LOAD");
  delay(200);
  lcd.clear();
  lcd.print("LOADIN");
  delay(200);
  lcd.clear();
  lcd.print("LOADING");
  delay(200);
  lcd.clear();
  lcd.print("LOADING .");
  delay(200);
  lcd.clear();
  lcd.print("LOADING ..");
  delay(200);
  lcd.clear();
  lcd.print("LOADING ...");
  delay(1500);
}

void loop() {
  if(Serial.available()){
    cor = Serial.readString(); 
    Serial.println(cor);
  }

  unsigned long tempo_atual = millis();
  float temperatura = sensor_dht.readTemperature(); 
  float umidade = sensor_dht.readHumidity(); 

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println(F("Houve uma falha ao ler o sensor DHT!"));
    return;
  }

  int numero_leituras = 10;
  int sensor_soma = 0;

  for (int i = 0; i < numero_leituras; i++) {
    valor_ldr = analogRead(PINO_LDR);
    intensidade_luz = map(valor_ldr, 0, 990, 0, 100);
    sensor_soma += intensidade_luz;
    delay(1);
  }
  int sensor_media = sensor_soma / numero_leituras;

  if (tempo_atual - tempo_previo >= intervalo_evento) {
    switch (estado_display) {
      case 0:
        exibir_luz(sensor_media); 
        estado_display = 1;
        break;
      case 1:
        exibir_umidade(umidade); 
        estado_display = 2;
        break;
      case 2:
        exibir_temperatura(temperatura); 
        estado_display = 0;
        break;
    }

    Serial.print(F("Temperatura: "));
    Serial.print(temperatura);
    Serial.print(F("°C Umidade: "));
    Serial.print(umidade);
    Serial.println(F("%"));
    Serial.print("Intensidade de Luz 0 - 1023 = ");
    Serial.println(valor_ldr);
    Serial.print("Intensidade de Luz 0 - 100% = ");
    Serial.println(sensor_media);
    Serial.println("******************************");
    tempo_previo = tempo_atual; 
  }
}

void buzina(){
  tone(PINO_BUZZER, 2000, 1500);
}

void acender_verde() {
  analogWrite(PINO_VERMELHO, 0);
  analogWrite(PINO_VERDE, 255);
  analogWrite(PINO_AZUL, 0);
}

void acender_vermelho() {
  analogWrite(PINO_VERMELHO, 255);
  analogWrite(PINO_VERDE, 0);
  analogWrite(PINO_AZUL, 0);
}

void acender_amarelo() {
  analogWrite(PINO_VERMELHO, 255);
  analogWrite(PINO_VERDE, 255);
  analogWrite(PINO_AZUL, 0);
}

void exibir_luz(int sensor_media) {
  lcd.clear();

  if (sensor_media >= 8 && sensor_media <= 35) {
    acender_amarelo();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
    delay(5000);
  } else if (sensor_media < 8) {
    lcd.setCursor(0,0);
    acender_verde();
    lcd.print("Ambiente com");
    lcd.setCursor(0,1);
    lcd.print("luz baixa");
    delay(5000);
  } else {
    acender_vermelho();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Ambiente muito");
    lcd.setCursor(0,1);
    lcd.print("claro");
    delay(5000);
  }
}

void exibir_umidade(float umidade) {
  lcd.clear();

  if (umidade >= 50 && umidade <= 70) {
    acender_verde();
    lcd.setCursor(0,0);
    lcd.print("Umidade OK");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  } else if (umidade < 50) {
    acender_vermelho();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Umidade BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  } else {
    acender_vermelho();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Umidade ALTA");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
    lcd.print(umidade);
    lcd.print("%");
    delay(5000);
  }
}

void exibir_temperatura(float temperatura) {
  lcd.clear();

  if (temperatura >= 10 && temperatura <= 15) {
    acender_verde();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223); 
    lcd.print("C");
    delay(5000);
  } else if (temperatura < 10) {
    acender_amarelo();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Temp. BAIXA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223); 
    lcd.print("C");
    delay(5000);
  } else {  
    acender_amarelo();
    buzina();
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temperatura);
    lcd.print((char)223); 
    lcd.print("C");
    delay(5000);
  }
}
