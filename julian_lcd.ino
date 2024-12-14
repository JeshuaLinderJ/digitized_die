#include <WiFi.h>
#include <time.h>
#include <TFT_eSPI.h>
#include <SPI.h>
// #include "d6.h"

#define BUTTON_PIN1 21 // GPIO21 for the first button
#define BUTTON_PIN2 19 // GPIO19 for the second button

unsigned long lastDebounceTime = 0; // For debouncing
unsigned long debounceDelay = 50;   // 50ms debounce time

TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h

bool button1Pressed = false; // Bool to control button control
int diceQuantity = 0;

void setup() {
  Serial.begin(9600);

  // Screen initialization
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  pinMode(BUTTON_PIN1, INPUT_PULLUP); // Configure button pin 1 with internal pull-up
  pinMode(BUTTON_PIN2, INPUT_PULLUP); // Configure button pin 2 with internal pull-up

  randomSeed(analogRead(0)); // Seed the random number generator

  // drawD2(80, 40, 50, TFT_WHITE, randomRoll(2));

}

void loop() {
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);

  // d6(); // D6 Dice roll animation
  // d2();

  
  if (buttonState2 == LOW){
    Serial.println("Button 2 pressed!");
    Serial.println(randomRoll(6));
  } else {
    // Serial.println("Button 2 released!");
  }
  delay(1000);
}

