
#define U    1
#define UR   2
#define R    4
#define DR   8
#define D   16
#define DL  32
#define L   64
#define UL 128


const int PinRightPWM = 9;
const int PinLeftPWM = 10;
const int PinOn = 6;
const int PinLeftForward = 11;
const int PinLeftBackward = 12;
const int PinRightForward = 8;
const int PinRightBackward = 7;

int encoderR = 0;
int encoderL = 0;


int receivedByte = 0;
bool led_state = LOW;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

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

  analogWrite(PinRightPWM, 0);
  analogWrite(PinLeftPWM, 0);
  delay(5000);

  drive('F');

  delay(1000);
  brake();
  Serial.begin(9600);
  Serial1.begin(57600);
}

void loop() {
  while (Serial1.available()) {
    receivedByte = (int)Serial1.read();
    Serial.println(receivedByte);
    digitalWrite(LED_BUILTIN, led_state);
    led_state = !led_state;
  }

  switch (receivedByte) {
    // do stuff based on received byte
    case R:
      // Turn Clockwise
      // Right side: backwards
      // Left side: forward
      turn('R');
      break;
    case L:
      // Turn CCW
      // Left: backward
      // Right: Forward
      turn('L');

      break;
    case D:
      // Drive Backwards
      // Both sided backward
      drive('B');
      break;
    case U:
      // Drive Forward
      // Both sides Forward
      drive('F');

      break;
    case DR:
      // Turn R while driving backward
      // Both sides backwards
      // Right side half speed
      setDir(LOW, 'R');
      setDir(LOW, 'L');
      setSpd(4, 'L');
      setSpd(2, 'R');


      break;
    case DL:
      // Turn L while driving backwards
      // Both sides backwards
      // Left side half speed
      setDir(LOW, 'R');
      setDir(LOW, 'L');
      setSpd(2, 'L');
      setSpd(4, 'R');

      break;
    case UR:
      // Turn R while driving forward
      // Both sides forward
      // Right side half speed
      setDir(HIGH, 'R');
      setDir(HIGH, 'L');
      setSpd(4, 'L');
      setSpd(2, 'R');
      break;
    case UL:
      // Turn L while driving forward
      // Both sides forward
      // Left side half speed
      setDir(HIGH, 'R');
      setDir(HIGH, 'L');
      setSpd(2, 'L');
      setSpd(4, 'R');

      break;
                                            
    default:
      // Brake
      brake();
      break;
  }
  delay(250);


}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
  // see https://www.arduino.cc/reference/en/language/functions/communication/serial/serialevent/
*/

//void serialEvent1() {
//  while (Serial1.available()) {
//    receivedByte = (int)Serial1.read();
//    digitalWrite(LED_BUILTIN, led_state);
//    led_state = !led_state;
//  }
//}



void turn(char dir) {
  if (dir = 'L') {
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
}

void drive(char dir) {
  if (dir = 'F') {
    // Forward
    setDir(HIGH, 'R');
    setDir(HIGH, 'L');
    setSpd(4, 'L');
    setSpd(4, 'R');


  } else {
    // Backward
    setDir(LOW, 'R');
    setDir(LOW, 'L');
    setSpd(4, 'L');
    setSpd(4, 'R');

  }
}



void setDir( int fwd, char side) {
  if (side == 'L') {
    digitalWrite(PinLeftForward, fwd);
    digitalWrite(PinLeftBackward, !fwd);

  }
  else {
    digitalWrite(PinRightForward, fwd);
    digitalWrite(PinRightBackward, !fwd);
  }
}

void brake() {
  digitalWrite(PinLeftForward, LOW);
  digitalWrite(PinLeftBackward, LOW);
  digitalWrite(PinRightForward, LOW);
  digitalWrite(PinRightBackward, LOW);


}

void setSpd(int v, char side) {
  if (side == 'L') {
    analogWrite(PinLeftPWM, v * 51);
  } else {
    analogWrite(PinRightPWM, v * 51);
  }
}



void service2() {
  encoderR++;
}

void service4() {
  encoderL++;
}
