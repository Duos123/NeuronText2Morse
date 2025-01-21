const uint DOT_PIN = A7;   // Analog pin 7
const uint DASH_PIN = A6;  // Analog pin 6

const unsigned long BASE_DELAY = 300;  // 300ms
const unsigned long DOT_DELAY = BASE_DELAY;
const unsigned long DASH_DELAY = BASE_DELAY * 3;
const unsigned long CHAR_DELAY = DASH_DELAY;

const bool DEBUG = true;  // Verbose mode

volatile bool isDot = false;
volatile bool isDash = false;

uint dotSignals = 0;
uint dashSignals = 0;

unsigned long baseMillis = 0;
unsigned long charMillis = 0;
unsigned long endMillis = 0;

String morse = "";
String text = "";

void setDot() {
  isDot = true;
}

void setDash() {
  isDash = true;
}

void setup() {
  pinMode(DOT_PIN, INPUT_PULLUP);   // Set DOT_PIN as an input
  pinMode(DASH_PIN, INPUT_PULLUP);  // Set DASH_PIN as an input
  Serial.begin(9600);               // Initializes serial communication.

  /*
  * Attach interrupts to DOT_PIN and DASH_PIN.
  * When a rising signal is detected, the corresponding function is executed.
  */
  attachInterrupt(digitalPinToInterrupt(DOT_PIN), setDot, RISING);
  attachInterrupt(digitalPinToInterrupt(DASH_PIN), setDash, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  /*
   * If no signals are received for CHAR_DELAY * 2, consider it the end of the text.
   */
  if (text != "" && currentMillis - endMillis >= CHAR_DELAY * 2) {
    if (DEBUG) {
      Serial.print("-> Decoded text: ");
      Serial.print(text);
      Serial.println();
    }
    text = "";
  }

  /*
   * If no signals are received for CHAR_DELAY, consider it the end of a character.
   */
  if (morse != "" && currentMillis - charMillis >= CHAR_DELAY) {
    if (DEBUG) {
      Serial.print("\tNo signals in ");
      Serial.print(CHAR_DELAY);
      Serial.println("ms");
    }

    char c = getMorseChar(morse);
    if (c != '_') {
      if (DEBUG) {
        Serial.print("\tDecoded character: ");
        Serial.println(c);
      } else {
        Serial.print(c);
      }
      text += c;
    } else {
      if (DEBUG) {
        Serial.println("\tInvalid Morse sequence received.");
      } else {
        Serial.print(c);
      }
    }
    if (DEBUG) {
      Serial.println();
    }
    morse = "";
    endMillis = currentMillis;
  }

  /*
   * Check for new signals every BASE_DELAY interval.
   */
  if (currentMillis - baseMillis >= BASE_DELAY) {
    if (isDot) {
      dotSignals++;
      charMillis = currentMillis;
      endMillis = currentMillis;
    } else if (dotSignals > 0) {
      // Convert collected dot signals into Morse code dots.
      for (uint i = 0; i < dotSignals / 2; i++) {
        morse += '.';
      }

      if (DEBUG) {
        Serial.print("Recieved ");
        Serial.print(dotSignals);
        Serial.println(" DOT signals.");

        Serial.print("\tCurrent sequence: ");
        Serial.println(morse);
        Serial.println();
      }

      dotSignals = 0;
    }

    if (isDash) {
      dashSignals++;
      charMillis = currentMillis;
      endMillis = currentMillis;
    } else if (dashSignals > 0) {
      // Convert collected dash signals into Morse code dashes.
      for (uint i = 0; i < dashSignals / 4; i++) {
        morse += '-';
      }

      if (DEBUG) {
        Serial.print("Recieved ");
        Serial.print(dashSignals);
        Serial.println(" DASH signals.");

        Serial.print("\tCurrent sequence: ");
        Serial.println(morse);
        Serial.println();
      }

      dashSignals = 0;
    }

    // Reset
    isDot = false;
    isDash = false;
    baseMillis = currentMillis;
  }
}

char getMorseChar(const String &morse) {
  static const char *morseTable[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--..", "......."
  };

  static const char charTable[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', ' '
  };

  for (uint i = 0; i < 27; i++) {
    if (morse == morseTable[i]) {
      return charTable[i];
    }
  }

  return '_';
}
