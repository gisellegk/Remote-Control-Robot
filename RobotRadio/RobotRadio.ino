int receivedByte = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(57600);
}

void loop() {
  switch(receivedByte){
    // do stuff based on received byte
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
