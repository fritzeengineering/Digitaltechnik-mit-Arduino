// Zustände definieren
enum State { WARTEN, TICKET, SCHRANKE_AUF, AUTO_EIN, SCHRANKE_ZU };
State state = State.AUS;
// Arduino zur Steuerung einer Zugangskontrolle
// die Bibliothek Servo.h wird eingebunden, sie steuert den Motor
#include „Servo.h“  
// der Servomotor erhält den Namen Servomotor
Servo Servomotor;

// Eingänge (Taster + Endschalter)
const int AUTO = 2;
const int TICKET = 3;

unsigned long startTime;
unsigned long waitTime;

void setup() {
  //Eingang
   pinMode(AUTO, INPUT_PULLUP);
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
      if(digitalread(AUTO) == LOW)
      {
        Serial.println("Auto erkannt!");
        state = State.TICKET;
      }
      delay(50);
    }
    break;

    case State.TICKET:
    {
      if(digitalread(TICKET) == LOW)
      {
          Serial.println("Ticket wird gezogen!");
          startTimer(1000);
          state = State.SCHRANKE_AUF;
      }
      delay(50);
    }
    break;

    case State.SCHRANKE_AUF:
    {
        Servomotor.write(150);    // Position 1 mit dem Winkel 150° ansteuern 
        if(isTimeOut())
        {
          Serial.println("Ticket gezogen, Schranke öffnet!");
          startTimer(5000);
          state = State.AUTO_EIN;
        }
    }
    break;

    case State.AUTO_EIN:
    {
        if(isTimeOut())     // Warte, bis Auto eingefahren ist.
        {
          Serial.println("Schranke geöffnet, Auto fährt ein.");
          startTimer(1000);
         state = State.SCHRANKE_ZU;
        }
        
    }
    break;

    case State.SCHRANKE_ZU:
    {
        Servomotor.write(0);    // Position 1 mit dem Winkel 150° ansteuern 
        if(isTimeOut())     // Warte, bis Auto eingefahren ist.
        {
          Serial.println("Schranke geschlossen.");
          state = State.WARTEN;
        }
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