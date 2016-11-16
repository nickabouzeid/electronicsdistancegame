// Written by : Mohannad Rawashdeh
// this code foe EZ0 Max sonar , analog interface
// http://www.instructables.com/member/Mohannad+Rawashdeh/
//.................................................
int SonarPin=A0;
int  sensorValue;
void setup(){
pinMode(SonarPin,INPUT);
Serial.begin(9600);
}
void loop(){
sensorValue=analogRead(SonarPin);
Serial.println(sensorValue);
delay(500);
}

