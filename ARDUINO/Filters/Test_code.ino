#include <Keypad.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
String tecladillo = "";
String Status = "Inicio"; int Filtro;

const int ledPH = 9; const int ledPL = 10; const int ledBP = 11; const int ledSB = 12;
float ALFA_F = 0; float ALFA_f_get = 0; String ALFA_S = "";
float ALFA_PH, ALFA_PL, ALFA_BP_1, ALFA_BP_2, ALFA_SB_1, ALFA_SB_2;
int PASAR = 1;


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
          if (PASAR == 1){  ALFA_PH = obtener_ALFA("1) High Pass", "Alfa = ");  }
          else if (PASAR == 2){  lcd.clear(); lcd.setCursor(2, 0); lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)"); }
          digitalWrite(ledPH , 1); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 0);
          break;
          
          case '2':
          if (PASAR == 1){  ALFA_PL = obtener_ALFA("2) Low Pass", "Alfa = "); }
          else if (PASAR == 2){   }
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 1);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 0);
          break;
          
          case '3':
          if (PASAR == 1) {  ALFA_BP_1 = obtener_ALFA("3) Band Pass", "Alfa1= ");  }
          else if (PASAR == 2){ALFA_BP_2 = obtener_ALFA("Digite ahora", "Alfa2= ");  }
          else if (PASAR == 3){   }
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 1); digitalWrite(ledSB , 0);
          break;
          
          case '4':
          if (PASAR == 1) {  ALFA_SB_1 = obtener_ALFA("4) Band Stop", "Alfa1= ");  }
          else if (PASAR == 2){ALFA_SB_2 = obtener_ALFA("Digite ahora", "Alfa2= ");  }
          else if (PASAR == 3){   lcd.clear(); lcd.setCursor(2, 0); lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)");   }
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  digitalWrite(ledBP , 0); digitalWrite(ledSB , 1);
          break;
          }
    }
}

float obtener_ALFA(String Tipo_filtro,String Alfa_igual)
{
          if (tecladillo != "=")
          {
            lcd.clear(); lcd.setCursor(1, 0); lcd.print(Tipo_filtro);
            ALFA_S += tecladillo;
            lcd.setCursor(0, 1); lcd.print(Alfa_igual);
            lcd.setCursor(6,1); lcd.print(ALFA_S); Serial.println(tecladillo);
          }
          else
          {
            ALFA_f_get = ALFA_S.toFloat();
            lcd.clear(); lcd.setCursor(6, 0); lcd.print(Alfa_igual);
            lcd.setCursor(7,1); lcd.print(ALFA_f_get); Serial.println(ALFA_f_get);
            PASAR++;
            ALFA_S = ""; //delay(30);
            return ALFA_f_get;
          }          
}
