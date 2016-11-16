// Original Written by : Mohannad Rawashdeh - modified by Nicholas & Vibhor
// this code for EZ0 Max sonar, analog interface
// http://www.instructables.com/member/Mohannad+Rawashdeh/
//.................................................

//lab 1
// first thing: removed all reference to cm from code (variables & functions), useless to us in our game & added foot
// second thing: coded in LEDs using code from light sensor lab, tested to make sure they're working
// added testDistance() function to test the distance after a random distance between 1 & 20 feet is generated using random(1, 20)
// built an if, if, else statement to decide which LED to turn on based on whether the subject is too close, too far, or in the range of the sensor
// added a score counter, in case we end up wanting it
// added print statements to tell player their desired distance & when they get to that distance
// next: perform an experiment to figure out ideal adjuster value (currently .497), data in Excel!

// lab 2 bugs/solns
// bug: distances not reporting correctly. solved with Excel sheet
// bug: game is too easily winnable given imprecise distance measurements (that vary wildly & quickly, "winning" the game when you actually didn't win)
//    solved: added delay inside winning if statement that waits 3 seconds, then checks again & only finishes round if sensorValue stays in range for 3 seconds
// bug: green LED not turning on
//    solved: it was actually turning on, just not bright enough. Switched to a 100 ohm resistor
// bug: green LED, once switched, didn't turn on at all
//    solved: resistor was placed into breadboard incorrectly (into slot 10 instead of slot 9)

//variables for sensor
int SonarPin=A0;
float adjuster=0.6058;

//variables for LED
const int LEDfurther = 13; //red LED indicates move further
const int LEDcloser = 12; //blue LED indicates move closer
const int LEDgood = 10; //green LED indicates good!

//variables for game
int score = 0;
int counter = 0;

void setup(){
pinMode(SonarPin,INPUT);
pinMode(LEDfurther, OUTPUT);
pinMode(LEDcloser, OUTPUT);
pinMode(LEDgood, OUTPUT);
Serial.begin(9600);
}

void loop(){
counter = 0;
int distance = random(1, 10);
Serial.println("The distance you want is:");
Serial.println(distance);   // prints distance required so the user can try to get to that required distance
counter =0;                 // begins counter for this specific "round" of the game for one distance
while (counter<1000){
    testDistance(counter, distance, score);
  }
}

void testDistance(int counter1, int distance, int score1){
  restart:
  counter = counter1+1;
  float currentInch=0.00;
  float currentFoot=0.00;
  int  sensorValue;
  sensorValue=analogRead(SonarPin);
  currentInch= (sensorValue*adjuster);
  currentFoot= currentInch/12;
  //Serial.println(currentFoot);
  if(abs(distance-currentFoot)<=1 || abs(currentFoot-distance)<=1){ 
    //this is when distance & currentFoot are within 1 feet of each other, aka good! they did it!
    digitalWrite(LEDfurther, LOW);
    digitalWrite(LEDcloser, LOW);
    digitalWrite(LEDgood, HIGH);
    delay(3000);
    if(abs(distance-currentFoot)<=1 || abs(currentFoot-distance)<=1){ 
      counter = 1000; //exits the while loop by setting counter = 1000, which finishes the while loop in the main loop() function
      score = score1+1;
      Serial.println("Congrats! You did it! Your current score is: ");
      Serial.println(score);
      delay(3000); //delays for 3 seconds while the green LEDgood is on, indicating a successful score
      return;
    }
  }  
  if(distance-currentFoot>1){ 
    //this is true when distance (eg. 10ft) is much bigger than currentFoot (eg. 2ft), so they need to go FURTHER
    digitalWrite(LEDfurther, HIGH);
    digitalWrite(LEDcloser, LOW);
    digitalWrite(LEDgood,LOW);
  }
  if(currentFoot-distance>1){ 
    //this is true when distance (eg. 2ft) is much smaller than currentFoot (eg. 10ft), so they need to go CLOSER
    digitalWrite(LEDfurther, LOW);
    digitalWrite(LEDcloser, HIGH);
    digitalWrite(LEDgood,LOW);
  }
  goto restart;
}
