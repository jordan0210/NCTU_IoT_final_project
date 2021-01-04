int keybroadBtn1[16] = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};

int keybroadBtn2[16] = {
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0
};

float btnVoltageThreshold = 0.01;

int btnCount = 0;

void setBtnValue1(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue==0) break;
    else if(btnValue<=keybroadBtn1[i]*(1.0+btnVoltageThreshold) && btnValue>=keybroadBtn1[i]*(1.0-btnVoltageThreshold)){
      Serial.println("You Push Same Button Again !!");
      break;
    } else if (keybroadBtn1[i]==0){
      keybroadBtn1[i] = btnValue;
      btnCount++;
      Serial.println("Insert New Button Value into keybroadBtn Array !!");
      break;
    }
  }
}

void setBtnValue2(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue==0) break;
    else if(btnValue<=keybroadBtn2[i]*(1.0+btnVoltageThreshold) && btnValue>=keybroadBtn2[i]*(1.0-btnVoltageThreshold)){
      Serial.println("You Push Same Button Again !!");
      break;
    } else if (keybroadBtn2[i]==0){
      keybroadBtn2[i] = btnValue;
      btnCount++;
      Serial.println("Insert New Button Value into keybroadBtn Array !!");
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
