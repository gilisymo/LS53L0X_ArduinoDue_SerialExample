/*
  SerialEnableDisable_ls53l0x
  this example code shows the Enable Disable commands over UART for the LS53L0X.
  The Serial1 interface is connected to Serial0 interface this to permit to print
  the result to the serial monitor.
  The VL53L0X is connected to Serial1. Default baud rate is 115200.
  The sketch send "disable" command to the LS then wait 5 second, then send "enable" command and 
  again wait for 5 second.
  The visual effect is the serial monitor we have data for 5 seconds and nothing for next 5 seconds,
  then this repeat. 
  
  This example code is in the public domain.
 */


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  while (!Serial) ;
  Serial1.begin(115200);
  while (!Serial1) ;
}

byte rx_byte = 0;
unsigned long Timer;
int timerstate = 0;

// the loop routine runs over and over again forever:
void loop() {
  // check for data byte on USB serial port
  if (Serial.available()) {
    // get byte from USB serial port
    rx_byte = Serial.read();
    // send byte to serial port 1
    Serial1.write(rx_byte);
  }
  // check for data byte on serial port 1
  if (Serial1.available()) {
    // get a byte from serial port 1
    rx_byte = Serial1.read();
    // send the byte to the USB serial port
    Serial.write(rx_byte);
  }

  // the following code uses millis() instead od delay to avoid blocking code
  switch(timerstate) {
    case 0:
      Serial1.println("disable");
      Timer = millis();
      timerstate = 1;
    break;
    case 1: // Wait 5 seconds
      if ((millis() - Timer) > 5000) {
        timerstate = 2;
        Timer = millis();
      }
    break;
    case 2:
      Serial1.println("enable");
      Timer = millis();
      timerstate = 3;
    break;
    default: // Wait 5 seconds
      if ((millis() - Timer) > 5000) {
        timerstate = 0;
        Timer = millis();
      }
    break;
  }
}



