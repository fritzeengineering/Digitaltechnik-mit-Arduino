// -----------------------------
// Ampel mit Fußgängerüberweg (FSM, nicht-blockierend)
// Pins anpassen nach Bedarf
// -----------------------------
enum State { KFZ_GRUEN, KFZ_GELB, KFZ_ROT_BEFORE_PED, FUSS_GRUEN, FUSS_BLINK, KFZ_ROT_GELB };
State state = KFZ_GRUEN;

// Pinzuordnung
const int KFZ_RED = 2;
const int KFZ_YEL = 3;
const int KFZ_GRN = 4;
const int PED_RED = 5;
const int PED_GRN = 6;
const int BUTTON  = 7;
const int BUZZER  = 8; // optional

// Zeiten (ms)
const unsigned long KFZ_GRUEN_MIN = 8000UL;
const unsigned long KFZ_GELB_TIME = 2000UL;
const unsigned long KFZ_ROT_BEFORE_PED = 1000UL;
const unsigned long PED_GRN_TIME = 7000UL;
const unsigned long PED_BLINK_DURATION = 3000UL; // letzte 3s blinken
const unsigned long KFZ_ROT_GELB_TIME = 2000UL;

// Laufvariablen
unsigned long stateStart = 0;
bool pedRequest = false;

// Entprell
unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 50UL;

void setup() {
  pinMode(KFZ_RED, OUTPUT);
  pinMode(KFZ_YEL, OUTPUT);
  pinMode(KFZ_GRN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PED_GRN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  setState(KFZ_GRUEN);
}

void loop() {
  checkButton();
  unsigned long now = millis();

  switch(state) {
    case KFZ_GRUEN:
      // Mindestgrün respektieren; falls Anfrage und Mindestzeit abgelaufen -> Gelb
      if (pedRequest && (now - stateStart >= KFZ_GRUEN_MIN)) {
        setState(KFZ_GELB);
      }
      break;

    case KFZ_GELB:
      if (now - stateStart >= KFZ_GELB_TIME) {
        setState(KFZ_RED_BEFORE_PED);
      }
      break;

    case KFZ_RED_BEFORE_PED:
      if (now - stateStart >= KFZ_ROT_BEFORE_PED) {
        setState(FUSS_GRUEN);
      }
      break;

    case FUSS_GRUEN: {
      unsigned long elapsed = now - stateStart;
      if (elapsed >= PED_GRN_TIME) {
        setState(KFZ_ROT_GELB);
      } else if (elapsed >= (PED_GRN_TIME - PED_BLINK_DURATION)) {
        // in Blinkphase: we switch to FUSS_BLINK to manage blinking
        setState(FUSS_BLINK);
      }
      break;
    }

    case FUSS_BLINK: {
      unsigned long elapsed = now - stateStart;
      if (elapsed >= PED_BLINK_DURATION) {
        // Blinken vorbei -> Rückkehr zu KFZ rot/gelb
        setState(KFZ_ROT_GELB);
      } else {
        // Blinklogik: blinke die Fußgängergrün-LED
        // Wir implementieren sichtbar blinkendes Verhalten via millis
        unsigned long t = now % 500; // 500ms period
        digitalWrite(PED_GRN, (t < 250) ? HIGH : LOW); // 50% Duty
      }
      break;
    }

    case KFZ_ROT_GELB:
      if (now - stateStart >= KFZ_ROT_GELB_TIME) {
        // zurück zu grün
        pedRequest = false; // Anfrage verarbeiten
        setState(KFZ_GRUEN);
      }
      break;
  }
}

// Hilfsfunktionen

void setState(State s) {
  state = s;
  stateStart = millis();
  // Alle LEDs standardmäßig ausschalten vor Setzen
  digitalWrite(KFZ_RED, LOW);
  digitalWrite(KFZ_YEL, LOW);
  digitalWrite(KFZ_GRN, LOW);
  digitalWrite(PED_RED, LOW);
  digitalWrite(PED_GRN, LOW);
  digitalWrite(BUZZER, LOW);

  switch(s) {
    case KFZ_GRUEN:
      digitalWrite(KFZ_GRN, HIGH);
      digitalWrite(PED_RED, HIGH);
      break;
    case KFZ_GELB:
      digitalWrite(KFZ_YEL, HIGH);
      digitalWrite(PED_RED, HIGH);
      break;
    case KFZ_RED_BEFORE_PED:
      digitalWrite(KFZ_RED, HIGH);
      digitalWrite(PED_RED, HIGH);
      break;
    case FUSS_GRUEN:
      digitalWrite(KFZ_RED, HIGH);
      digitalWrite(PED_GRN, HIGH);
      break;
    case FUSS_BLINK:
      digitalWrite(KFZ_RED, HIGH);
      // PED_GRN will be blinked in loop
      break;
    case KFZ_ROT_GELB:
      digitalWrite(KFZ_RED, HIGH);
      digitalWrite(KFZ_YEL, HIGH);
      digitalWrite(PED_RED, HIGH);
      break;
  }
}

// Button mit Entprellung prüfen
void checkButton() {
  int raw = digitalRead(BUTTON); // INPUT_PULLUP => LOW = gedrückt
  unsigned long now = millis();
  if (raw == LOW) {
    if (now - lastButtonTime > debounceDelay) {
      // Taste erkannt
      pedRequest = true;
      // optional: akustisches Signal
      tone(BUZZER, 1000, 100);
      lastButtonTime = now;
    }
  }
}
