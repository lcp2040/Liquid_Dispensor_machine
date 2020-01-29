#include <Adafruit_Fingerprint.h>

#include <LiquidCrystal.h>



int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)

// pin #3 is OUT from arduino (WHITE wire)

SoftwareSerial mySerial(8, 9);

LiquidCrystal lcd(2,3,4,5,6,7); // initialize the library with the numbers of the interface pins
byte sensorInterrupt = 0;  // 0 = digital pin 12
byte sensorPin       = 12;

float calibrationFactor = 4.5;
volatile byte pulseCount; 
const int read = A0; //Sensor AO pin to Arduino pin A0
int value;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

int a;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()

{ 
 Serial.begin(9600); // initialize the serial communications:

lcd.begin(16,2); lcd.setCursor(0,0); lcd.print("Scan your finger");
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

pinMode(13,OUTPUT);

pinMode(12,INPUT);

pinMode(11, OUTPUT);

pinMode(A0, INPUT);

finger.begin(57600); // set the data rate for the sensor serial port }

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}
void loop() // run over and over again

{
  value = analogRead(read); //Read data from analog pin and store it to value variable
  Serial.println(read);
  if (value<=480){ 
    
    Serial.println("Water level: 0mm - Empty!"); 
  }
  else if (value>480 && value<=530){ 
    
    Serial.println("Water level: 0mm to 5mm"); 
  }
  else if (value>530 && value<=615){ 
    Serial.println("Water level: 5mm to 10mm"); 
  }
  else if (value>615 && value<=660){
    Serial.println("Water level: 10mm to 15mm"); 
  } 
  else if (value>660 && value<=680){ 
    Serial.println("Water level: 15mm to 20mm"); 
  }
  else if (value>680 && value<=690){ 
    Serial.println("Water level: 20mm to 25mm"); 
  }
  else if (value>690 && value<=700){
    Serial.println("Water level: 25mm to 30mm"); 
  }
  else if (value>700 && value<=705){ 
    Serial.println("Water level: 30mm to 35mm"); 
  }
  else if (value>705){ 
    Serial.println("Water level: 35mm to 40mm"); 
  }
  
  delay(5000); // Check for new value every 5 sec


getFingerprintID();

delay(100);

digitalWrite (13,HIGH);

 a = digitalRead(sensorPin);
{   
   if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    Serial.print("\t");       // Print tab space
  Serial.print(totalMilliLitres/1000);
  Serial.print("L");
    

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
      attachInterrupt(sensorInterrupt, pulseCounter , FALLING);
  }
}
}
void pulseCounter()
{pulseCount++ ;
}
uint8_t getFingerprintID()

{
  uint8_t p = finger.getImage();

switch (p)

{

case FINGERPRINT_OK:

lcd.clear();

lcd.print(" Image taken... ");

delay(1000);

break;

case FINGERPRINT_NOFINGER:

return p;

case FINGERPRINT_PACKETRECIEVEERR:

return p;

case FINGERPRINT_IMAGEFAIL:

return p;

default:

return p; }

// OK success!

p = finger.image2Tz();

switch (p) {

case FINGERPRINT_OK:

break;

case FINGERPRINT_IMAGEMESS:

return p;

case FINGERPRINT_PACKETRECIEVEERR:

return p;

case FINGERPRINT_FEATUREFAIL:

return p;

case FINGERPRINT_INVALIDIMAGE:

return p;

default:

return p; }

// OK converted!

p = finger.fingerFastSearch();

if (p == FINGERPRINT_OK)

{

lcd.clear();

lcd.print(" Found match! ");
delay(500);
lcd.clear();
digitalWrite(11, HIGH);
lcd.print("Please Collect"); 
delay(10000);
digitalWrite(11,LOW); // turn on green LED to indicate match
lcd.setCursor(0,1);
{ if (value<=480){ 
    lcd.print("Water level: 0mm - Empty!"); 
  }
  else if (value>480 && value<=530){ 
    lcd.print("Water level: 0mm to 5mm"); 
  }
  else if (value>530 && value<=615){ 
    lcd.print("Water level: 5mm to 10mm"); 
  }
  else if (value>615 && value<=660){ 
    lcd.print("Water level: 10mm to 15mm"); 
  } 
  else if (value>660 && value<=680){ 
    lcd.print("Water level: 15mm to 20mm"); 
  }
  else if (value>680 && value<=690){ 
    lcd.print("Water level: 20mm to 25mm"); 
  }
  else if (value>690 && value<=700){ 
    lcd.print("Water level: 25mm to 30mm"); 
  }
  else if (value>700 && value<=705){ 
    lcd.print("Water level: 30mm to 35mm"); 
  }
  else if (value>705){ 
    lcd.print("Water level: 35mm to 40mm"); 
  }
}
}

else if(p == FINGERPRINT_NOTFOUND)

{

lcd.clear();

lcd.setCursor(0,0);

lcd.print(" Did not match! ");

delay(1000);

lcd.clear();

lcd.setCursor(0,0);

lcd.print(" scan finger! ");

return p;

}

else

{ return p; }

// IF FOUND A MATCH............


}
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {

uint8_t p = finger.getImage();

if (p != FINGERPRINT_OK) return -1;

p = finger.image2Tz();

if (p != FINGERPRINT_OK) return -1;

p = finger.fingerFastSearch();

if (p != FINGERPRINT_OK) return -1;
lcd.print(a);

}
