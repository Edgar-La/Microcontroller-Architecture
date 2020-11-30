#include <LiquidCrystal.h>


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Contador = 0;
//int Boton = 2;
const byte interruptPin = 2;


void setup() {
  //pinMode(Boton, INPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("El conteo es:");
  //attachInterrupt(digitalPinToInterrupt(interruptPin), conteo, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin), conteo, FALLING);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(Contador);
}

void conteo() {
  Contador++;
}
