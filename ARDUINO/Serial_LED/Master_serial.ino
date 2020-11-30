int value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
}

void loop() {
  value = digitalRead(7);
  if (value == HIGH)
    Serial.print(0);  //manda byte valor 0
  else
    Serial.print(1);  //manda byte valor 1
}
