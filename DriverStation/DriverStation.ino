void setup() {
  Serial.begin(57600);
}

int n = 0; 
void loop() {
    Serial.write(n);   // read it and send it out Serial1 (pins 0 & 1)
    n++;
    delay(500);
  
}
