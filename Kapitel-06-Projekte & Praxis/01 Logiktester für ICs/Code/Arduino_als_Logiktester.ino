// Arduino als Logiktester für SN7408,SN7400, SN7432 etc.
const int OUT_PIN_A = 2;
const int OUT_PIN_B = 3;
const int IN_PIN_Y = 5;

int signale[6][4] = { 0, 0, 0, 1,  //UND
                      0, 1, 1, 1,   //ODER
                      1, 1, 1, 0,   //NAND
                      1, 0, 0, 0,   //NOR
                      0, 1, 1, 0,   //EXOR
                      1, 0, 0, 1    //EXNOR
                    };  

String gatter[7] = { "UND", "ODER", "NAND", "NOR", "EXOR", "EXNOR", "N.A."};

void setup()
{
    //Ausgänge
    pinMode(OUT_PIN_A, OUTPUT);
    pinMode(OUT_PIN_B, OUTPUT);
    //Eingang
    pinMode(IN_PIN_Y, INPUT);
    //serielle Kommunikation
    Serial.begin(19200);
}

void loop()
{
    int y[4], index = 6, count=0;

    // A = 0, B = 0
    digitalWrite(OUT_PIN_A, LOW);
    digitalWrite(OUT_PIN_B, LOW);
    delay(100);
    y[0] = digitalRead(IN_PIN_Y);
    Serial.print("Test 1: A=0, B=0 => Q: ");
    Serial.print(y[0]);
    Serial.println();
    delay(500); 

     // A = 1, B = 0
    digitalWrite(OUT_PIN_A, HIGH);
    digitalWrite(OUT_PIN_B, LOW);
    delay(100);
    y[1] = digitalRead(IN_PIN_Y);
    Serial.print("Test 2: A=1, B=0 => Q: ");
    Serial.print(y[1]);
    Serial.println();
    delay(500); 

     // A = 0, B = 1
    digitalWrite(OUT_PIN_A, LOW);
    digitalWrite(OUT_PIN_B, HIGH);
    delay(100);
    y[2] = digitalRead(IN_PIN_Y);
    Serial.print("Test 3: A=0, B=1 => Q: ");
    Serial.print(y[2]);
    Serial.println();
    delay(500);  

     // A = 1, B = 1
    digitalWrite(OUT_PIN_A, HIGH);
    digitalWrite(OUT_PIN_B, HIGH);
    delay(100);
    y[3] = digitalRead(IN_PIN_Y);
    Serial.print("Test 4: A=1, B=1 => Q: ");
    Serial.print(y[3]);
    Serial.println();
    delay(500);  

    digitalWrite(OUT_PIN_A, LOW);
    digitalWrite(OUT_PIN_B, LOW);

    for(int n=0; n<6; n++)
    {
      count = 0;
      for(int m=0; m<4; m++)
      {
        if(y[m] == signale[n][m])
        {
          count++;
          if(count == 4)
          {
            index = n;
          }
        }
      }
    }
    Serial.print("Baustein: ");
    Serial.print(gatter[index]);
    Serial.println();
    Serial.print("***");
    Serial.println();
    delay(2000);
}
