# Projekt: Feuchtigkeitsmessung für proaktives Wässern

## Ziel
Ziel des Projekts ist es, den Feuchtigkeitsverlauf der Erde zu analysieren und mithilfe von TinyML vorherzusagen, wann gegossen werden muss, bevor ein kritischer Zustand erreicht wird.

---

## Vorgehen

Zur Datenerhebung wurden in regelmäßigen Abständen Feuchtigkeitswerte mit einem Bodensensor gemessen.

Für das Training des Modells wurde aus den Messdaten eine Zeitreihe aufgebaut. Dabei enthält jeder Datensatz:

- den aktuellen Feuchtewert  
- den Wert von vor 1 Stunde  
- den Wert von vor 2 Stunden  
- den Wert von vor 3 Stunden  
- den Zielwert (Target), also den Feuchtewert eine Stunde nach dem aktuellen Zeitpunkt

Damit ergibt sich eine Struktur, die den zeitlichen Verlauf der Feuchtigkeit abbildet.

Auf Basis dieser Daten wurde ein Regressionsmodell trainiert.  
Dieses Modell ist in der Lage, aus den vergangenen Messwerten den zukünftigen Feuchtewert vorherzusagen.

Anschließend wurde ein Grenzwert definiert, ab dem ein Gießen erforderlich ist.

Im Betrieb funktioniert das System wie folgt:

1. Es werden kontinuierlich aktuelle Messwerte erfasst  
2. Das Modell sagt den Feuchtewert in der Zukunft voraus  
3. Wird der vorhergesagte Wert unter den Grenzwert fallen,  
   → wird auf dem Display eine Gießempfehlung ausgegeben

---

## Requirements

### Hardware
- Arduino Nano 33 BLE Sense Lite  
- Tiny Machine Learning Shield  
- Seeed Studio Moisture Sensor  
- Seeed Studio Grove 16x2 LCD  
- Verbindungskabel (Grove / Dupont)  
- Stromquelle (USB oder Batterie)  

---

### Software
- Arduino IDE  
- Edge Impulse (für Training und Deployment des Modells)  

---

## Anleitung

### Aufbau
1. Moisture Sensor auf Port A6 und LCD auf einem der drei SDA/SCL-Ports am Machine Learning Shield anschließen
2. Arduino auf das Shield stecken  
3. Arduino per USB mit dem Computer verbinden  

---

### Software-Setup
4. Code in die Arduino IDE kopieren  
5. Sicherstellen, dass die Edge-Impulse-Library eingebunden ist  
6. Code ggf. anpassen (siehe unten)  

---

### Messintervall anpassen

Standardmäßig misst der Code in kurzen Intervallen (z. B. alle paar Sekunden).

Für realistische Messungen sollte das Intervall angepasst werden:

```cpp
#define READ_INTERVAL_MS 3600000
```
### Deployment
7. Code auf den Arduino hochladen
8. Seriellen Monitor optional zur Kontrolle öffnen

### Nutzung
9. Sensor in die Erde stecken
10. System starten
11. Das Display zeigt dann eine Handlungsempfehlung
