int value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
}
void loop() {
  value = Serial.read();
  delay(5);
  if (value == '1')
  {
    digitalWrite(10, HIGH);
    Serial.println("Led prendido");
  }
  else if (value == '0')
  {
    digitalWrite(10, LOW);
    Serial.println("Led apagado");
  }

}
