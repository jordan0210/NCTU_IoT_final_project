#define btnVoltageThreshold 0.01

int keybroadBtn[16] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};

int btnCount = 0;

void setBtnValue(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue==0)
      break;
    else if(btnValue<=keybroadBtn[i]*(1+btnVoltageThreshold)) && btnValue>=keybroadBtn[i]*(1-btnVoltageThreshold)){
      Serial.println("You Push Same Button Again !!");
      break;
    } else if (keybroadBtn[i]==0){
      keybroadBtn[i] = btnValue;
      btnCount++;
      Serial.println("Insert New Button Value into keybroadBtn Array !!");
      break;
    }
  }
}

void KeyboardCalibrator(int pin){

  while(1)
  {
    if(btnCount == 16) return;
    int btnValue = analogRead(pin);
    setBtnValue(btnValue);
    delay(500);
  }
}
