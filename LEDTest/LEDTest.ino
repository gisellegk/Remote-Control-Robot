
#define UL 128
#define UR  64
#define DL  32
#define DR  16
#define U    8
#define D    4
#define L    2
#define R    1


int receivedByte = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(57600);
}

void loop() {
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(5,LOW);
  switch(receivedByte){
    // do stuff based on received byte
    case R:
      digitalWrite(6,HIGH);
      break;
    case L:
      digitalWrite(7,HIGH);
      break;
    case D:
      digitalWrite(8,HIGH);
      break;
    case U:
      digitalWrite(9,HIGH);
      break;
    case DR:
      digitalWrite(10,HIGH);
      break;
    case DL:
      digitalWrite(11,HIGH);
      break;
    case UR:
      digitalWrite(12,HIGH);
      break;
    case UL:
      digitalWrite(5,HIGH);
      break;
    default:
      break;
  }
  delay(250);


}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
bool led_state = LOW;
void serialEvent() {
  while (Serial.available()) {
    receivedByte = (int)Serial.read();
    digitalWrite(LED_BUILTIN, led_state);
    led_state = !led_state;
  }
}
