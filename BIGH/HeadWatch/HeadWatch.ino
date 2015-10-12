/*
  Arduino TFT text example

  This example demonstrates how to draw text on the
  TFT with an Arduino. The Arduino reads the value
  of an analog sensor attached to pin A0, and writes
  the value to the LCD screen, updating every
  quarter second.

  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald

  http://arduino.cc/en/Tutorial/TFTDisplayText

 */

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

// char array to print to the screen
char GASPrintout[4];
char ProxPrintout[4];

void setup() {

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to yellow
  TFTscreen.stroke(255, 255, 0);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
//  TFTscreen.text("Sensor Value :\n ", 0, 0);
  
  // ste the font size very large for the loop
  TFTscreen.setTextSize(5);
}

void loop() {

  //ricezione segnali e inizializzazione identificatore
  
  
  //costruzione della stringa stampata
  
  
  //visualizzazione
  
  
  // Read the value of the sensor on A0
  String GAS = String(analogRead(A0));
  String Prox = String(analogRead(A1));
  // convert the reading to a char array
  GAS.toCharArray(GASPrintout, 4);
  Prox.toCharArray(ProxPrintout, 4);
  // set the font color
  TFTscreen.stroke(255, 255, 255);
  // print the sensor value
  TFTscreen.text(GASPrintout, 0, 20);
  // wait for a moment
  delay(250);
  TFTscreen.text(ProxPrintout, 0, 20);
  delay(250);
  // erase the text you just wrote
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.text(GASPrintout, 0, 20);
  delay(250);
  TFTscreen.text(ProxPrintout, 0, 20);
}

