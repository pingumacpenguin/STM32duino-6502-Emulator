#define BLINK_PIN PB0
uint8_t curkey = 0;

// Create USB serial_debug port
USBSerial serial_debug;


extern "C" {

  uint16_t getpc();
  uint8_t getop();
  void exec6502(int32_t tickcount);
  void reset6502();
  void serout(uint8_t val) {
    serial_debug.write(val);
  }
  uint8_t getkey() {
    //DEBUG
    // serial_debug.print(curkey);
    return(curkey);
  }
  void clearkey() {
    curkey = 0;
  }
  void printhex(uint16_t val) {
    serial_debug.print(val, HEX);
    serial_debug.println();
  }
}

void setup () {
  /*
  // Flash the LED 3 times to prove we rebooted.
  pinMode(BLINK_PIN, OUTPUT);
  for ( int i = 0; i = 2 ; i++)
  {
    digitalWrite(BLINK_PIN, LOW);
    delay(1000);
    digitalWrite(BLINK_PIN, HIGH);
    delay(1000);
  }
  digitalWrite(BLINK_PIN, LOW);
  */
  serial_debug.begin (9600);
  serial_debug.println ();

  reset6502();
}

void loop () {



  exec6502(100); //if timing is enabled, this value is in 6502 clock ticks. otherwise, simply instruction count.
  if (serial_debug.available()) {
    // curkey = serial_debug.read() & 0x7F;
    curkey = serial_debug.read() ;
    //digitalWrite(BLINK_PIN, LOW);
    //delayMicroseconds(100);
    //digitalWrite(BLINK_PIN, HIGH);
  }
}

