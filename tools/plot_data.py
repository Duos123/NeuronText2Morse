import pandas as pd
import matplotlib.pyplot as plt

# Pfad zur CSV-Datei
csv_file = "output2.csv"

# CSV-Datei einlesen
data = pd.read_csv(csv_file)

# Überprüfen, ob die Daten korrekt geladen wurden
print(data.head())

# Plot erstellen
plt.figure(figsize=(10, 6))
plt.plot(data["Time(ms)"], data["Voltage1(V)"], label="Voltage1 (V)", color="blue", linewidth=1.5)
plt.plot(data["Time(ms)"], data["Voltage2(V)"], label="Voltage2 (V)", color="red", linewidth=1.5)

# Achsenbeschriftungen und Titel
plt.xlabel("Time (ms)")
plt.ylabel("Voltage (V)")
plt.title("Voltage over Time")
plt.legend()

# Gitter hinzufügen
plt.grid(True, linestyle="--", alpha=0.7)

# Plot anzeigen
plt.tight_layout()
plt.show()
