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
bool button2Pressed = false;
int diceQuantity = 0;
int choiceCount = 0;

void setup() {
  Serial.begin(9600);

  // Screen initialization
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  pinMode(BUTTON_PIN1, INPUT_PULLUP); // Configure button pin 1 with internal pull-up
  pinMode(BUTTON_PIN2, INPUT_PULLUP); // Configure button pin 2 with internal pull-up

  randomSeed(analogRead(0)); // Seed the random number generator

  // Draw menu
  int size = 25;
  int halfSize = size / 2;
  tft.fillRect(17.5 - halfSize, 37.5 - halfSize, size, size, TFT_WHITE); // Option 1, d2
  tft.fillRect(77.5 - halfSize, 37.5 - halfSize, size, size, TFT_WHITE); // Option 2, d4
  tft.fillRect(137.5 - halfSize, 37.5 - halfSize, size, size, TFT_WHITE); // Option 3, d6
  // drawD2(80, 40, 50, TFT_WHITE, randomRoll(2));

}

void loop() {

  int size = 20;
  int halfSize = size / 2;

  // Keep choiceCount within range of choices
  if(choiceCount > 3){
    choiceCount = 0;
  }

  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);

  // d6(); // D6 Dice roll animation
  // d2();

  
  if (buttonState2 == LOW){
    button2Pressed = true;
    Serial.println("Button 2 pressed!");
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    choiceCount++;

    // Switch case for choiceCount options
  switch(choiceCount){
    case 0:
      tft.fillScreen(TFT_BLACK);
      break;
    case 1:
      tft.drawRect(80 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 2
      tft.drawRect(140 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 3
      tft.fillRect(20 - halfSize, 40 - halfSize, size, size, TFT_RED); // Option 1, coin flip
      tft.setTextColor(TFT_BLACK, TFT_RED);
      tft.drawCentreString("d2", 10, 30, 3);
      break;
    case 2:
      tft.drawRect(20 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 1
      tft.drawRect(140 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 3
      tft.fillRect(80 - halfSize, 40 - halfSize, size, size, TFT_ORANGE); // Option 2, d6 dice
      tft.setTextColor(TFT_BLACK, TFT_ORANGE);
      tft.drawCentreString("d4", 70, 30, 3);
      break;
    case 3:
      tft.drawRect(20 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 1
      tft.drawRect(80 - halfSize, 40 - halfSize, size, size, TFT_WHITE); // Clear option 2
      tft.fillRect(140 - halfSize, 40 - halfSize, size, size, TFT_YELLOW); // Option 3, d4 dice
      tft.setTextColor(TFT_BLACK, TFT_YELLOW);
      tft.drawCentreString("d6", 130, 30, 3);
      break;
    }
  } else {
    button2Pressed = false;
    // Serial.println("Button 2 released!");
  }

  if(buttonState1 == LOW){
    switch(choiceCount){
      case 1:
        d2();
        break;
      case 2:
        d4();
        break;
      case 3:
        d6();
        break;
    }
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

void drawD4(int x, int y, int size, uint16_t color, int face) {
  int halfSize = size / 2;

  // Draw heads or tails based on face number
  if(face == 1) {
    // Draw heads
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("1", x, y - 10, 4);
  } else if(face == 2){
    // Draw tails
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("2", x, y - 10, 4);
  } else if(face == 3){
    // Draw tails
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("3", x, y - 10, 4);
  } else if(face == 4){
    // Draw tails
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("4", x, y - 10, 4);
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


void d2(){
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  if (buttonState1 == LOW && !button1Pressed) { // Button is pressed
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      
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
          delay(1000);
          button1Pressed = false;
          drawD2(80, 40, 50, TFT_WHITE, randomRoll(2));
          break;
      }
      delay(110);
    }
  } else { // Button is not pressed
    if(button1Pressed == true){
      button1Pressed = false;
    }
  }
}


void d6(){
  int buttonState1 = digitalRead(BUTTON_PIN1);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  if (buttonState1 == LOW && !button1Pressed) { // Button is pressed
    for(int i = 0 ; i < 14 ; i++){
      Serial.println("Button 1 pressed!");
      
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
          delay(1000);
          button1Pressed = false;
          drawD6(80, 40, 50, TFT_WHITE, randomRoll(6));
          break;
      }
      delay(75);
    }
  } else { // Button is not pressed
    if(button1Pressed == true){
      button1Pressed = false;
    }
  }
}