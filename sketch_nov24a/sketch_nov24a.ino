// Globale Variablen und Konstanten
const int sensorPin = A7;         // Zweiter Lichtsensor an Pin A7
const float thresholdVoltage = 0.8; // Schwellenwert der Spannung
const int smoothingFactor = 10;   // Anzahl der Werte für den gleitenden Durchschnitt
const unsigned long dotTime = 1000;   // Dauer für einen Punkt
const unsigned long dashTime = 3000;  // Dauer für einen Bindestrich
const unsigned long charTime = 5000;  // Timeout für ein Zeichen
const unsigned long wordTime = 25000; // Timeout für ein Wort

int sensorValue = 0;              // Variable für den gelesenen Wert des Sensors
float smoothedValue = 0;          // Geglätteter Wert des Sensors
String letter = "";               // Zwischenspeicher für Morsezeichen
unsigned long startTime = 0;      // Startzeit für die Spannungsmessung
bool isMeasuring = false;         // Status für aktive Messung

void setup() {
  Serial.begin(9600);             // Seriellen Monitor starten
  pinMode(sensorPin, INPUT);      // Sensor-Pin als Eingang definieren
}

void loop() {
  // Sensorwert lesen und Spannung berechnen
  sensorValue = analogRead(sensorPin);
  smoothedValue = (smoothedValue * (smoothingFactor - 1) + sensorValue) / smoothingFactor;
  float voltage = smoothedValue * (5.0 / 1023.0); // Spannung berechnen

  // Überprüfung auf Wort-Timeout
  if (millis() - startTime >= wordTime) {
    Serial.print("Wort abgeschlossen: ");
    Serial.println(letter);      // Wort ausgeben
    letter = "";                 // Zwischenspeicher zurücksetzen
    startTime = millis();        // Startzeit zurücksetzen
    return;
  }

  // Überprüfung auf Zeichen-Timeout
  if (millis() - startTime >= charTime && !isMeasuring) {
    char morseChar = getMorseChar(letter);
    Serial.print("Morsezeichen: ");
    Serial.println(morseChar);  // Zeichen ausgeben
    letter = "";                // Zwischenspeicher zurücksetzen
    startTime = millis();       // Startzeit zurücksetzen
    return;
  }

  // Spannung über Schwellenwert prüfen
  if (voltage > thresholdVoltage) {
    if (!isMeasuring) {
      startTime = millis();      // Startzeit speichern
      isMeasuring = true;        // Messung aktiv setzen
    }

    // Überprüfung auf zweite Spitze
    unsigned long duration = millis() - startTime;
    bool hasPeak = false;
    unsigned long checkStartTime = millis();

    while (millis() - checkStartTime < 1200) { // 1 Sekunde + 200ms Puffer
      float currentVoltage = analogRead(sensorPin) * (5.0 / 1023.0);
      if (currentVoltage > thresholdVoltage) {
        hasPeak = true; // Zweite Spitze erkannt
        break;
      }
    }

    // Punkt oder Bindestrich abhängig von der Dauer
    if (hasPeak) {
      Serial.print("Punkt erkannt: ");
      letter += ".";             // Punkt hinzufügen
    } else {
      Serial.print("Dash erkannt: ");
      letter += "-";
      delay(1800);             // Bindestrich hinzufügen
    }

    isMeasuring = false;         // Messung abschließen
    startTime = millis();        // Startzeit aktualisieren
  }
}


// Funktion zur Dekodierung von Morsezeichen
char getMorseChar(String morse) {
  if (morse == ".-") return 'A';
  if (morse == "-...") return 'B';
  if (morse == "-.-.") return 'C';
  if (morse == "-..") return 'D';
  if (morse == ".") return 'E';
  if (morse == "..-.") return 'F';
  if (morse == "--.") return 'G';
  if (morse == "....") return 'H';
  if (morse == "..") return 'I';
  if (morse == ".---") return 'J';
  if (morse == "-.-") return 'K';
  if (morse == ".-..") return 'L';
  if (morse == "--") return 'M';
  if (morse == "-.") return 'N';
  if (morse == "---") return 'O';
  if (morse == ".--.") return 'P';
  if (morse == "--.-") return 'Q';
  if (morse == ".-.") return 'R';
  if (morse == "...") return 'S';
  if (morse == "-") return 'T';
  if (morse == "..-") return 'U';
  if (morse == "...-") return 'V';
  if (morse == ".--") return 'W';
  if (morse == "-..-") return 'X';
  if (morse == "-.--") return 'Y';
  if (morse == "--..") return 'Z';
  return '\0'; // Rückgabe eines Nullzeichens, falls kein passendes Morsezeichen gefunden wurde
}





// Ich sollte den Zeitpunkt, des ersten spikes kurzeitig speichern => Dann überprüfen, ob 
