void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  delay(500);
  digitalWrite(5,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  delay(500);
}
