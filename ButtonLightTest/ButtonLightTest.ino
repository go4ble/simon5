/**
 * ButtonLightTest
 *
 * test button and light connectivity on simon5 setup
 *
 * Copyright 2013 Kyle Boone
 * Written for UW HCDE 231 technical instructions assignment
 */

int N_INOUT = 5;
int LED_OUT[] = {0, 1, 2, 3, 4};
int BUTTON_IN[] = {A0, A1, A2, A3, A4};
int SPEAKER = 6;
int TONES[] = {123, 147, 165, 175, 196};

void setup() {
  for (int i = 0; i < N_INOUT; i++) {
    pinMode(BUTTON_IN[i], INPUT_PULLUP);
    pinMode(LED_OUT[i], OUTPUT);
  }
}

void loop() {
  int playTone = -1;
  for (int i = 0; i < N_INOUT; i++) {
    digitalWrite(LED_OUT[i], !digitalRead(BUTTON_IN[i]));
    if (!digitalRead(BUTTON_IN[i])) {
      playTone = i;
    }
  }
  if (playTone != -1) {
    tone(SPEAKER, TONES[playTone], 100);
  }
}
