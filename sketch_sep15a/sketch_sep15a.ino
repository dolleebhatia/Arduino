void setup () {
  pinMode (2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop () {
  if (digitalRead(2) == HIGH) {
    digitalWrite (3, HIGH);
    digitalWrite(4, LOW);
  }
  else {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  }

}

