int keybroadBtn[16] = {
    917,894,871,857,
    841,820,801,791,
    778,763,746,735,
    725,709,695,687
};

float btnVoltageThreshold = 0.01;

int btnCount = 0;

void setBtnValue(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue==0) break;
    else if(btnValue<=keybroadBtn[i]*(1.0+btnVoltageThreshold) && btnValue>=keybroadBtn[i]*(1.0-btnVoltageThreshold)){
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
