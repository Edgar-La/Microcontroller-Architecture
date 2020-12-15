//PROGRAMA: Filtros PASA-ALTAS, PASA-BAJAS, PASA-BANDAS Y RECHAZA BANDAS.
//ALUMNOS: Cardenas Aguilar Uriel & Lara Arellano Edgar
//FECHA: 14 de diciembre de 2020

//-----------------------Seccion librerias y variables--------------------------
#include <Keypad.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
String tecladillo = "";
String Status = "Inicio"; int Filtro;

const int ledPH = 9; const int ledPL = 10;
const int ledBP = 11;const int ledSB = 12;
float ALFA_F = 0; float ALFA_f_get = 0; String ALFA_S = "";
float ALFA_PH, ALFA_PL, ALFA_BP_1, ALFA_BP_2, ALFA_SB_1, ALFA_SB_2;
float LP = 0; float HP = 0; float ruido = 0; float LP_LOW = 0;
float LP_HIGH = 0; float Pasa_Banda = 0; float Rechaza_Banda = 0;
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
Keypad teclado = Keypad(makeKeymap(teclas),
filas_Pines, colum_Pines, filas, colum);
 
//-----------------------Seccion LCD I2C---------------------------------------
LiquidCrystal_I2C lcd(0x20,32,2);

//-----------------------Seccion setup-----------------------------------------
void setup(){
  Serial.begin(9600);
  //-----------LEDS
  pinMode(ledPH , OUTPUT); pinMode(ledPL , OUTPUT);
  pinMode(ledBP , OUTPUT); pinMode(ledSB , OUTPUT);
  //---------------
  lcd.begin(32, 2);
  lcd.setCursor(8, 0);
  lcd.backlight();
  lcd.print("Selec Filtro:");
  lcd.setCursor(6,1);
  lcd.print("1PH 2PL 3BP 4SB");
}

//-----------------------Seccion loop---------------------------------------------
void loop(){
  char customKey = teclado.getKey();
  ruido = analogRead(A0);
  
  if (customKey != NO_KEY){
        //Condicion para escoger el filtro
        if (Status == "Inicio") {   Filtro = customKey; Status = "Otro";    }
        //Si ya se esocgio se usa otra variable para otras cosas
        else {    tecladillo = ""; tecladillo = customKey;    }

        switch(Filtro){
          case '1': //Filtro Pasa altas
          //Condicion para teclear alfa
          if (PASAR == 1){  ALFA_PH = obtener_ALFA("1) High Pass", "Alfa = ");  }
          //Definida la alfa, muestra mensaje en LCD
          else if (PASAR == 2){  lcd.clear(); lcd.setCursor(2, 0);
          lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)"); 
          digitalWrite(ledPH , 1); digitalWrite(ledPL , 0); //Enciende LED
          digitalWrite(ledBP , 0); digitalWrite(ledSB , 0); //del filtro HP
          //Procede a entrar en ciclo para Filtrar y realizar SERIAL PLOT
          while(1){float filteredHP = HighPassFilter(ruido,ALFA_PH);
          Serial.print(ruido); Serial.print(","); Serial.println(filteredHP);} }
          break;
          
          case '2':   //Filtro Pasa bajas
          //Condicion para teclear alfa
          if (PASAR == 1){  ALFA_PL = obtener_ALFA("2) Low Pass", "Alfa = "); }
          //Definida la alfa, muestra mensaje en LCD
          else if (PASAR == 2){  lcd.clear(); lcd.setCursor(2, 0);
          lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)"); 
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 1);  //Enciende LED
          digitalWrite(ledBP , 0); digitalWrite(ledSB , 0);  //del filtro LP
          //Procede a entrar en ciclo para Filtrar y realizar SERIAL PLOT
          while(1){float filteredLP = LowPassFilter(ruido,ALFA_PL);
          Serial.print(ruido); Serial.print(","); Serial.println(filteredLP);}}
          break;
          
          case '3':   //Filtro Pasa banda
          if (PASAR == 1) { //Condicion para teclear alfa inf
            ALFA_BP_1 = obtener_ALFA( "3) Band Pass", "Alfa inferior= " );  }
          else if (PASAR == 2){ //Condicion para teclear alfa sup
            ALFA_BP_2 = obtener_ALFA("Digite ahora", "Alfa superior= ");  }
          //Definidas las alfas, muestra mensaje en LCD
          else if (PASAR == 3){ lcd.clear(); lcd.setCursor(2, 0);
          lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)");  
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  //Enciende LED 
          digitalWrite(ledBP , 1); digitalWrite(ledSB , 0);  //del filtro BP
          //Procede a entrar en ciclo para Filtrar y realizar SERIAL PLOT
          while(1){float filteredBP = BandPassFilter(ruido,ALFA_BP_1,ALFA_BP_2);
          Serial.print(ruido); Serial.print(","); Serial.println(filteredBP);}}
          break;
          
          case '4':   //Filtro Rechaza banda
          if (PASAR == 1) {   //Condicion para teclear alfa inf
            ALFA_SB_1 = obtener_ALFA("4) Band Stop", "Alfa inferior= ");  }
          else if (PASAR == 2){     //Condicion para teclear alfa sup
            ALFA_SB_2 = obtener_ALFA("Digite ahora", "Alfa superior= ");  }
          //Definidas las alfas, muestra mensaje en LCD
          else if (PASAR == 3){   lcd.clear(); lcd.setCursor(2, 0);
          lcd.print("Ya estoy"); lcd.setCursor(2, 1); lcd.print("filtrando :)");   
          digitalWrite(ledPH , 0); digitalWrite(ledPL , 0);  //Enciende LED
          digitalWrite(ledBP , 0); digitalWrite(ledSB , 1);  //del filtro SB
          //Procede a entrar en ciclo para Filtrar y realizar SERIAL PLOT
          while(1){float filteredBS = BandStopFilter(ruido,ALFA_SB_1,ALFA_SB_2);
          Serial.print(ruido); Serial.print(","); Serial.println(filteredBS);}}
          break;
          }
    }
}

