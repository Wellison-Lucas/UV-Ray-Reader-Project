#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_SI1145.h>

Adafruit_SI1145 uv = Adafruit_SI1145();
LiquidCrystal_I2C lcd(0x3F, 16, 3);

#define pinoSensorUV A0
#define pinoBotao 2

#define verdeLed 3
#define amareloLed 4
#define laranjaLed 5
#define vermelhoLed 6
#define roxoLed 7

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("UV Sensor");
  uv.begin();

  pinMode(pinoBotao, INPUT);
  pinMode(verdeLed, OUTPUT);
  pinMode(amareloLed, OUTPUT);
  pinMode(laranjaLed, OUTPUT);
  pinMode(vermelhoLed, OUTPUT);
  pinMode(roxoLed, OUTPUT);
}

void loop() {
  int botaoState = digitalRead(pinoBotao);
  if (botaoState == HIGH) {
    double sensorValue = analogRead(pinoSensorUV);
    double millivoltage = sensorValue * 5000.0 / 1023.0;
    double IUV = millivoltage * 0.280 / 1023.0;
    int nivelUV = getNivelUV(IUV);
    String cor = getCor(nivelUV);

    // Área de pele exposta ao sol (m²)
    double areaPele = 0.05;

    // Tempo de exposição (s)
    double tempoExposicao = 3600;  // 1 hora em segundos

    // Energia recebida em joules
    double energiaRecebida = IUV * areaPele * tempoExposicao;

    lcd.setCursor(0, 0);
    lcd.print("Volt:");
    lcd.print(millivoltage, 0);
    lcd.print(" mV");

    lcd.setCursor(0, 1);
    lcd.print("IUV:");
    lcd.print(nivelUV);

    lcd.setCursor(0, 2);
    lcd.print("Cor:");
    lcd.print(cor);

    lcd.setCursor(10, 3);  
    lcd.print("Rad:");
    lcd.print(IUV);

    lcd.setCursor(0, 3);
    lcd.print("E:");
    lcd.print(energiaRecebida, 2);

    // Acende os LEDs de acordo com o nível de UV
    if (nivelUV <= 2) {
      digitalWrite(verdeLed, HIGH);
      digitalWrite(amareloLed, LOW);
      digitalWrite(laranjaLed, LOW);
      digitalWrite(vermelhoLed, LOW);
      digitalWrite(roxoLed, LOW);
    } else if (nivelUV <= 5) {
      digitalWrite(verdeLed, LOW);
      digitalWrite(amareloLed, HIGH);
      digitalWrite(laranjaLed, LOW);
      digitalWrite(vermelhoLed, LOW);
      digitalWrite(roxoLed, LOW);
    } else if (nivelUV <= 7) {
      digitalWrite(verdeLed, LOW);
      digitalWrite(amareloLed, LOW);
      digitalWrite(laranjaLed, HIGH);
      digitalWrite(vermelhoLed, LOW);
      digitalWrite(roxoLed, LOW);
    } else if (nivelUV <= 10) {
      digitalWrite(verdeLed, LOW);
      digitalWrite(amareloLed, LOW);
      digitalWrite(laranjaLed, LOW);
      digitalWrite(vermelhoLed, HIGH);
      digitalWrite(roxoLed, LOW);
    } else {
      digitalWrite(verdeLed, LOW);
      digitalWrite(amareloLed, LOW);
      digitalWrite(laranjaLed, LOW);
      digitalWrite(vermelhoLed, LOW);
      digitalWrite(roxoLed, HIGH);
    }
  } else {
    // Desliga todos os LEDs quando o botão é pressionado
    digitalWrite(verdeLed, LOW);
    digitalWrite(amareloLed, LOW);
    digitalWrite(laranjaLed, LOW);
    digitalWrite(vermelhoLed, LOW);
    digitalWrite(roxoLed, LOW);
  }

  delay(1000);
}

int getNivelUV(double IUV) {
  if (IUV < 0.025) return 0;
  if (IUV < 0.050) return 1;
  if (IUV < 0.075) return 2;
  if (IUV < 0.100) return 3;
  if (IUV < 0.125) return 4;
  if (IUV < 0.150) return 5;
  if (IUV < 0.175) return 6;
  if (IUV < 0.200) return 7;
  if (IUV < 0.225) return 8;
  if (IUV < 0.250) return 9;
  if (IUV < 0.275) return 10;
  if (IUV <= 0.300) return 11;
}

String getCor(int nivelUV) {
  if (nivelUV <= 2) return "Verde    ";
  if (nivelUV <= 5) return "Amarelo  ";
  if (nivelUV <= 7) return "Laranja  ";
  if (nivelUV <= 10) return "Vermelho  ";
  return "Roxo       ";
}
