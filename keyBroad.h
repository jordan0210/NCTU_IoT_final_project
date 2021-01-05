int keybroadBtn1[16] = {
//    0,0,0,0,
//    0,0,0,0,
//    0,0,0,0,
//    0,0,0,0
    988,924,893,861,840,794,771,747,730,694,677,658,644,618,604,588
};

int keybroadBtn2[16] = {
//    0,0,0,0,
//    0,0,0,0,
//    0,0,0,0,
//    0,0,0,0
    965,925,898,858,828,798,779,750,726,702,687,666,647,629,616,599
};

float btnVoltageThreshold = 0.01;

int btnCount = 0;

void setBtnValue1(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue <= 10) break;
    else if(btnValue<=keybroadBtn1[i]*(1.0+btnVoltageThreshold) && btnValue>=keybroadBtn1[i]*(1.0-btnVoltageThreshold)){
      Serial.println("You Push Same Button " + String(i/4+1) + " : " + String(i%4+1) + " in keybroad1 Again !!");
      break;
    } else if (keybroadBtn1[i]==0){
      keybroadBtn1[i] = btnValue;
      btnCount++;
      Serial.println("Insert Button " + String(i/4+1) + " : " + String(i%4+1) + " in keybroad-1 into keybroadBtn Array !!");
      break;
    }
  }
}

void setBtnValue2(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue <= 10) break;
    else if(btnValue<=keybroadBtn2[i]*(1.0+btnVoltageThreshold) && btnValue>=keybroadBtn2[i]*(1.0-btnVoltageThreshold)){
      Serial.println("You Push Same Button " + String(i/4+1) + " : " + String(i%4+1) + " in keybroad2 Again !!");
      break;
    } else if (keybroadBtn2[i]==0){
      keybroadBtn2[i] = btnValue;
      btnCount++;
      Serial.println("Insert Button " + String(i/4+1) + " : " + String(i%4+1) + " in keybroad-2 into keybroadBtn Array !!");
      break;
    }
  }
}

void KeyboardCalibrator1(int pin){

  btnCount = 0;

  while(1)
  {
    if(btnCount == 16) return;
    int btnValue = analogRead(pin);
    setBtnValue1(btnValue);
    delay(500);
  }
}

void KeyboardCalibrator2(int pin){

  btnCount = 0;

  while(1)
  {
    if(btnCount == 16) return;
    int btnValue = analogRead(pin);
    setBtnValue2(btnValue);
    delay(500);
  }
}