//Funcion para ALFA---------------------------------------------------------
//Esta funcion se llama cada que se requiera definir una alfa
float obtener_ALFA(String Tipo_filtro,String Alfa_igual)
{
          if (tecladillo != "=")
          {
            lcd.clear(); lcd.setCursor(8, 0); lcd.print(Tipo_filtro);
            ALFA_S += tecladillo;   //Conforme se teclea se va a concatenar
            lcd.setCursor(2, 1); lcd.print(Alfa_igual);
            lcd.setCursor(17,1); lcd.print(ALFA_S); Serial.println(tecladillo);
          }
          else  //Si ya se dio click en =, se procede a esto
          {
            ALFA_f_get = ALFA_S.toFloat();  //Se realiza conversion a flotante
            lcd.clear(); lcd.setCursor(10, 0); lcd.print(Alfa_igual);
            lcd.setCursor(17,1);
            //Se muestra ALFA en LCD y terminal serial
            lcd.print(ALFA_f_get); Serial.println(ALFA_f_get);
            //Se incrementa para proseguir con lo que requiera el switch
            PASAR++;
            ALFA_S = ""; 
            return ALFA_f_get;    //Rgresa el valor que necesitan los filtros
          }          
}

//Filtro PASA BAJAS---------------------------------------------------------
float LowPassFilter(int value, float alfa)
{
   LP = alfa * value + (1 - alfa) * LP;
   return LP;
}

//Filtro PASA ALTAS---------------------------------------------------------
float HighPassFilter(int value, float alfa)
{
   LP = alfa * value + (1 - alfa) * LP;
   HP = value - LP;
   return HP;
}

//Filtro PASA BANDA---------------------------------------------------------
float BandPassFilter(int value, float alfa_LOW, float alfa_HIGH)
{
   LP_LOW = alfa_LOW * value + (1 - alfa_LOW) * LP_LOW;
   LP_HIGH = alfa_HIGH * value + (1 - alfa_HIGH) * LP_HIGH;
   Pasa_Banda = LP_HIGH - LP_LOW;
   return Pasa_Banda;
}

//Filtro RECHAZA BANDA---------------------------------------------------------
float BandStopFilter(int value, float alfa_LOW, float alfa_HIGH)
{
   LP_LOW = alfa_LOW * value + (1 - alfa_LOW) * LP_LOW;
   LP_HIGH = alfa_HIGH * value + (1 - alfa_HIGH) * LP_HIGH;
   Pasa_Banda = LP_HIGH - LP_LOW;
   Rechaza_Banda = value - Pasa_Banda;
   return Rechaza_Banda;
}
