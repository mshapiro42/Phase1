/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

// SoftwareSerial is used to communicate with the XBee
#include <SoftwareSerial.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void motor(int m, int pwm);
int ASCIItoInt(char c);
//End of Auto generated function prototypes by Atmel Studio



#define pwmA 3
#define dirA 12
#define pwmB 11
#define dirB 13
#define A 0
#define B 1
#define deadbandA 30
#define deadbandB 30
#define pushButton 2

int8_t left_read, right_read;
int left_value, right_value, pushValue;
int systemState, num;
char c;
SoftwareSerial XBee(4, 5); // Arduino RX, TX (XBee Dout, Din)

void setup()
{
  // Initialize XBee Software Serial port. Make sure the baud
  // rate matches your XBee setting (9600 is default).
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(pushButton, INPUT_PULLUP);
  systemState = true;
  pushValue = true;
}

void loop()
{
  // In loop() we continously check to see if a command has been
  //  received.
  /*pushValue = digitalRead(pushButton);
    if (pushValue == 0) {
    while (digitalRead(pushButton) == 0);
    systemState = !systemState;
    if (systemState) {
      Serial.println("System On!");
    } else{
      Serial.println("System Off!");
    }
    }*/
  /*if (systemState = true) {

      char c = XBee.read();
      while(XBee.available() < 6);
      left_read = XBee.read();
      right_read = XBee.read();
      //Serial.print("Left Receive: ");
      Serial.print(left_read);
      Serial.println(" ");
      //Serial.print("  Right Receive: ");
      Serial.println(right_read);
      left_value = map(left_read, 0, 255, -255, 255);
      right_value = map(right_read, 0, 255, -255, 255);
      motor(B, left_value);
      motor(A, right_value);
    }
    }
    else {
    motor(A, 0);
    motor(B, 0);
    }*/
   
  if (XBee.available()>=2) {
    c = XBee.read();
    num = XBee.read();
    //Serial.write(c);
    //Serial.println(num);
    switch (c) {
      case 'l':
        Serial.print("Left ");
        Serial.println(num);
        break;
       /* while(!(XBee.available()));
        c = XBee.read();
        motor(B, ASCIItoInt(c));
        break;*/
      case 'r':
        Serial.print("\t\t");
        Serial.print("Right ");
        Serial.println(num);
        break;
        /*while(!(XBee.available()));
        c = XBee.read();
        motor(A, ASCIItoInt(c));
        break;*/
      default:
        Serial.println("error");
        break;
    }
  }
}

///////////////////////////////////
void motor(int m, int pwm) {
  int dirPin, pwmPin, deadband;
  switch (m) {
    case A:
      dirPin = dirA;
      pwmPin = pwmA;
      deadband = deadbandA;
    case B:
      dirPin = dirB;
      pwmPin = pwmB;
      deadband = deadbandB;
  }
  digitalWrite(dirPin, (pwm >= 0));
  if (abs(pwm) >=  deadband) {
    analogWrite(pwmPin, abs(pwm));
  } else {
    analogWrite(pwmPin, deadband);
  }
}
///////////////////////////////////
// ASCIItoInt
// Helper function to turn an ASCII hex value into a 0-15 byte val
int ASCIItoInt(char c)
{
  if ((c >= '0') && (c <= '9'))
    return c - 0x30; // Minus 0x30
  else if ((c >= 'A') && (c <= 'F'))
    return c - 0x37; // Minus 0x41 plus 0x0A
  else if ((c >= 'a') && (c <= 'f'))
    return c - 0x57; // Minus 0x61 plus 0x0A
  else
    return -1;
}
