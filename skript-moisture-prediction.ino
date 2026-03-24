#include <f3uc47_inferencing.h>
#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"

#define SENSOR_PIN A6
#define READ_INTERVAL_MS 10000

float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

rgb_lcd lcd;

void setup() {
  lcd.begin(16, 2);
  
  lcd.print("SAMMEL MESSWERTE");

  Serial.begin(115200);
  delay(2000);

  Serial.println("Edge Impulse Test startet...");
  Serial.print("Frame size: ");
  Serial.println(EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);

  Serial.println("Sammle Messwerte...");

  for (size_t i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; i++) {
    features[i] = analogRead(SENSOR_PIN);
    delay(READ_INTERVAL_MS);
  }
}

void loop() {
  
  signal_t signal;
  int err = numpy::signal_from_buffer(features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0) {
    Serial.print("signal_from_buffer Fehler: ");
    Serial.println(err);
    delay(2000);
    return;
  }

  ei_impulse_result_t result = { 0 };
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

  if (res != EI_IMPULSE_OK) {
    Serial.print("run_classifier Fehler: ");
    Serial.println(res);
    delay(2000);
    return;
  }

  float value = result.classification[0].value;

  Serial.println("Ausgabe:");

  Serial.print(result.classification[0].label);
  Serial.print(": ");
  Serial.println(value, 0);

  lcd.clear();

if (value <= 500) {
    Serial.println("Bitte gieß mich!");
    lcd.setCursor(0, 1);
    lcd.print("Bitte giess mich");
  } else {
    Serial.println("Ich bin nicht durstig :)");
    lcd.setCursor(0, 1);
    lcd.print("Ich bin feucht");
  }

  Serial.println("---");

  Serial.println("Sammle neuen Messwert...");

  for (size_t i = 0; i < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 1; i++) {
    features[i] = features[i+1];
  }

  features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE-1] = analogRead(SENSOR_PIN);

  delay(READ_INTERVAL_MS);
}