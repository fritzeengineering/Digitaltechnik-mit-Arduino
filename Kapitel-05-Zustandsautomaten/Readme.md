Komplexere Systeme wie Ampeln, Aufzüge oder Alarmanlagen lassen sich mit Zustandsautomaten modellieren. 
Ich erkläre dir Schritt für Schritt, wie du mit dem Arduino solche Automaten programmierst, Zustände im Code abbildest und Übergänge definierst.

# Zustandsautomaten

Zustandsautomaten sind ein praxisnahes Thema, weil man damit über reine Logikgatter hinauskommt und Abläufe abbilden kann. Genau das unterscheidet auch Arduino-Programmierung von „statischen“ Logikbausteinen.
Ein Zustandsautomat (auch endlicher Automat oder Finite State Machine, FSM) ist ein mathematisches Modell, mit dem man Systeme beschreibt, die sich zu jedem Zeitpunkt in genau einem Zustand befinden und durch Ereignisse/Eingaben in andere Zustände übergehen können.
Bestandteile eines Zustandsautomaten sind:
1.	Menge von Zuständen – z. B. Start, Warten, Verarbeiten, Fertig.
2.	Startzustand – der Zustand, in dem das System zu Beginn ist.
3.	Eingaben (Symbole oder Ereignisse) – Signale, die einen Übergang auslösen.
4.	Übergangsfunktion – legt fest, in welchen Zustand der Automat bei einer bestimmten Eingabe wechselt.
5.	(Optional) Endzustände – Zustände, in denen der Automat „akzeptiert“ oder terminiert.
