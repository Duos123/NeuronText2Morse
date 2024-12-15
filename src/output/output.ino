const uint DOT_PIN = A7;
const uint DASH_PIN = A6;

const uint BASE_DELAY = 250;
const uint DOT_DELAY = BASE_DELAY;
const uint DASH_DELAY = BASE_DELAY * 3;
const uint CHAR_DELAY = DASH_DELAY;

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
  pinMode(DOT_PIN, INPUT);
  pinMode(DASH_PIN, INPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(DOT_PIN), setDot, RISING);
  attachInterrupt(digitalPinToInterrupt(DASH_PIN), setDash, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  if (text != "" && currentMillis - endMillis >= CHAR_DELAY * 2) {
    Serial.print("-> Decoded text: ");
    Serial.print(text);
    Serial.println();
    text = "";
  }

  if (morse != "" && currentMillis - charMillis >= CHAR_DELAY) {
    Serial.print("\tNo signals in ");
    Serial.print(CHAR_DELAY);
    Serial.println("ms");

    char c = getMorseChar(morse);
    if (c != '_') {
      Serial.print("\tDecoded character: ");
      Serial.println(c);
      text += c;
    } else {
      Serial.println("\tInvalid Morse sequence received.");
    }
    Serial.println();
    morse = "";
    endMillis = currentMillis;
  }

  if (currentMillis - baseMillis >= BASE_DELAY) {
    if (isDot) {
      dotSignals++;
      charMillis = currentMillis;
      endMillis = currentMillis;
    } else if (dotSignals > 0) {
      for (uint i = 0; i < dotSignals / 2; i++) {
        morse += '.';
      }

      Serial.print("Recieved ");
      Serial.print(dotSignals);
      Serial.println(" DOT signals.");

      Serial.print("\tCurrent sequence: ");
      Serial.println(morse);
      Serial.println();

      dotSignals = 0;
    }

    if (isDash) {
      dashSignals++;
      charMillis = currentMillis;
      endMillis = currentMillis;
    } else if (dashSignals > 0) {
      for (uint i = 0; i < dashSignals / 4; i++) {
        morse += '-';
      }

      Serial.print("Recieved ");
      Serial.print(dashSignals);
      Serial.println(" DASH signals.");

      Serial.print("\tCurrent sequence: ");
      Serial.println(morse);
      Serial.println();

      dashSignals = 0;
    }

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

  for (int i = 0; i < 27; i++) {
    if (morse == morseTable[i]) {
      return charTable[i];
    }
  }

  return '_';
}
