//Created by Maya Ayoub, July 2021
//IMPORTANT: How to use this code: Run it, open serial, go to https://www.epochconverter.com/ and imput your own time as GMT
//Cont: copy the "Epock timestamp", in serial: type "T(whatever your number was)". For example: T1627403725

#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "DHT.h"
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
#include <TimeLib.h>
#define TIME_HEADER "T"
#define TIME_REQUEST 7
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

#define DHTPIN 2   
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  dht.begin();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Humidity");
  lcd.setCursor(0, 1);
  lcd.print("& Temperature Sensor");
  lcd.clear();
   Serial.begin(9600);
   pinMode(13, OUTPUT);
  setSyncProvider( requestSync);  //set function to call when sync required
  Serial.println("Waiting for sync message");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay (2000);

Time();
}

 void Time ()
{
   if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    SensorReadings();  
  }
  if (timeStatus() == timeSet) {
    digitalWrite(13, HIGH); // LED on if synced
  } else {
    digitalWrite(13, LOW);  // LED off if needs refresh
  }
}

void SensorReadings()
{
double h= dht.readHumidity();
double t = dht.readTemperature();
double f = dht.readTemperature(true);
double hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
double hic = dht.computeHeatIndex(t, h, false);

LCDPrint(h,t,f,hif,hic);

}

void LCDPrint (int hum, int tem, int temF, int HIF, int HIC)
{
  lcd.setCursor(0,0); // Set the cursor on the third column and first row.
  lcd.clear();
  lcd.print(hum);
  lcd.print("% ");
  lcd.print(tem);
  lcd.print("C ");
  lcd.print(temF);
  lcd.print("F");
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print(HIC);
  lcd.print("C ");
  lcd.print(HIF);
  lcd.print("F ");
  lcd.print(hour());
  lcd.print(":");
  lcd.print(minute());
  lcd.print(":");
  lcd.print(second());
  

}

void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
