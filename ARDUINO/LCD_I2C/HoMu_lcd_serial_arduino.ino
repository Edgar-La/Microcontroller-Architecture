//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x20,16,2);  // run ic2_scanner sketch and get the IC2 address, which is 0x3f in my case,it could be 0x3f in many cases
 
void setup()
{
  //lcd.init(); //Inicia pantalla led
  lcd.begin(16, 2);
  //Cursor en la posicion 3,0
  lcd.setCursor(3, 0);
  lcd.backlight();
  lcd.print("Hola mundo!");
  lcd.setCursor(7,1);
  lcd.print(":)");
}
 
void loop()
{

}
