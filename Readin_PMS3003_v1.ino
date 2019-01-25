/*   Sensor: PMS3003 Plantower
 *   PM1.0, PM2.5, PM10 (ug/m3)
 *   v1
 */

// counting num of bytes
int count = 0;

// variables
unsigned char pm01;
unsigned char pm25; 
unsigned char pm10;

void setup() {
  Serial.begin(9600);     // 9600 baudrate for the sensor
}

void loop() 
{
  if (Serial.available()) // check serial
  {
    dust();               // call function dust() for reading data
  }
}


void dust()       // function for reading and printing data
{
  int inByte = Serial.read();   // store received byte to variable 'inByte'
   
  if (inByte == 0x42)           
  {
    count = 0;        // reset counting value if character of 1st byte is detected
  }

  else                // otherwise keep counting up
  {
    count++;
    if (count == 11)  // Byte 12 - PM1.0
    {
      pm01 = inByte;  
    }
    if (count == 13)  // Byte 14 - PM2.5
    {
      pm25 = inByte;
    }
    if (count == 15)  // Byte 16 - PM10
    {
      pm10 = inByte;
    }
    if (count == 16)  // After capturing PM1.0, PM2.5, PM10 values, print them out
    {
      Serial.print("PM1.0: ");
      Serial.print(pm10, DEC);
      Serial.print(" PM2.5: ");
      Serial.print(pm25, DEC);
      Serial.print(" PM10: ");
      Serial.println(pm10, DEC);
    }
  }
}

