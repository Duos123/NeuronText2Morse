import serial
import time

# Arduino Port (überprüfe den Port auf deinem System, der hier /dev/cu.usbmodem1101 ist)
arduino_port = '/dev/cu.usbmodem2101'
baud_rate = 9600  # Die Baudrate, die im Arduino Code verwendet wird
output_file = "output.txt"  # Datei, in der der Output gespeichert wird

# Seriellen Port öffnen
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

# Warte darauf, dass der Arduino bereit ist
time.sleep(2)

# Startnachricht empfangen
header = ser.readline().decode('utf-8').strip()

# Header in die Datei schreiben
with open(output_file, "w") as file:
    file.write(f"Header: {header}\n")

print(f"Header: {header}")

# Daten einlesen und in die Datei sowie ins Terminal schreiben
try:
    with open(output_file, "a") as file:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                print(line)
                file.write(f"{line}\n")

except KeyboardInterrupt:
    print("\nProgramm beendet.")
finally:
    ser.close()
