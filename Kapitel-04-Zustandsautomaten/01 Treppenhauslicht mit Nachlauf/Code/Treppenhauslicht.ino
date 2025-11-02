// Zustände definieren
enum State { AUS, AN, COUNTDOWN };
State state = State.AUS;

// Eingänge (Taster + Endschalter)
const int TASTER = 2;
const int LAMPE = 5;
const unsigned long WarteZeit = 3000; //3000ms == 3s

void setup() {
   pinMode(TASTER, INPUT_PULLUP);
   pinMode(LAMPE, OUTPUT);

   digitalwrite(LAMPE, LOW);
}

void loop() {
  unsigned long startZeit;
  unsigned long aktuelleZeit;

  // put your main code here, to run repeatedly:
  switch(state)
  {
    case State.AUS:
    {
      if(digitalread(TASTER) == LOW)
      {
        state = State.AN;
      }
    }
    break;

    case State.AN:
    {
      digitalwrite(LAMPE, LOW);
      startZeit = millis();
      state = State.COUNTDOWN;
    }
    break;

    case State.COUNTDOWN:
    {
      if((millis() - startZeit) >= WarteZeit)
      {
        digitalwrite(LAMPE, LOW);
        state = State.AUS;
      }
    }
    break;
  }
}
