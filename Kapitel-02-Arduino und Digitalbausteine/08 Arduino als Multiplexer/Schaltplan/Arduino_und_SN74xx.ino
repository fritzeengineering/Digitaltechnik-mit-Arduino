// Arduino und Logikbaustein SN7408 (SN7400, SN7432)
const int OUT_PIN_A = 2;
const int OUT_PIN_B = 3;

void setup()
{
    //Ausgänge
    pinMode(OUT_PIN_A, OUTPUT);
    pinMode(OUT_PIN_B, OUTPUT);
}

void loop()
{
    digitalWrite(OUT_PIN_A, LOW);
    digitalWrite(OUT_PIN_B, LOW);
    delay(1000);
    digitalWrite(OUT_PIN_A, HIGH);
    digitalWrite(OUT_PIN_B, LOW);
    delay(1000);
    digitalWrite(OUT_PIN_A, LOW);
    digitalWrite(OUT_PIN_B, HIGH);
    delay(1000);
    digitalWrite(OUT_PIN_A, HIGH);
    digitalWrite(OUT_PIN_B, HIGH);
    delay(1000);
}
