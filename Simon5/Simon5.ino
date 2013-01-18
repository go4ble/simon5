/**
 * Simon5
 *
 * Simon game with five selections
 *
 * Copyright 2013 Kyle Boone
 * Written for UW HCDE 231 technical instructions assignment
 */

#define N_INOUT 5  // number of lights/buttons
#define GAME_LEN 15  // number successful selections to win

#define TIME_SHOW 500  // time to show light/buzzer
#define TIME_BETWEEN 200  // time between each buzz
#define TIME_LOSE 2500  // time to allow player

// pin assignment
int LED_OUT[] = {0, 1, 2, 3, 4};
int BUTTON_IN[] = {A0, A1, A2, A3, A4};
int SPEAKER = 6;

// tones paired with particular lights
int TONES[] = {165, 139, 220, 82, 117};

void setup() {
  for (int i = 0; i < N_INOUT; i++) {
    pinMode(BUTTON_IN[i], INPUT_PULLUP);
    pinMode(LED_OUT[i], OUTPUT);
  }
  randomSeed(analogRead(A5));  // prepare random generator
  
  gameBegin();
  
  int game[GAME_LEN];
  for (int pos = 0; pos < GAME_LEN; pos++) {
    // determine next light to show
    game[pos] = random(N_INOUT);
    
    // play current sequence
    for (int i = 0; i <= pos; i++) {
      digitalWrite(LED_OUT[game[i]], HIGH);
      tone(SPEAKER, TONES[game[i]], TIME_SHOW);
      delay(TIME_SHOW);
      digitalWrite(LED_OUT[game[i]], LOW);
      delay(TIME_BETWEEN);
    }
    
    // player input
    for (int i = 0; i <= pos; i++) {
      if (getButton() != game[i])
        gameLose();
      digitalWrite(LED_OUT[game[i]], HIGH);
      tone(SPEAKER, TONES[game[i]], TIME_SHOW);
      delay(TIME_SHOW);
      digitalWrite(LED_OUT[game[i]], LOW);
    }
    delay(500);
  }
  gameWin();
}

// get next button press from player
// player has TIME_LOSE to press button before game is ended
// if player presses more than one button, game is ended
int getButton() {
  int button = -1;
  unsigned long start = millis();
  while (millis() - start < TIME_LOSE) {
    for (int i = 0; i < N_INOUT; i++)
      if (!digitalRead(BUTTON_IN[i]))
        if (button == -1)
          button = i;
        else
          gameLose();
    if (button != -1)
      return button;
  }
  gameLose();
  return button;
}

// flash some lights
// play some music
void gameBegin() {
  tone(SPEAKER, 523, 250);
  digitalWrite(LED_OUT[2], HIGH);
  delay(250);
  tone(SPEAKER, 587, 250);
  digitalWrite(LED_OUT[1], HIGH);
  digitalWrite(LED_OUT[3], HIGH);
  delay(250);
  tone(SPEAKER, 784, 500);
  digitalWrite(LED_OUT[0], HIGH);
  digitalWrite(LED_OUT[4], HIGH);
  delay(500);
  for (int i = 0; i < N_INOUT; i++)
    digitalWrite(LED_OUT[i], LOW);
  delay(500);
}

// flash lots of lights
// use horrible sounds
// make player feel bad for losing
void gameLose() {
  tone(SPEAKER, 49, 250);
  for (int i = 0; i < N_INOUT; i++)
    digitalWrite(LED_OUT[i], HIGH);
  delay(300);
  tone(SPEAKER, 44, 250);
  digitalWrite(LED_OUT[0], LOW);
  digitalWrite(LED_OUT[4], LOW);
  delay(300);
  tone(SPEAKER, 33, 500);
  digitalWrite(LED_OUT[1], LOW);
  digitalWrite(LED_OUT[3], LOW);
  delay(250);
  digitalWrite(LED_OUT[2], LOW);
  while (true) {}
}

// indicate to player that they have won
void gameWin() {
  for (int k = 1; k <= 5; k++) {
    tone(SPEAKER, 500, 250);
    for (int i = 0; i < N_INOUT; i++)
      digitalWrite(LED_OUT[i], HIGH);
    delay(250);
    for (int i = 0; i < N_INOUT; i++)
      digitalWrite(LED_OUT[i], LOW);
    delay(50);
  }
  
  while (true) {}
}

// loop isn't used
void loop() {
  //
}

