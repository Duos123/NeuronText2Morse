# Text2Morse

Implement Text-to-Morse and Morse-to-Text conversion using two Arduino Nano BLE 33 boards and two Lu.i boards.

https://github.com/user-attachments/assets/ed819064-9fd6-46a6-b6ce-5030dc234cb1

### Welcome

This repository showcases an **educational project** designed to transform text into Morse code and back into text. It demonstrates the integration of two LU.I devices and two Arduino boards to process and communicate information interactively.

#### Project Overview:
- The first Arduino receives a string of text as input. Each character is encoded into Morse code as dots and dashes, with specific delays for each. These signals are sent to the LU.I boards.
- The LU.I boards receive the signal, fire upon activation, and pass the output to the second Arduino board.
- The output Arduino board decodes the received frequencies back into dots and dashes, which are then converted back into the original text.

This project highlights how low-cost, accessible tools like LU.I and Arduino can be used to explore signal processing and coding principles.

---

### Prerequisites  

To run this project, you will need:  
- Arduino IDE  
- 2 LU.I boards  
- 2 Arduino boards  

### Gettin Started

### Note

There is a [demo](https://chubetho.github.io/Text2MorseWeb/) for this project when there is no Arduino Nano or Lu.i board.
