//Arduino als universeller Logikbaustein
const int IN_PIN_A = 2;
const int IN_PIN_B = 3;
const int OUT_PIN_Q = 5;

int command = 'U';

void setup() {
  // Serielle Schnittstelle initialisieren
  Serial.begin(19200);
  ShowBehaviour();
  //Eingänge
  pinMode(IN_PIN_A, INPUT);
	pinMode(IN_PIN_B, INPUT);
	//Ausgang
	pinMode(OUT_PIN_Q, OUTPUT);
}

void loop() {
  bool q = false;
	bool a = digitalRead(IN_PIN_A) == LOW;
  bool b = digitalRead(IN_PIN_B) == LOW;
  int ret;

  if (Serial.available() > 0) 
  {
    command = Serial.read();      // Save character received.
    ret = Serial.read();          // Save character received <return>.
    command &= ~0x20;             //Kleinbuchstaben in Grossbuchstaben ändern
    ShowBehaviour();
  }
  
  switch(command)
  {
    case 'U':   //UND
    {
      q = a && b;
    }
    break;

    case 'O':   //ODER
    {
      q = a || b;
    }
    break;

    case 'A':   //NAND
    {
      q = !(a && b);
    }
    break;

    case 'N':   //NOR
    {
      q = !(a || b);
    }
    break;

	  case 'E': //EXOR
    {
      q = a ^ b;
    }
    break;

    case 'X': //EXNOR
    {
      q = !(a ^ b);
    }
    break;
  }

  /*Serial.print("Command: ");
  Serial.print(command);
  Serial.println();
  Serial.print("A: ");
  Serial.print(a);
  Serial.println();
  Serial.print("B: ");
  Serial.print(b);
  Serial.println();
  Serial.print("Q: ");
  Serial.print(q);
  Serial.print("\n-----\n");*/
  digitalWrite(OUT_PIN_Q, q ? HIGH : LOW);
  delay(500);
}

void ShowBehaviour(void)
{
  switch(command)
  {
    case 'U':   //UND
    {
      Serial.print("Arduino arbeitet als UND.\n");
    }
    break;

    case 'O':   //ODER
    {
      Serial.print("Arduino arbeitet als ODER.\n");
    }
    break;

    case 'A':   //NAND
    {
      Serial.print("Arduino arbeitet als NAND.\n");
    }
    break;

    case 'N':   //NOR
    {
      Serial.print("Arduino arbeitet als NOR.\n");
    }
    break;

    case 'E': //EXOR
    {
      Serial.print("Arduino arbeitet als XOR.\n");
    }
    break;

    case 'X': //EXNOR
    {
      Serial.print("Arduino arbeitet als XNOR.\n");
    }
    break;
  }
}
