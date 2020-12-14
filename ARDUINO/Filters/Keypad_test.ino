#include <Keypad.h>
#include <string.h>
int LED_C = 13, edo_btns = 0;

char password[] = "1234";
String pass_check = "";

const byte filas = 4; 
const byte colum = 4;
char teclas[filas][colum] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'.', '0', '='}
};

byte filas_Pines[filas] = {5, 4, 3, 2}; 
byte colum_Pines[colum] = {8, 7, 6}; 

Keypad teclado = Keypad(makeKeymap(teclas), filas_Pines, colum_Pines, filas, colum); 

void setup(){
  Serial.begin(9600);
  pinMode(LED_C, OUTPUT);
  digitalWrite(LED_C, !edo_btns);
  Serial.println("Digite '1234'");
}
  
void loop(){
  char customKey = teclado.getKey();
  if (customKey != NO_KEY){
    digitalWrite(LED_C, HIGH);
    pass_check += customKey;
    Serial.println(customKey);
      if (pass_check == password)
      {
        digitalWrite(LED_C, edo_btns);
        Serial.println("Iniciando"); delay(500);
        Serial.println(pass_check);
        Serial.println("...Testeando...");delay(2000);
        
        digitalWrite(LED_C, !edo_btns);
        
        Serial.println("Testado");
        pass_check = "";
        }
  }
}
