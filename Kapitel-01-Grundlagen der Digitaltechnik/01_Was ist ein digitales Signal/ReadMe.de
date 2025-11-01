# Was ist ein digitales Signal?  
**Digitaltechnik mit Arduino – Grundlagen verstehen**

In diesem ersten Unterprojekt lernen wir den wichtigsten Baustein der gesamten Digitaltechnik kennen:  
das **digitale Signal**.

Wir untersuchen, wie ein Arduino digitale Zustände erzeugt, was High/Low bedeutet und führen ein klassisches Einstiegs-Experiment aus.

---

## 🎯 Lernziele
- Unterschied zwischen HIGH und LOW verstehen  
- Arduino-Pins als digitale Ausgänge nutzen  
- Takt und Periodendauer praktisch sehen  
- Erste LEDs mit dem Mikrocontroller steuern  

---

## 🔧 Hardware
- Arduino Uno oder Nano  
- 1 LED  
- 1 Widerstand (220–330 Ω)  
- Jumperkabel  
- Breadboard  

---

## 🧩 Schaltung
Der digitale Ausgang **Pin 8** steuert die LED über einen Vorwiderstand.
Schaltplan:  
`/docs/visuals/schaltplan-kap1.png`

---

## 💡 Codebeispiel: Digitales Blinken (1 Hz)
Datei: `code/blink.ino`

```cpp
void setup() {
  pinMode(8, OUTPUT);
}

void loop() {
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(8, LOW);
  delay(500);
}