void drawD6(int x, int y, int size, uint16_t color, int face) {
  int halfSize = size / 2;

  // Draw outer rectangle for the dice
  tft.drawRect(x - halfSize, y - halfSize, size, size, color);

  // Calculate positions for dots based on face
  int dotRadius = size / 10;
  int offset = size / 4;

  // Define dot positions
  int dots[7][2] = {
    {x, y},                                 // Center (face 1, 3, 5)
    {x - offset, y - offset},               // Top-left (face 4, 5, 6)
    {x + offset, y + offset},               // Bottom-right (face 4, 5, 6)
    {x - offset, y + offset},               // Bottom-left (face 2, 3, 6)
    {x + offset, y - offset},               // Top-right (face 2, 3, 6)
    {x - offset, y},                        // Middle-left (face 6)
    {x + offset, y},                        // Middle-right (face 6)
  };

  // Draw dots based on face number
  switch (face) {
    case 1:
      tft.fillCircle(dots[0][0], dots[0][1], dotRadius, color);
      break;
    case 2:
      tft.fillCircle(dots[3][0], dots[3][1], dotRadius, color);
      tft.fillCircle(dots[4][0], dots[4][1], dotRadius, color);
      break;
    case 3:
      tft.fillCircle(dots[0][0], dots[0][1], dotRadius, color);
      tft.fillCircle(dots[3][0], dots[3][1], dotRadius, color);
      tft.fillCircle(dots[4][0], dots[4][1], dotRadius, color);
      break;
    case 4:
      tft.fillCircle(dots[1][0], dots[1][1], dotRadius, color);
      tft.fillCircle(dots[2][0], dots[2][1], dotRadius, color);
      tft.fillCircle(dots[3][0], dots[3][1], dotRadius, color);
      tft.fillCircle(dots[4][0], dots[4][1], dotRadius, color);
      break;
    case 5:
      tft.fillCircle(dots[0][0], dots[0][1], dotRadius, color);
      tft.fillCircle(dots[1][0], dots[1][1], dotRadius, color);
      tft.fillCircle(dots[2][0], dots[2][1], dotRadius, color);
      tft.fillCircle(dots[3][0], dots[3][1], dotRadius, color);
      tft.fillCircle(dots[4][0], dots[4][1], dotRadius, color);
      break;
    case 6:
      tft.fillCircle(dots[1][0], dots[1][1], dotRadius, color);
      tft.fillCircle(dots[2][0], dots[2][1], dotRadius, color);
      tft.fillCircle(dots[3][0], dots[3][1], dotRadius, color);
      tft.fillCircle(dots[4][0], dots[4][1], dotRadius, color);
      tft.fillCircle(dots[5][0], dots[5][1], dotRadius, color);
      tft.fillCircle(dots[6][0], dots[6][1], dotRadius, color);
      break;
  }
}
void drawD2(int x, int y, int size, uint16_t color, int face) {
  int halfSize = size / 2;

  // Draw heads or tails based on face number
  if (face == 1) {
    // Draw heads
    tft.fillCircle(x, y, halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("H", x, y - 10, 4);
  } else {
    // Draw tails
    tft.fillCircle(x, y, halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("T", x, y - 10, 4);
  }
}

int randomRoll(int d){ // Roll logic per d#, using standard die used in DnD, and percentage value roll under d100 (%)
  switch(d){
    case 2:
      return random(1, 3);
    case 4:
      return random(1, 5);
    case 6:
      return random(1, 7);
    case 8:
      return random(1, 9);
    case 10:
      return random(1, 11);
    case 12:
      return random(1, 13);
    case 20:
      return random(1, 21);
    case 100:
      return random(1, 101);
    default:
      return -1; // Return -1 for unsupported values of d
  }
}

void d6(){
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  if (buttonState1 == LOW && !button1Pressed) { // Button is pressed
    for(int i = 0 ; i < 14 ; i++){
      Serial.println("Button 1 pressed!");
      // Serial.println("Random number: " + String(randomNumber));
      // Serial.println("---------------------------------");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD6(80, 40, 50, TFT_RED, randomRoll(6));
          button1Pressed = true;
          break;
        case 2:
          drawD6(80, 40, 50, TFT_ORANGE, randomRoll(6));
          break;
        case 3:
          drawD6(80, 40, 50, TFT_YELLOW, randomRoll(6));
          break;
        case 4:
          drawD6(80, 40, 50, TFT_GREEN, randomRoll(6));
          break;
        case 5:
          drawD6(80, 40, 50, TFT_BLUE, randomRoll(6));
          break;
        case 6:
          drawD6(80, 40, 50, TFT_PURPLE, randomRoll(6));
          break;
        case 7:
          drawD6(80, 40, 50, TFT_VIOLET, randomRoll(6));
          break;
        case 8:
          drawD6(80, 40, 50, TFT_BLUE, randomRoll(6));
          break;
        case 9:
          drawD6(80, 40, 50, TFT_GREEN, randomRoll(6));
          break;
        case 10:
          drawD6(80, 40, 50, TFT_YELLOW, randomRoll(6));
          break;
        case 11:
          drawD6(80, 40, 50, TFT_ORANGE, randomRoll(6));
          break;
        case 12:
          drawD6(80, 40, 50, TFT_RED, randomRoll(6));
          break;
        case 13:
          drawD6(80, 40, 50, TFT_BLACK, randomRoll(6));
          break;
      }
      delay(75);
    }
  } else { // Button is not pressed
    if(button1Pressed == true){
      drawD6(80, 40, 50, TFT_WHITE, randomRoll(6));
      button1Pressed = false;
    }
  }
}

void d2(){
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  if (buttonState1 == LOW && !button1Pressed) { // Button is pressed
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      // Serial.println("Random number: " + String(randomNumber));
      // Serial.println("---------------------------------");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD2(80, 40, 50, TFT_RED, randomRoll(2));
          button1Pressed = true;
          break;
        case 2:
          drawD2(80, 40, 50, TFT_ORANGE, randomRoll(2));
          break;
        case 3:
          drawD2(80, 40, 50, TFT_YELLOW, randomRoll(2));
          break;
        case 4:
          drawD2(80, 40, 50, TFT_GREEN, randomRoll(2));
          break;
        case 5:
          drawD2(80, 40, 50, TFT_BLUE, randomRoll(2));
          break;
        case 6:
          drawD2(80, 40, 50, TFT_PURPLE, randomRoll(2));
          break;
        case 7:
          drawD2(80, 40, 50, TFT_VIOLET, randomRoll(2));
          break;
        case 8:
          drawD2(80, 40, 50, TFT_BLUE, randomRoll(2));
          break;
        case 9:
          drawD2(80, 40, 50, TFT_GREEN, randomRoll(2));
          break;
        case 10:
          drawD2(80, 40, 50, TFT_YELLOW, randomRoll(2));
          break;
        case 11:
          drawD2(80, 40, 50, TFT_ORANGE, randomRoll(2));
          break;
        case 12:
          drawD2(80, 40, 50, TFT_RED, randomRoll(2));
          break;
        case 13:
          drawD2(80, 40, 50, TFT_BLACK, randomRoll(2));
          break;
      }
      delay(110);
    }
  } else { // Button is not pressed
    if(button1Pressed == true){
      drawD2(80, 40, 50, TFT_WHITE, randomRoll(2));
      button1Pressed = false;
    }
  }
}