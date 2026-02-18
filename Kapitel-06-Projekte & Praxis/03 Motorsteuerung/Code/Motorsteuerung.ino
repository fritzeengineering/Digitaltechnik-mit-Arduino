// Motorsteuerung mit Start/Stopp-Taster
// Motor an Pin 8 (Relais oder Transistor)
// Start-Taster an Pin 2, Stopp-Taster an Pin 3

const int startButton = 2;
const int stopButton  = 3;
const int motorPin    = 8;

bool motorOn = false;

void setup() {
  pinMode(startButton, INPUT_PULLUP); // Taster gegen GND
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW); // Motor aus
}

void loop() {
  // Start-Taster gedrückt → Motor EIN
  if (digitalRead(startButton) == LOW) {
    motorOn = true;
    delay(50); // Entprellen
  }

  // Stopp-Taster gedrückt → Motor AUS
  if (digitalRead(stopButton) == LOW) {
    motorOn = false;
    delay(50); // Entprellen
  }

  // Motorstatus setzen
  digitalWrite(motorPin, motorOn ? HIGH : LOW);
}
