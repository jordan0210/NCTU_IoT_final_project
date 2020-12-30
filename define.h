#define pin_keybroad1
#define pin_keybroad2
#define pin_slider1
#define pin_slider2
#define pin_potentiometer1
#define pin_potentiometer2
#define pin_speaker1
#define pin_speaker2
#define pin_mp3Speaker
#define pin_mp3_TX
#define pin_mp3_RX

const int keybroadBtn[16] = {
  , , , ,
  , , , ,
  , , , ,
  , , ,
};

int readKeybroadBtn(int pin);

void changeMusic();
