
int keybroadBtn[16] = {
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,
  0, 0, 0, 0
};

int btnCount = 0;

void setup(){
  Serial.begin(9600);
}

void setBtnValue(int btnValue)
{
  for(int i=0; i<16; i++)
  {
    if(btnValue==0) break;
    else if(btnValue<=keybroadBtn[i]*1.01 && btnValue>=keybroadBtn[i]*0.99)
    {
      Serial.println("You Push Same Button Again !!");
      break;
    }
    else if (keybroadBtn[i]==0)
    {
      keybroadBtn[i] = btnValue;
      btnCount++;
      Serial.println("Insert New Button Value into keybroadBtn Array !!");
      break;
    }
  }
}

void loop(){

  if(btnCount == 16)
  {
    Serial.println("int keybroadBtn[16] = {");
    for(int i=0; i<16; i++)
    {
      Serial.print(String(keybroadBtn[i]));
      if((i+1)%4 == 0) Serial.println(",");
      else Serial.print(", ");
    }
    Serial.println("};");
    delay(10000);
    return;
  }
  int btnValue = analogRead(A0);
  
  Serial.println("BTN V: "+String(btnValue));
  setBtnValue(btnValue);
  delay(1000);
}
