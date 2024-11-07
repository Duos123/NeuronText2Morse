int outputPin = 11;

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // Corrected LED_BULTIN to LED_BUILTIN
}

void send_1() { // Function to set pins to HIGH
  digitalWrite(outputPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void send_0() { // Function to set pins to LOW
  digitalWrite(outputPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // First blink
  send_1();
  delay(1000); // LED on for 100 ms
  send_0();
  delay(100); // LED off for 100 ms

  // Second blink
  send_1();
  delay(100); // LED on for 100 ms
  send_0();
  delay(100); // LED off for 100 ms

  // Wait 1 second before the next set of blinks
  delay(1000);
}


// TODO: Text to Morse: 
// Arduino Output: Eingabe über serial monitor (text) -> Uebersetzung in HIGH und LOW 
// => Weitergabe an 2 parallel geschaltete Neuronen (encoding das Signal, getrennt)
// => Ergebniss der beiden (getrennten) Neuronen wird zusammen dekodiert
// => Weitergabe des Ergebnisses der Dekodierung an den Arduino zurück  
// Arduino Input: 