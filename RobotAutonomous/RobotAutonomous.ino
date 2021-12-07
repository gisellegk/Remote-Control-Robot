const int PinRightPWM = 9;
const int PinLeftPWM = 10;
const int PinOn = 6;
const int PinLeftForward = 11;
const int PinLeftBackward = 12;
const int PinRightForward = 8;
const int PinRightBackward = 7;

int encoderR = 0;
int encoderL = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), service2, RISING);
  attachInterrupt(digitalPinToInterrupt(4), service4, RISING);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(PinRightPWM, OUTPUT);
  pinMode(PinLeftPWM, OUTPUT);
  pinMode(PinOn, INPUT);
  pinMode(PinLeftForward, OUTPUT);
  pinMode(PinLeftBackward, OUTPUT);
  Serial.begin(9600);

  Serial.println("Stopping...");
  analogWrite(PinRightPWM, 0);
  analogWrite(PinLeftPWM, 0);
  delay(5000);

  //do {} while(digitalRead(PinOn) == HIGH); // wait for button to be pressed
  Serial.println("Starting loop");
}


void loop() {

  Serial.println("Start Test Sequence");

   Serial.println("Waiting still for 1 second");
  delay(1000); 
  
  Serial.println("Drive Forward");
  driveEncoder(695);
  brake();
  delay(1000);
  
  Serial.println("Turning...");
//  turnEncoder('R', 900);
  turn('R', .5);
  brake();
  delay(1000);
  
  Serial.println("Drive back");
  driveEncoder(695);
  brake();
  delay(1000);
  
  Serial.println("Turning...");
  turn('L', .5);
//  turnEncoder('L', 900);
  brake();
  
  delay(1000);
  Serial.print("Encoder Pulses 1: ");
  Serial.println(encoderR);
  Serial.print("Encoder Pulses 2: ");
  Serial.println(encoderL);
  
  while(true);

}

void service2() {
  encoderR++;
}

void service4() {
  encoderL++;
}


void driveEncoder(int pulses){
  encoderR = 0;
  encoderL = 0;
  setDir(HIGH, 'R');
  setDir(HIGH, 'L');
  
  while(encoderR < pulses) {
    setSpd(4*((encoderR/((float)pulses/2))%1), 'R');
    setSpd(4*((encoderR/((float)pulses/2))%1), 'L');
    Serial.print("Right side: ");
    Serial.print(encoderR);
    Serial.print(" Left Side: ");
    Serial.println(encoderL);
    if(encoderR >= pulses) {
      digitalWrite(PinRightForward, HIGH);
      digitalWrite(PinRightBackward, HIGH);
//    }
//    if(encoderL >= pulses) {
      digitalWrite(PinLeftForward, HIGH);
      digitalWrite(PinLeftBackward, HIGH);
    }
  }

}

void turnEncoder(char dir, float pulses){
  encoderR = 0;
  encoderL = 0;
  if(dir = 'L'){
    // CCW
    setDir(HIGH, 'R');
    setDir(LOW, 'L');
    setSpd(5, 'L');
    setSpd(5, 'R');
  } else {
    // CW
    setDir(HIGH, 'L');
    setDir(LOW, 'R');
    setSpd(5, 'L');
    setSpd(5, 'R');
    
  }
  
  while(encoderR < pulses) {
    Serial.print("Right side: ");
    Serial.print(encoderR);
    Serial.print(" Left Side: ");
    Serial.println(encoderL);
    if(encoderR >= pulses) {
      digitalWrite(PinRightForward, HIGH);
      digitalWrite(PinRightBackward, HIGH);
//    }
//    if(encoderL >= pulses) {
      digitalWrite(PinLeftForward, HIGH);
      digitalWrite(PinLeftBackward, HIGH);
    }
  }
}


void driveOneFoot(){
  setDir(HIGH, 'R');
  setDir(HIGH, 'L');
  setSpd(4, 'R');
  delay(10);
  setSpd(4, 'L');
  delay(1000);
}

void turn(char dir, float numRot){
  if(dir = 'L'){
    // CCW
    setDir(HIGH, 'R');
    setDir(LOW, 'L');
    setSpd(5, 'L');
    setSpd(5, 'R');
    delay((int)(3400 * numRot));
  } else {
    // CW
    setDir(HIGH, 'L');
    setDir(LOW, 'R');
    setSpd(5, 'L');
    setSpd(5, 'R');
    delay((int)(3400 * numRot));
    
  }
}

void drive(char dir, int len){
  if(dir = 'F') {
    // Forward
    setDir(HIGH, 'R');
    setDir(HIGH, 'L');
    setSpd(4, 'L');
    setSpd(4, 'R');
    delay(len);

  } else {
    // Backward
    setDir(LOW, 'R');
    setDir(LOW, 'L');
    setSpd(4, 'L');
    setSpd(4, 'R');
    delay(len);
  }
}

void setDir( int fwd, char side){
  if(side == 'L'){
    digitalWrite(PinLeftForward, fwd); 
    digitalWrite(PinLeftBackward, !fwd); 

  }
  else {
    digitalWrite(PinRightForward, fwd); 
    digitalWrite(PinRightBackward, !fwd); 
  }
}

void brake(){
  digitalWrite(PinLeftForward, HIGH);
  digitalWrite(PinLeftBackward, HIGH);
  digitalWrite(PinRightForward, HIGH);
  digitalWrite(PinRightBackward, HIGH);

  
}

void setSpd(int v, char side){
  if(side=='L') {
    analogWrite(PinLeftPWM, v*51);      
  }else {
    analogWrite(PinRightPWM, v*51);
  }
}

void waitForButton(){
  Serial.println("Waiting for start signal");
  do {} while(digitalRead(PinOn) == HIGH); // wait for button to be pressed
}
