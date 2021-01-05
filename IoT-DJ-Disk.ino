#include "define.h"
#include "keyBroad.h"

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial softwareSerial(10, 11);
DFRobotDFPlayerMini player;

int currentMusic = 0;
const int maxMusic = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Keybroad start.");
//  KeyboardCalibrator1(pin_keybroad1);
//  KeyboardCalibrator2(pin_keybroad2);

  for (int i = 0; i < 16; i++) {
    Serial.print(String(keybroadBtn1[i]) + ",");
  }
  Serial.println();

  for (int i = 0; i < 16; i++) {
    Serial.print(String(keybroadBtn2[i]) + ",");
  }
  Serial.println();

  softwareSerial.begin(9600);
  while (!player.begin(softwareSerial)) {
    Serial.println("Player connect fail.");
  }
  Serial.println("Player begin.");

  player.volume(readVolume());
  player.loop(currentMusic + 1);
  Serial.println("Current EQ: " + String(player.readEQ()));
}

void loop() {
  // put your main code here, to run repeatedly:

  int keybroadValue = readKeybroadBtn();
  if (keybroadValue != 0) {
    if (keybroadValue <= 16) { //keybroad1
      Serial.println("You push the button on keyboard-2 : (" + String((keybroadValue-1)/4+1) + ", " + String((keybroadValue-1)%4+1) + ")");
      if (keybroadValue >= 1 && keybroadValue <= maxMusic) {
        if (keybroadValue != currentMusic + 1) {
          player.loop(keybroadValue);
          currentMusic = keybroadValue - 1;
        }
      } else if (keybroadValue == 13) {
        player.previous();
        currentMusic = (currentMusic - 1) % maxMusic;
      } else if (keybroadValue == 16) {
        player.next();
        currentMusic = (currentMusic + 1) % maxMusic;
      }
    } else if (keybroadValue > 16) { // keybroad2
      keybroadValue -= 16;
      Serial.println("You push the button on keyboard-2 : (" + String((keybroadValue-1)/4+1) + ", " + String((keybroadValue-1)%4+1) + ")");
      if (keybroadValue == 1) {
        Serial.println("Try change EQ to " + String(DFPLAYER_EQ_BASS));
        player.EQ(DFPLAYER_EQ_BASS);
        Serial.println("Current EQ: " + String(player.readEQ()));
      } else if (keybroadValue == 2) {
        Serial.println("Try change EQ to " + String(DFPLAYER_EQ_ROCK));
        player.EQ(DFPLAYER_EQ_ROCK);
        Serial.println("Current EQ: " + String(player.readEQ()));
      }
    }
  }

  player.volume(readVolume());
}

int readVolume() {
  int value = map(analogRead(pin_slider1), 0, 1023, 0, 30);
  if (value < 0) {
    value = 0;
  } else if (value > 30) {
    value = 30;
  }

  return value;
}

int readKeybroadBtn() {
  int value = analogRead(pin_keybroad1);
  for (int i = 1; i <= 16; i++) {
    if (value <= keybroadBtn1[i - 1] * 1.01 && value >= keybroadBtn1[i - 1] * 0.99) {
      return i;
    }
  }

  value = analogRead(pin_keybroad2);
  for (int i = 1; i <= 16; i++) {
    if (value <= keybroadBtn2[i - 1] * 1.01 && value >= keybroadBtn2[i - 1] * 0.99) {
      return i + 16;
    }
  }
  return 0;
}

//void changeMusic() {
//  int selectedMusic = readkeybroadBtn(pin_keybroad1);
//  if (currentMusic != selectedMusic && selectedMusic != 0) {
//    player.play(selectedMusic);
//    currentMusic = selectedMusic;
//  }
//}
