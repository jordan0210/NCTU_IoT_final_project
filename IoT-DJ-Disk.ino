#include "define.h"
#include "keyBroad.h"

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//SoftwareSerial softwareSerial(pin_mp3_RX, pin_mp3_TX);
//DFRobotDFPlayerMini player;

int currentMusic = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Keybroad start.");
  KeyboardCalibrator1(pin_keybroad1);
  KeyboardCalibrator2(pin_keybroad2);

  for (int i = 0; i < 16; i++)
  {
    Serial.print(String(keybroadBtn1[i]) + ",");
  }

  for (int i = 0; i < 16; i++)
  {
    Serial.print(String(keybroadBtn2[i]) + ",");
  }

  //  softwareSerial.begin(9600);
  //  while(!player.begin(softwareSerial)){}
  Serial.println("Player begin.");

  //  player.volume(readVolume());
  //  player.loop(currentMusic);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("slider 1:   " + String(analogRead(pin_slider1)));
  Serial.println("slider 2:   " + String(analogRead(pin_slider2)));
  Serial.println("keybroad 1: " + String(analogRead(pin_keybroad1)));
  Serial.println("keybroad 2: " + String(analogRead(pin_keybroad2)));

  delay(1000);
  //  readkeybroadBtn(pin_keybroad1);
  //
  //  changeMusic();
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

int readkeybroadBtn(int pin) {
  int value = analogRead(pin);
  for (int i = 1; i <= 16; i++) {
    if (value <= keybroadBtn1[i] * 1.01 && value >= keybroadBtn1[i] * 0.99) {
      return i;
    }
  }
  return 0;
}

void changeMusic() {
  int selectedMusic = readkeybroadBtn(pin_keybroad1);
  if (currentMusic != selectedMusic && selectedMusic != 0) {
//    player.play(selectedMusic);
    currentMusic = selectedMusic;
  }
}
