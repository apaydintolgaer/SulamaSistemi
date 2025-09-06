#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

const int rolePin = 5;          
const int nemSensorPin = A0;    
const int nemEsik = 500; 
const unsigned long pompaCalismaSuresi = 5000;

bool pompaCalisiyor = false;
unsigned long pompaBaslangicZamani = 0;

void setup() {
  pinMode(rolePin, OUTPUT);
  digitalWrite(rolePin, LOW); 

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Sulama Sistemi");
  delay(2000);
  lcd.clear();
}

void loop() {
  int nemDegeri = analogRead(nemSensorPin);
  Serial.print("Nem: ");
  Serial.println(nemDegeri);

  lcd.setCursor(0, 0);
  lcd.print("Nem: ");
  lcd.print(nemDegeri);
  lcd.print("    "); 

  if (!pompaCalisiyor && nemDegeri > nemEsik) {
    digitalWrite(rolePin, HIGH);
    pompaBaslangicZamani = millis();
    pompaCalisiyor = true;

    lcd.setCursor(0, 1);
    lcd.print("Pompa: CALISTI ");
    Serial.println("Pompa calisti");
  }

  if (pompaCalisiyor && (millis() - pompaBaslangicZamani >= pompaCalismaSuresi)) {
    digitalWrite(rolePin, LOW);
    pompaCalisiyor = false;

    lcd.setCursor(0, 1);
    lcd.print("Pompa: DURDU   ");
    Serial.println("Pompa durdu");
  }

  delay(500); 
}