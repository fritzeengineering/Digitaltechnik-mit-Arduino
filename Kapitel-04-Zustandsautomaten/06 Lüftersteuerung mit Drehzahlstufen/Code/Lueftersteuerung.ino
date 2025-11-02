// Zustände definieren
enum State { AUS, STUFE_1, STUFE_2, STUFE_3 };
State state = State.AUS;

// Eingänge (Taster + Endschalter)
const int TASTER = 2;
const int STUFE_1 = 5;
const int STUFE_2 = 6;
const int STUFE_3 = 7;
const unsigned long WarteZeit = 3000; //3000ms == 3s

void setup() {
  //Eingang
   pinMode(TASTER, INPUT_PULLUP);
  //Ausgänge
   pinMode(STUFE_1, OUTPUT);
   pinMode(STUFE_2, OUTPUT);
   pinMode(STUFE_3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(state)
  {
    case State.AUS:
    {
      digitalwrite(STUFE_1, LOW);
      digitalwrite(STUFE_2, LOW);
      digitalwrite(STUFE_3, LOW);
      if(tasterPress())
      {
        state = State.STUFE_1;
      }
    }
    break;

    case State.STUFE_1:
    {
      digitalwrite(STUFE1, HIGH);
      if(tasterPress())
      {
        state = State.STUFE_2;
      }
    }
    break;

    case State.STUFE_2:
    {
        digitalwrite(STUFE_2, HIGH);
        if(tasterPress())
        {
          state = State.STUFE_3;
        }
    }
    break;

    case State.STUFE_3:
    {
        digitalwrite(STUFE_3, HIGH);
        if(tasterPress())
        {
          state = State.AUS;
        }
    }
    break;
  }

  bool tasterPressed()
  {
      if(digitalread(TASTER) == LOW)
      {
        return(true);
      }
      return(false);
      delay(50);
  }
}
