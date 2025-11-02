// Arduino zur Sicherheitsverriegelung
const int BEWEGUNG = 2;
const int TUER_KONTAKT = 3;
const int FENSTER = 4;
const int GLASBRUCH = 5;
const int SIRENE = 8;
const int ALARM = 9;

void setup() 
{
  //Eingänge
  pinMode(BEWEGUNG, INPUT_PULLUP);
  pinMode(TUER_KONTAKT, INPUT_PULLUP);
  pinMode(FENSTER, INPUT_PULLUP);
  pinMode(GLASBRUCH, INPUT_PULLUP);
  //Ausgang
  pinMode(SIRENE, OUTPUT); 
  pinMode(ALARM, OUTPUT); 
}

void loop() 
{
  bool bw, tk, fe, gb, si, al;

    bw = digitalread(BEWEGUNG) == LOW; 	//Eingänge einlesen 
    tk = digitalread(TUER_KONTAKT) == LOW; 
    fe = digitalread(FENSTER) == LOW;		
    gb = digitalread(GLASBRUCH) == LOW;		

    si = (bw && tk);    //Signale verknüpfen
    al = si && (fe || gb);

    if(si)
    {
      #ifdef PASSIVE_BUZZER
        tone(SIRENE, 1000);          // Sende 1KHz Tonsignal, passiver Buzzer
      #endif

      #ifdef ACTIVE_BUZZER
        digitalWrite(SIRENE, HIGH); // aktiver Buzzer
      #endif
    }
    else
    {
      #ifdef PASSIVE_BUZZER
        tone(SIRENE, 1000);          // Sende 1KHz Tonsignal, passiver Buzzer
      #endif

      #ifdef ACTIVE_BUZZER
        digitalWrite(SIRENE, LOW);  // aktiver Buzzer
      #endif
    }

    if(al)
    {
      digitalWrite(ALARM, HIGH); // Alarm!
    }
    else
    {
      digitalWrite(ALARM, LOW); 
    }
}
