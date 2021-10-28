//Created by Maya Ayoub, July 2021
 #include <Stepper.h>
// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver
// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
#define sensor A2

void setup() {
  Serial.begin(9600);
    myStepper.setSpeed(5);
}

void loop() {
 for (int j=0;j<=300;j++)
 {
 data();
Motor(j);
//spectrum();
 }
 return 0;
  }
  
void data() {
 int value = analogRead(sensor);
  value = map(value, 0, 1024, 300, 1100);
  Serial.print(value);
  Serial.println(" ");
}
 
// Include the Arduino Stepper.h library:
void Motor(int j) {
  // Step one revolution in one direction:
  myStepper.step(10);
  delay(10); 
}

/*
void spectrum (int j)
{
int Step = j*8;
double i = ((Step/2048)*2)*3.1415;
double d = 0.000001;
double m = 1;
double phi = (35/180)*3.1415;

double lambda; 
lambda = ((d*sin(phi+i)-sin(i))/m)*pow(10,9);
Serial.println(lambda);

*/
