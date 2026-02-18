// Zustände definieren
enum State { WARTEN, AUSWAHL, AUSGABE, RUECKGABE };
State state = State.WARTEN;
// Arduino zur Steuerung einer Zugangskontrolle
// die Bibliothek Servo.h wird eingebunden, sie steuert den Motor
#include „Servo.h“  
// der Servomotor erhält den Namen Servomotor
Servo Servomotor;

// Eingänge (Taster + Endschalter)
const int MUENZE = 2;
const int AUSWAHL = 3;

unsigned long startTime;
unsigned long waitTime;

void setup() {
  //Eingang
   pinMode(MUENZE, INPUT_PULLUP);
   pinMode(AUSWAHL, INPUT_PULLUP);
   //Ausgang, Servomotor wird Pin 8 zugeordnet
  Servomotor.attach(SERVO);  
  //Serielle Schnittstelle initialisieren
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(state)
  {
    case State.WARTEN:
    {
      if(digitalread(MUENZE) == LOW)
      {
        Serial.println("Muenze eingeworfen!");
        state = State.AUSWAHL;
      }
      delay(50);
    }
    break;

    case State.AUSWAHL:
    {
      if(digitalread(AUSWAHL) == LOW)
      {
        Serial.println("Auswahl getroffen!");
        startTimer(1000);
        Servomotor.write(90); 
        state = State.AUSGABE;
      }
      delay(50);
    }
    break;

    case State.AUSGABE:
    {
        if(isTimeOut())
        {
          Servomotor.write(0); 
          Serial.println("Getraenk ausgeworfen!");
          state = State.RUECKGABE;
        }
    }
    break;

    case State.RUECKGABE:
    {
        Serial.println("Wechselgeld ausgegeben!");
        state = State.WARTEN;
    }
    break;
  }

  void StartTimer(unsigned long wtime)
  {
     startTime = millis(); 
     waitTime = wtime;
  }

  bool isTimeOut()
  {
      unsigned long actTime = millis();
      if((actTime - startTime) >= waitTime)
      {
        return(true);
      }
      return(false);
  }
}