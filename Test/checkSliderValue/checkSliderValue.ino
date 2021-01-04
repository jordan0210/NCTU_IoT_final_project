int minValue = 1000;
int maxValue = -1000;
int value;

void setup(){
  Serial.begin(9600);
  Serial.println("Start");
}

void loop(){
  value = analogRead(0);
  if (value < minValue){
    minValue = value;
    Serial.print(minValue);
    Serial.print(" : ");
    Serial.println(maxValue);
  }
  if (value > maxValue){
    maxValue = value;
    Serial.print(minValue);
    Serial.print(" : ");
    Serial.println(maxValue);
  }
}
