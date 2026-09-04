#include <LiquidCrystal.h>

// Inicializar libreria con los pines de control (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A0;
const int lightPin = A1;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  // Pantalla de bienvenida
  lcd.setCursor(0, 0);
  lcd.print(" Estacion Meteo ");
  lcd.setCursor(0, 1);
  lcd.print(" Iniciando...   ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Lectura y conversion del TMP36
  int rawTemp = analogRead(tempPin);
  float voltage = rawTemp * (5.0 / 1024.0);
  float tempC = (voltage - 0.5) * 100.0; // Conversion a Celsius

  // 2. Lectura de Luz (LDR)
  int lightValue = analogRead(lightPin);
  int lightPercentage = map(lightValue, 0, 1023, 0, 100);

  // 3. Renderizado en Pantalla LCD
  // Linea 1: Temperatura
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); // Simbolo de grados C
  lcd.print("C   ");

  // Linea 2: Luz / Estado
  lcd.setCursor(0, 1);
  lcd.print("Luz: ");
  lcd.print(lightPercentage);
  lcd.print("% ");
  
  if (lightPercentage > 70) {
    lcd.print("[Sol] ");
  } else if (lightPercentage > 30) {
    lcd.print("[Nub] ");
  } else {
    lcd.print("[Noc] ");
  }

  // Monitor Serie para debugging
  Serial.print("Temp: "); Serial.print(tempC);
  Serial.print(" C | Luz: "); Serial.print(lightPercentage); Serial.println("%");

  delay(1000);
}
