// Zustände definieren
enum State { GESCHLOSSEN, OEFFNET, OFFEN, SCHLIESST };
State state = GESCHLOSSEN;

// Eingänge (Taster + Endschalter)
const int tasterAuf = 2;
const int tasterZu = 3;
const int tasterStopp = 4;
const int endOben = 5;
const int endUnten = 6;

// Ausgänge (LEDs als Motor-Simulation)
const int motorAuf = 9;     // LED = Motor öffnet
const int motorZu = 10;     // LED = Motor schließt

void setup() {
  pinMode(tasterAuf, INPUT_PULLUP);
  pinMode(tasterZu, INPUT_PULLUP);
  pinMode(tasterStopp, INPUT_PULLUP);
  pinMode(endOben, INPUT_PULLUP);
  pinMode(endUnten, INPUT_PULLUP);

  pinMode(motorAuf, OUTPUT);
  pinMode(motorZu, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Motor standardmäßig aus
  digitalWrite(motorAuf, LOW);
  digitalWrite(motorZu, LOW);

  switch (state) {
    case GESCHLOSSEN:
      Serial.println("Tor: Geschlossen");
      if (digitalRead(tasterAuf) == LOW) {
        state = OEFFNET;
      }
      break;

    case OEFFNET:
      Serial.println("Tor: Öffnet");
      digitalWrite(motorAuf, HIGH);
      if (digitalRead(endOben) == LOW) {
        state = OFFEN;
      }
      if (digitalRead(tasterStopp) == LOW || digitalRead(tasterZu) == LOW) {
        state = GESCHLOSSEN;  // Abbruch oder sofort wieder schließen
      }
      break;

    case OFFEN:
      Serial.println("Tor: Offen");
      if (digitalRead(tasterZu) == LOW) {
        state = SCHLIESST;
      }
      break;

    case SCHLIESST:
      Serial.println("Tor: Schließt");
      digitalWrite(motorZu, HIGH);
      if (digitalRead(endUnten) == LOW) {
        state = GESCHLOSSEN;
      }
      if (digitalRead(tasterStopp) == LOW || digitalRead(tasterAuf) == LOW) {
        state = OFFEN; // Abbruch oder sofort wieder öffnen
      }
      break;
  }

  delay(200); // kleine Entprellung / Debug-Verzögerung
}

