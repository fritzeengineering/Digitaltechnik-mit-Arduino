// Arduino simuliert NAND-Gliedc
const int IN_BTN_A = 2;
const int IN_BTN_B = 3;
const int OUT_PIN_Q = 5;

void setup()
{
    //Eingänge
    pinMode(IN_BTN_A, INPUT);
    pinMode(IN_BTN_B, INPUT);
    //Ausgang
    pinMode(OUT_PIN_Q, OUTPUT);
}

void loop()
{
    bool a, b, q;

    a = digitalRead(IN_BTN_A) == LOW; 	//Eingänge einlesen 
    b = digitalRead(IN_BTN_B) == LOW; 
    q = !(a && b);				              //Signale verknüpfen

    if(q)			//Ergebnis anzeigen
    {
      digitalWrite(OUT_PIN_Q, HIGH);	
    } 
    else
    {
      digitalWrite(OUT_PIN_Q, LOW);
    }  
}