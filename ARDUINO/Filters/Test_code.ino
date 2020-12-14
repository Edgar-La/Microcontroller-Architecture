#include <Keypad.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
String tecladillo = "";
String Status = "Inicio"; int Filtro;// = "";

const int ledPH = 9; const int ledPL = 10; const int ledBP = 11; const int ledSB = 12;
float ALFA_F = 0;
String ALFA_S = "";

//-----------------------Seccion KEYPAD---------------------------------------
const byte filas = 4; 
const byte colum = 3;
char teclas[filas][colum] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'.', '0', '='}
};
byte filas_Pines[filas] = {5, 4, 3, 2}; 
byte colum_Pines[colum] = {8, 7, 6}; 
Keypad teclado = Keypad(makeKeymap(teclas), filas_Pines, colum_Pines, filas, colum); 
//-----------------------Seccion LCD I2C---------------------------------------
LiquidCrystal_I2C lcd(0x20,16,2);
//-----------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  //-----------LEDS
  pinMode(ledPH , OUTPUT); pinMode(ledPL , OUTPUT); pinMode(ledBP , OUTPUT); pinMode(ledSB , OUTPUT);
  //---------------
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.backlight();
  lcd.print("Selec Filtro:");
  lcd.setCursor(0,1);
  lcd.print("1PH 2PL 3BP 4SB");
}
//-----------------------------------------------------------------------------
void loop(){
  char customKey = teclado.getKey();
  if (customKey != NO_KEY){
        if (Status == "Inicio") {   Filtro = customKey; Status = "Otro";    }
        else {    tecladillo = ""; tecladillo = customKey;    }

        switch(Filtro){
          case '1':
          lcd.clear(); lcd.setCursor(1, 0); lcd.print("1) High Pass");
          lcd.setCursor(1, 1); lcd.print("Digite alfa:");
          if (tecladillo != "=")
          {
            ALFA_S += tecladillo;
            lcd.clear(); lcd.setCursor(6, 0); lcd.print("Alfa = ");
            lcd.setCursor(5,1); lcd.print(ALFA_S); Serial.println(tecladillo);
          }
          else{ALFA_F = ALFA_S.toFloat();
          lcd.clear(); lcd.setCursor(6, 0); lcd.print("Alfa = ");
          lcd.setCursor(5,1); lcd.print(ALFA_F); Serial.println(ALFA_F);
          }
          digitalWrite(ledPH , 1); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 0);
          Serial.println(customKey);
          break;
          
          case '2':
          lcd.clear(); lcd.setCursor(2, 0); lcd.print("2) Low Pass");
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 1);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 0);
          Serial.println(customKey);
          break;
          case '3':
          
          lcd.clear(); lcd.setCursor(2, 0); lcd.print("3) Band Pass");
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 1); digitalWrite(ledSB , 0);
          Serial.println(customKey);
          break;
          
          case '4':
          lcd.clear(); lcd.setCursor(2, 0); lcd.print("4) Band Stop");
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 1);
          Serial.println(customKey);
          break;
          }
    }
}
