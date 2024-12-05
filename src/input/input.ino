const int d11 = 11;  // Pin connected to W1 on 'dot' board
const int d12 = 12;  // Pin connected to W1 on 'dash' board
const int baseDelay = 1000;
const int dashDelay = baseDelay * 3;
const int charDelay = baseDelay * 5;
const int wordDelay = baseDelay * 10;

void setup() {
  pinMode(d11, OUTPUT);
  pinMode(d12, OUTPUT);
  // Serial.begin(9600);
  // Serial.println("Input:");
}

void loop() {
  // if(Serial.available() == 0) return;

  // String input = Serial.readStringUntil('\n');
  // input.toUpperCase();
  String input = "DAS IST EIN INPUT TEXT";  //  "-.."

  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    //if (!isAlpha(c)) continue;
    Serial.println(c);

      encode(c);
      delay(charDelay);
    
  }

  // Serial.println("End!");
}

void encode(char c) {
  String code = getMorseCode(c);
  for (int i = 0; i < code.length(); i++) {
    if (code[i] == '.') {
      sendDot();
    } else if (code[i] == '-') {
      sendDash();
    }
  }
}

String getMorseCode(char c) {
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
    case ' ': return ".....";
    default: return "";
  }
}


void sendDot() {
  digitalWrite(d11, HIGH);
  delay(baseDelay);
  digitalWrite(d11, LOW);
  delay(baseDelay);
}

void sendDash() {
  digitalWrite(d12, HIGH);
  delay(dashDelay);
  digitalWrite(d12, LOW);
  delay(baseDelay);
}
