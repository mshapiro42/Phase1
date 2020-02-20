#define LEFT_JOYSTICK A3
#define RIGHT_JOYSTICK A0
#define ESTOP 6

uint16_t left_read, right_read;
uint8_t left_value, right_value, left_value_p, right_value_p;


char c_data;
const int status_LED = 13;

void setup() {
  // put your setup code here, to run once:
  left_value_p = 127;
  right_value_p = 127;
  SerialUSB.begin(9600);

  //while (!SerialUSB);
  Serial1.begin(9600);

  pinMode(status_LED, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

  SerialUSB.println("Wireless Joystick Controller's XBee Ready to Communicate");
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  left_read = analogRead(LEFT_JOYSTICK);
  right_read = analogRead(RIGHT_JOYSTICK);
  left_value = map(left_read, 0, 1023, 0, 255);
  right_value = map(right_read, 0, 1023, 0, 255);
  if (SerialUSB.available()) {
    c_data = SerialUSB.read();
    Serial1.print(c_data);

    SerialUSB.print("Sending Character Here, ");
    SerialUSB.print(c_data);
    digitalWrite(status_LED, HIGH);
  }

  if ((left_value != left_value_p) || (right_value != right_value_p)) {
    SerialUSB.print("Updating Speed Values: ");
    SerialUSB.print(left_value);
    SerialUSB.print(" ");
    SerialUSB.println(right_value);
    if (left_value != left_value_p) {
      Serial1.write("l");
      Serial1.write(left_value);
    }
    if (right_value != right_value_p) {
      Serial1.write("r");
      Serial1.write(right_value);
    }
  }
  delay(100);
  digitalWrite(status_LED, LOW);
  left_value_p = left_value;
  right_value_p = right_value;
}
