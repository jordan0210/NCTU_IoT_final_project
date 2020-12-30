#include "define.h"

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial softwareSerial(pin_mp3_RX, pin_mp3_TX);
DFRobotDFPlayerMini player;

int currentMusic = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  softwareSerial.begin(9600);
  while(!player.begin(softwareSerial)){}
  Serial.println("Player begin.");
  player.volume(30);
  player.play(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  changeMusic();
}

int readkeybroadBtn(int pin){
  int value = analogRead(pin);
  for (int i=0; i<16; i++){
    if (value < keybroadBtn[i]){
      return i;
    }
  }
  return 16;
}

void changeMusic(){
  int selectedMusic = readkeybroadBtn(pin_keybroad1);
  if (currentMusic != selectedMusic && selectedMusic != 0){
    player.play(selectedMusic);
    currentMusic = selectedMusic;
  }
}
