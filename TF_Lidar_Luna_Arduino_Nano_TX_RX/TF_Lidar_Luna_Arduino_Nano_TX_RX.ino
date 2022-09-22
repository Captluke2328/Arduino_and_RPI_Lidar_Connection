#include <LiquidCrystal.h>
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object

#include "printf.h"   // Modified to support Intel based Arduino
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2); //RX, TX
// devices such as the Galileo. Download from:
// https://github.com/spaniakos/AES/blob/master/printf.h

// The Software Serial library is an alternative for devices that
// have only one hardware serial port. Delete the comment slashes
// on lines 37 and 38 to invoke the library, and be sure to choose
// the correct RX and TX pins: pins 10 and 11 in this example. Then
// in the 'setup' section, change the name of the hardware 'Serial1'
// port to match the name of your software serial port, such as:
// 'mySerial.begin(115200); etc.

//#include <SoftwareSerial.h>
//SoftwareSerial mySerial( 10, 11);

//const int pin_RS = 8;
//const int pin_EN = 9;
//const int pin_d4 = 4;
//const int pin_d5 = 5;
//const int pin_d6 = 6;
//const int pin_d7 = 7;
//const int pin_BL = 10;
//LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);


int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
int counter = 0;
char dist[11];


void setup() {
  Serial.begin(115200);
//  lcd.begin(16, 2);
//  lcd.setCursor(0,0);
//  lcd.print("Device");
//  lcd.setCursor(0,1);
//  lcd.print("Booted");
  delay(20);               // Give port time to initalize
  printf_begin();          // Initialize printf.
  printf("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // say 'hello'

  mySerial.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin( &mySerial);   // Initialize device library object and...
  // tfmP.begin( &Serial1);   // Initialize device library object and...

  // pass device serial port to the object.

  // Send some example commands to the TFMini-Plus
  // - - Perform a system reset - - - - - - - - - - -
  printf( "Soft reset: ");
  if( tfmP.sendCommand( SOFT_RESET, 0))
  {
    printf( "passed.\r\n");
  }
  else tfmP.printReply();

  delay(500);  // added to allow the System Rest enough time to complete

  // - - Display the firmware version - - - - - - - - -
  printf( "Firmware version: ");
  if( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
  {
    printf( "%1u.", tfmP.version[ 0]); // print three single numbers
    printf( "%1u.", tfmP.version[ 1]); // each separated by a dot
    printf( "%1u\r\n", tfmP.version[ 2]);
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  printf( "Data-Frame rate: ");
  if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    printf( "%2uHz.\r\n", FRAME_20);
  }
  else tfmP.printReply();


  // delay(2000);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Distance");
//  lcd.setCursor(0,1);
//  lcd.print("0000cm");
}

void loop() {
  delay(20);   // Loop delay to match the 20Hz data frame rate
  counter++;
  if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    printf( "Dist:%04icm ", tfDist);   // display distance,
    printf( "Flux:%05i ",   tfFlux);   // display signal strength/quality,
    printf( "Temp:%2i%s",  tfTemp, "C");   // display temperature,
    printf( "\r\n");                   // end-of-line.
    if(counter >= 10){
      sprintf (dist, "%04i", tfDist);
//      lcd.setCursor(0,1);
//      lcd.print(dist);
      counter=0;
    }
  }
  else                  // If the command fails...
  {
    tfmP.printFrame();  // display the error and HEX dataa
  }
}