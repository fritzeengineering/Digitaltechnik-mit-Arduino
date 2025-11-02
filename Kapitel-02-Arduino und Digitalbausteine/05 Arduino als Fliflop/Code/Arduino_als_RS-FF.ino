// Arduino simuliert Exklusiv-ODER-Glied
const int IN_PIN_A = 2;
const int IN_PIN_B = 3;
const int OUT_PIN_Q = 5;

void setup()
{
    //Eingänge
    pinMode(IN_PIN_A, INPUT_PULLUP);
    pinMode(IN_PIN_B, INPUT_PULLUP);
    //Ausgänge
    pinMode(OUT_PIN_Q, OUTPUT);
}

void loop()
{
    if (digitalRead(IN_PIN_A) == LOW) 
    {   // Taste gedrückt
      delay(50);                           // entprellen
      if (digitalRead(IN_PIN_A) == LOW) 
      { // nochmal prüfen
        digitalWrite(OUT_PIN_Q, HIGH); // LED toggeln
        while (digitalRead(IN_PIN_A) == LOW);      // warten bis losgelassen
      }
    }

    if (digitalRead(IN_PIN_B) == LOW) 
    {   // Taste gedrückt
      delay(50);                           // entprellen
      if (digitalRead(IN_PIN_B) == LOW) 
      { // nochmal prüfen
        digitalWrite(OUT_PIN_Q, LOW); // LED toggeln
        while (digitalRead(IN_PIN_B) == LOW);      // warten bis losgelassen
      }
    }
}
