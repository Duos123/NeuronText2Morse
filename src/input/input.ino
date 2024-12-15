const uint DOT_PIN = 11;
const uint DASH_PIN = 12;

const uint BASE_DELAY = 250;
const uint DOT_DELAY = BASE_DELAY;
const uint DASH_DELAY = BASE_DELAY * 3;
const uint CHAR_DELAY = DASH_DELAY;

void setup() {
  pinMode(DOT_PIN, OUTPUT);
  pinMode(DASH_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() == 0) return;

  String input = Serial.readStringUntil('\n');
  input.toUpperCase();
  Serial.println("Received input: " + input);

  for (uint i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    Serial.print("\n\tEncoding character: ");
    Serial.println(c);

    encode(c);
    delay(CHAR_DELAY);
  }
}

void encode(char c) {
  const char* code = getMorseCode(c);
  if (code == nullptr) {
    Serial.print("\tCharacter not supported: ");
    Serial.println(c);
    return;
  }

  Serial.print("\tMorse code for ");
  Serial.print(c);
  Serial.print(": ");
  Serial.println(code);

  for (uint i = 0; code[i] != '\0'; i++) {
    if (code[i] == '.') {
      Serial.println("\t\tSending DOT");
      sendDot();
    } else if (code[i] == '-') {
      Serial.println("\t\tSending DASH");
      sendDash();
    }
  }
}

const char* getMorseCode(char c) {
  switch (c) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case ' ': return ".......";
    default: return nullptr;
  }
}

void sendDot() {
  digitalWrite(DOT_PIN, HIGH);
  delay(DOT_DELAY);
  digitalWrite(DOT_PIN, LOW);
  delay(BASE_DELAY);
}

void sendDash() {
  digitalWrite(DASH_PIN, HIGH);
  delay(DASH_DELAY);
  digitalWrite(DASH_PIN, LOW);
  delay(BASE_DELAY);
}
