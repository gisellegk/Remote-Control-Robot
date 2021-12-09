const int pinU = 8; // up
const int pinR = 9; // right
const int pinD = 10; // down
const int pinL = 11; // left

  //  UL  UR  DL  DR  U  D  L  R
  // 128  64  32  16  8  4  2  1

#define UL 128
#define UR  64
#define DL  32
#define DR  16
#define U    8
#define D    4
#define L    2
#define R    1


void setup() {
  pinMode(pinU, INPUT_PULLUP);
  pinMode(pinR, INPUT_PULLUP);
  pinMode(pinD, INPUT_PULLUP);
  pinMode(pinL, INPUT_PULLUP);
  
  Serial.begin(57600);
}

//int n = 0;
uint8_t up = 0;
uint8_t down = 0;
uint8_t left = 0;
uint8_t right = 0;
uint8_t message = 0;

void loop() {
  // Read pins
  up = !digitalRead(pinU);
  down = !digitalRead(pinD);
  left = !digitalRead(pinL);
  right = !digitalRead(pinR);
  // Construct message

  
  if(up + down + left + right > 1) {
    // combination
    if (up) {
      if(left) message = UL;
      else if (right) message = UR;
    } else if (down) {
      if(left) message = DL;
      else if (right) message = DR;
    }
  } else {
    // single direction or stopped
    message = (up << 3 | down << 2 | left << 1 | right);
  }
//  Serial.print("UP: ");
//  Serial.print(up);
//  Serial.print(" DOWN: ");
//  Serial.print(down);
//  Serial.print(" LEFT: ");
//  Serial.print(left);
//  Serial.print(" RIGHT: ");
//  Serial.println(right);
//  Serial.println(message);
  Serial.write(message);
  delay(100);
  
}
