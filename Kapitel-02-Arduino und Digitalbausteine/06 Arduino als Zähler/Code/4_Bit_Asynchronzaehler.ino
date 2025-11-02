// 4-Bit Asynchronzähler (Vorwärtszähler) mit Arduino
// Ausgabe über LEDs an D8-D11
// Takt per Taster an D2

const int clockPin = 2;             // Taster als "Clock"
const int outputs[4] = {8, 9, 10, 11}; // LEDs für Q0-Q3 (LSB → MSB)
int lastClockState = HIGH;
unsigned char counter = 0;       // Zählerstand 0..15

void setup() {
  pinMode(clockPin, INPUT_PULLUP); // Taster mit Pullup
  for (int n = 0; n < 4; n++) {
    pinMode(outputs[n], OUTPUT);
    digitalWrite(outputs[n], LOW);
  }
}

void loop() {
  int clockState = digitalRead(clockPin);

  // Flanke erkennen (fallend: HIGH -> LOW)
  if (lastClockState == HIGH && clockState == LOW) {
    counter = (counter + 1) & 0x0F; // auf 4 Bit begrenzen (0..15)

    // Bits auf LEDs ausgeben
    for (int n = 0; n < 4; n++) {
      int bitVal = (counter >> n) & 0x01; // i-tes Bit auslesen
      digitalWrite(outputs[n], bitVal==1 ? HIGH : LOW);
    }
    delay(50); // Entprellen
  }
  lastClockState = clockState;
}
