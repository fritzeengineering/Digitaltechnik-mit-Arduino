// 4-Bit Schieberegister vorwärts mit Arduino
// LEDs an Pins 8-11 (Q0-Q3)
// Taster an Pin 2 als Clock-Eingang
// Taster an Pin 3 als Data-Eingang

const int clockPin = 2;             // Takt-Taster
const int dataPin = 3;             // Takt-Taster
const int outputs[4] = {8, 9, 10, 11}; // LEDs = Schieberegister-Ausgänge

unsigned char shiftReg = 0b0001; // Startmuster (nur Bit0 aktiv)
int lastClockState = HIGH;

void setup() {
  //Eingänge
  pinMode(clockPin, INPUT_PULLUP); // Taster mit Pullup
  pinMode(dataPin, INPUT_PULLUP); // Taster mit Pullup
  //Ausgänge
  for (int n = 0; n < 4; n++) {
    pinMode(outputs[n], OUTPUT);
    digitalWrite(outputs[n], LOW);
  }
  digitalWrite(outputs[0], HIGH);
}

void loop() {
  int clockState = digitalRead(clockPin);
  int dataState = digitalRead(dataPin);   // aus 0 wird eine 1 und umgekehrt

  // Flankenerkennung (fallend)
  if (lastClockState == HIGH && clockState == LOW) {
    // Muster eins nach links schieben
    shiftReg <<= 1;

    // Falls das MSB rausfällt, von vorne beginnen
    if (shiftReg > 0b1000) {
      shiftReg = 0b0001;
      shiftReg |= dataState;
    }

    // Ausgabe auf LEDs
    for (int n = 0; n < 4; n++) {
      int bitVal = (shiftReg >> n) & 0x01;
      digitalWrite(outputs[n], bitVal==1 ? HIGH : LOW);
    }
    delay(50); // Entprellen
  }
  lastClockState = clockState;
}
