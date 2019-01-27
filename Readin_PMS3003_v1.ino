/*   Sensor: PMS3003 Plantower
 *   PM1.0, PM2.5, PM10 (ug/m3)
 *   v1
 */
#include <SoftwareSerial.h>

SoftwareSerial pms(6, 7);   // RX, TX

// counting num of bytes
int count = 0;

// variables
unsigned char pm[3];

void setup() {
  Serial.begin(9600);     // 9600 baudrate for the sensor
  pms.begin(9600);
}

void loop() 
{
  if (pms.available()) // check serial
  {
    dust();               // call function dust() for reading data
  }
}


void dust()       // function for reading and printing data
{
  int inByte = pms.read();   // store received byte to variable 'inByte'
   
  if (inByte == 0x42)           
  {
    count = 0;        // reset counting value if character of 1st byte is detected
    pm[0] = (char)0;
    pm[1] = (char)0;
    pm[2] = (char)0;
  }

  else                // otherwise keep counting up
  {
    count++;
    if (count == 11)  // Byte 12 - PM1.0
    {
      pm[0] = inByte;  
    }
    if (count == 13)  // Byte 14 - PM2.5
    {
      pm[1] = inByte;
    }
    if (count == 15)  // Byte 16 - PM10
    {
      pm[2] = inByte;
    }
    if (count == 16)  // After capturing PM1.0, PM2.5, PM10 values, print them out
    {
      Serial.print("PM1.0: ");
      Serial.print(pm[0], DEC);
      Serial.print(" PM2.5: ");
      Serial.print(pm[1], DEC);
      Serial.print(" PM10: ");
      Serial.println(pm[2], DEC);
    }
  }
}
