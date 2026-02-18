// 4:1 Multiplexer Simulation mit Arduino
const int inputs[4] = {4, 5, 6, 7}; // Eingänge I0-I3
const int selectPins[2] = {2, 3};   // Steuerleitungen S0, S1
const int outPin = 13;              // Ausgang Q

void setup() {
  for (int n = 0; n < 4; n++)
  {
    pinMode(inputs[n], INPUT_PULLUP);
  } 
  for (int n = 0; n < 2; n++) 
  {
    pinMode(selectPins[n], INPUT_PULLUP);
  }
  pinMode(outPin, OUTPUT);
}

void loop() {
  int s0 = digitalRead(selectPins[0]) == LOW; // Steuerbit 0
  int s1 = digitalRead(selectPins[1]) == LOW; // Steuerbit 1

  int sel = (s1 << 1) | s0; // Binäre Auswahl (0–3)

  int y = digitalRead(inputs[sel]) == LOW; // aktiven Eingang auswählen

  digitalWrite(outPin, y ? HIGH : LOW);    // Ausgang setzen
}
