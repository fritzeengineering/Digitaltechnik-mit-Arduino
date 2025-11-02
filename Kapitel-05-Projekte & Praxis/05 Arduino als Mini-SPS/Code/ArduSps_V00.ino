// --- Minimal-AWL-Interpreter auf Arduino ---
// Syntax-Beispiel (über Serial):
// U E 0.1
// U E 0.2
// = A 0.0

#define MAX_LINES 20

struct ScriptInstr {
  char op;          // 'U' (AND), 'O' (OR), '=' (assign)
  bool negate;      // für UN, ON
  int pin;          // Arduino-Pin
  bool isInput;     // true = Eingang (E), false = Ausgang (A)
};

ScriptInstr script[MAX_LINES];
int scriptLen = 0;

void setup() {
  Serial.begin(19200);
  Serial.println("AWL-Interpreter gestartet.");
  Serial.println("Beispiel:");
  Serial.println("  U E 2");
  Serial.println("  U E 3");
  Serial.println("  = A 8");

  //Eingänge
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  //Ausgang
  pinMode(8, OUTPUT);
}

void loop()
{
  // Programm über Serial einlesen
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) parseLine(line);
  }

  // SPS-Zyklus
  executeProgram();
  delay(10); // Zykluszeit
}

void executeProgram() 
{
  bool RLO = false; // Result of Logic Operation
  
  for (int n = 0; n < scriptLen; n++) 
  {
    ScriptInstr ins = script[n];
    bool val = false;

    if (ins.isInput) {
      val = (digitalRead(ins.pin) == LOW); // Taster aktiv LOW
    }

    if (ins.negate) 
    {
      val = !val;
    }

    switch (ins.op) {
      case 'U': // AND
      {
          if(n == 0) 
          {
            RLO = val;
          }
          else 
          {
            RLO = RLO && val;
          }
      }
      break;

      case 'O': // OR
       {
          if(n == 0) 
          {
            RLO = val;
          }
          else 
          {
            RLO = RLO || val;
          }
      }
      break;

      case '=': // assign
      {
        digitalWrite(ins.pin, RLO ? HIGH : LOW);
      }
      break;
    }
  }
  delay(10); // Zykluszeit
}

// --- Parser für AWL-Syntax ---
void parseLine(String line) 
{
  ScriptInstr ins;
  ins.op = 0;
  ins.negate = false;

  line.trim();
  line.replace("  ", " ");

  if(line.startsWith("U "))
  {
    ins.op = 'U';
    ins.negate = false;
  }

  if(line.startsWith("UN "))
  {
    ins.op = 'U';
    ins.negate = true;
  }

  if(line.startsWith("O "))
  {
    ins.op = 'O';
    ins.negate = false;
  }

  if(line.startsWith("ON ")) 
  {
    ins.op = 'O';
    ins.negate = true;
  }

  if (line.startsWith("=")) 
  {
    ins.op = '=';
  }

  // Teile aufsplitten
  int space = line.indexOf(' ');
  String rest = line.substring(space + 1); //.trim();

  if (rest.startsWith("E")) 
  {
    ins.isInput = true;
    ins.pin = rest.substring(1).toInt(); // z.B. "E2" → Pin 2
  } 
  else if (rest.startsWith("A")) 
  {
    ins.isInput = false;
    ins.pin = rest.substring(1).toInt(); // z.B. "A8" → Pin 8
  }

  if (scriptLen < 20)
  {
    script[scriptLen++] = ins;
    /*if (ins.isInput) 
    {
      pinMode(ins.pin, INPUT_PULLUP);
    }
    else 
    {
      pinMode(ins.pin, OUTPUT);
    }*/
    
    Serial.print("Instr hinzugefügt: ");
    Serial.println(line);
  }
}



