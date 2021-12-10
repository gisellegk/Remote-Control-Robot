

#define U    1
#define UR   2
#define R    4
#define DR   8
#define D   16
#define DL  32
#define L   64
#define UL 128


int receivedByte = 0;
bool led_state = LOW;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Beginning test code");
  Serial1.begin(57600);
}

void loop() {
  while (Serial1.available()) {
    receivedByte = (int)Serial1.read();
    Serial.println(receivedByte);
    digitalWrite(LED_BUILTIN, led_state);
    led_state = !led_state;
  }
  
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
    case U:
      digitalWrite(6,HIGH);
      break;
    case UR:
      digitalWrite(7,HIGH);
      break;
    case R:
      digitalWrite(8,HIGH);
      break;
    case DR:
      digitalWrite(9,HIGH);
      break;
    case D:
      digitalWrite(10,HIGH);
      break;
    case DL:
      digitalWrite(11,HIGH);
      break;
    case L:
      digitalWrite(12,HIGH);
      break;
    case UL:
      digitalWrite(5,HIGH);
      break;
    default:
      break;
  }
  delay(100);


}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

//void serialEvent1() {
//  while (Serial1.available()) {
//    receivedByte = (int)Serial1.read();
//    Serial.println(receivedByte);
//    digitalWrite(LED_BUILTIN, led_state);
//    led_state = !led_state;
//  }
//}
