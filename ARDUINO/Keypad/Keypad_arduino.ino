#include <Keypad.h>
#include <string.h>
int LED_O = 12;
int LED_C = 13;
int edo_btns = 0;

char password[] = "1234";
char pass_check[4];
int cont = 0;

const byte filas = 4; 
const byte colum = 4;
char teclas[filas][colum] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', 'x'},
  {'1', '2', '3', '-'},
  {'O', '0', '=', '+'}
};

byte filas_Pines[filas] = {9, 8, 7, 6}; 
byte colum_Pines[colum] = {5, 4, 3, 2}; 

Keypad teclado = Keypad(makeKeymap(teclas), filas_Pines, colum_Pines, filas, colum); 

void setup(){
  Serial.begin(9600);
  pinMode(LED_O, OUTPUT);
  pinMode(LED_C, OUTPUT);
  digitalWrite(LED_C, !edo_btns);
}
  
void loop(){
  char customKey = teclado.getKey();
  if (customKey != NO_KEY){
    digitalWrite(LED_C, HIGH);
    pass_check[cont] = customKey;
    Serial.println(pass_check[cont]);
    cont = cont + 1;
    if (cont == 4)
    {
      if(pass_check[0] == password[0]&&pass_check[1] == password[1]&&pass_check[2] == password[2]&&pass_check[3] == password[3])
      {
        digitalWrite(LED_O, !edo_btns);
        digitalWrite(LED_C, edo_btns);
        Serial.println("Abierto");
        delay(500);
        Serial.println("...Cerrando...");
        delay(2000);
        digitalWrite(LED_O, edo_btns);
        digitalWrite(LED_C, !edo_btns);
        Serial.println("Cerrado");}
      cont = 0;
    }
  }
}
