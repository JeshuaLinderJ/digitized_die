#include <WiFi.h>
#include <time.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define BUTTON_PIN1 21 // GPIO21 for the first button
#define BUTTON_PIN2 19 // GPIO19 for the second button
unsigned long lastDebounceTime = 0; // For debouncing
unsigned long debounceDelay = 50;   // 50ms debounce time
TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h

// ================================================
int diceQuantity = 0;
int choiceCount = 0;
// ================================================
void setup() {
  Serial.begin(9600);

  // Screen initialization
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  pinMode(BUTTON_PIN1, INPUT_PULLUP); // Configure button pin 1 with internal pull-up
  pinMode(BUTTON_PIN2, INPUT_PULLUP); // Configure button pin 2 with internal pull-up
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN1), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN2), button2ISR, FALLING);

  randomSeed(analogRead(0)); // Seed the random number generator

  // Draw menu
  int size = 16;
  tft.drawRect(16, 16, size, size, TFT_WHITE); 
  tft.drawRect(48, 16, size, size, TFT_WHITE); 
  tft.drawRect(16, 48, size, size, TFT_WHITE); 
  tft.drawRect(48, 48, size, size, TFT_WHITE); 
  tft.drawRect(96, 16, size, size, TFT_WHITE); 
  tft.drawRect(128, 16, size, size, TFT_WHITE); 
  tft.drawRect(96 , 48, size, size, TFT_WHITE); 
  tft.drawRect(128, 48, size, size, TFT_WHITE); 
  

}

// ================================================
volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
// ================================================

void loop() {
  bool inLoop = true; // Control for whether loop is running or not
  int size = 16;

  // Keep choiceCount within range of choices
  if(choiceCount > 8){
    choiceCount = 0;
  }
  if (button2Pressed && inLoop){
    button2Pressed = false; // reset flag
    // Serial.println("Button 2 pressed!");
    tft.fillScreen(TFT_BLACK);
    // tft.setTextColor(TFT_BLACK, TFT_BLACK);
    choiceCount++;

    // Switch case for choiceCount options
    switch(choiceCount){
      case 0:
        tft.fillScreen(TFT_BLACK);
        break;
      case 1:
        tft.fillRect(16, 16, size, size, TFT_WHITE);
        tft.drawRect(128, 48, size, size, TFT_WHITE);

        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D2", 18, 36);
        break;
      case 2:
        tft.fillRect(48, 16, size, size, TFT_WHITE);
        tft.drawRect(16, 16, size, size, TFT_WHITE);

        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D4", 50, 36);
        break;
      case 3:
        tft.fillRect(16, 48, size, size, TFT_WHITE);
        tft.drawRect(48, 16, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D6", 19, 36);
        break;
      case 4:
        tft.fillRect(48, 48, size, size, TFT_WHITE);
        tft.drawRect(16, 48, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D8", 50, 36);
        break;
      case 5:
        tft.fillRect(96, 16, size, size, TFT_WHITE);
        tft.drawRect(48, 48, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D10", 96, 36);
        break;
      case 6:
        tft.fillRect(128 , 16, size, size, TFT_WHITE);
        tft.drawRect(96, 16, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D12", 128, 36);
        break;
      case 7:
        tft.fillRect(96, 48, size, size, TFT_WHITE);
        tft.drawRect(96 , 16, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 48, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D20", 96, 36);
        break;
      case 8:
        tft.fillRect(128, 48, size, size, TFT_WHITE);
        tft.drawRect(96, 48, size, size, TFT_WHITE);

        tft.drawRect(16, 16, size, size, TFT_WHITE); 
        tft.drawRect(16, 48, size, size, TFT_WHITE); 
        tft.drawRect(48, 16, size, size, TFT_WHITE); 
        tft.drawRect(48, 48, size, size, TFT_WHITE); 
        tft.drawRect(96, 16, size, size, TFT_WHITE); 
        tft.drawRect(128, 16, size, size, TFT_WHITE); 
        tft.setTextSize(1);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.drawString("D100", 125, 36);
        break;
    }
  }

  if(button1Pressed && inLoop){
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
      case 4:
        d8();
        break;
      case 5:
        d10();
        break;
      case 6:
        d12();
        break;
      case 7:
        d12();
        break;
      case 8:
        d12();
        break;
    }
    button1Pressed = false; // reset flag
    inLoop = false;
    delay(125);
  }

  // ------------------------------------------------
  // TESTING
  // d2();
  // d4();
  // d6();
  // ------------------------------------------------

  delay(1000);
}
// ================================================
// FUNCTIONS PER D#

// ------------------------------------------------
// D2 (coin flip)
void d2(){
  // tft.setTextSize(1);
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD2(80, 40, 50, TFT_RED, randomRoll(2));
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
          drawD2(80, 40, 50, TFT_WHITE, randomRoll(2));
          break;
      }
      delay(110);
    }
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
// ------------------------------------------------
// D4 (triangular dice)

void d4(){
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD4(80, 40, 50, TFT_RED, randomRoll(4));
          break;
        case 2:
          drawD4(80, 40, 50, TFT_ORANGE, randomRoll(4));
          break;
        case 3:
          drawD4(80, 40, 50, TFT_YELLOW, randomRoll(4));
          break;
        case 4:
          drawD4(80, 40, 50, TFT_GREEN, randomRoll(4));
          break;
        case 5:
          drawD4(80, 40, 50, TFT_BLUE, randomRoll(4));
          break;
        case 6:
          drawD4(80, 40, 50, TFT_PURPLE, randomRoll(4));
          break;
        case 7:
          drawD4(80, 40, 50, TFT_VIOLET, randomRoll(4));
          break;
        case 8:
          drawD4(80, 40, 50, TFT_BLUE, randomRoll(4));
          break;
        case 9:
          drawD4(80, 40, 50, TFT_GREEN, randomRoll(4));
          break;
        case 10:
          drawD4(80, 40, 50, TFT_YELLOW, randomRoll(4));
          break;
        case 11:
          drawD4(80, 40, 50, TFT_ORANGE, randomRoll(4));
          break;
        case 12:
          drawD4(80, 40, 50, TFT_RED, randomRoll(4));
          break;
        case 13:
          delay(1000);
          drawD4(80, 40, 50, TFT_WHITE, randomRoll(4));
          break;
      }
      delay(110);
    }
  }
}

void drawD4(int x, int y, int size, uint16_t color, int face) {
  int halfSize = size / 2;
  if(face == 1) {
    // Draw heads
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("1", x, y - 10, 4);
  } else if(face == 2){
    
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("2", x, y - 10, 4);
  } else if(face == 3){
    
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("3", x, y - 10, 4);
  } else if(face == 4){
    
    tft.fillTriangle(x, y - halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("4", x, y - 10, 4);
  }
}
// ------------------------------------------------
// D6 (standard dice)

void d6(){
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      Serial.println("Button 1 pressed!");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD6(80, 40, 50, TFT_RED, randomRoll(6));
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
          drawD6(80, 40, 50, TFT_WHITE, randomRoll(6));
          break;
      }
      delay(75);
    }
  }
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
// ------------------------------------------------
// D8

void d8(){
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD8(80, 29, 50, TFT_RED, randomRoll(8));
          break;
        case 2:
          drawD8(80, 29, 50, TFT_ORANGE, randomRoll(8));
          break;
        case 3:
          drawD8(80, 29, 50, TFT_YELLOW, randomRoll(8));
          break;
        case 4:
          drawD8(80, 29, 50, TFT_GREEN, randomRoll(8));
          break;
        case 5:
          drawD8(80, 29, 50, TFT_BLUE, randomRoll(8));
          break;
        case 6:
          drawD8(80, 29, 50, TFT_PURPLE, randomRoll(8));
          break;
        case 7:
          drawD8(80, 29, 50, TFT_VIOLET, randomRoll(8));
          break;
        case 8:
          drawD8(80, 29, 50, TFT_BLUE, randomRoll(8));
          break;
        case 9:
          drawD8(80, 29, 50, TFT_GREEN, randomRoll(8));
          break;
        case 10:
          drawD8(80, 29, 50, TFT_YELLOW, randomRoll(8));
          break;
        case 11:
          drawD8(80, 29, 50, TFT_ORANGE, randomRoll(8));
          break;
        case 12:
          drawD8(80, 29, 50, TFT_RED, randomRoll(8));
          break;
        case 13:
          delay(1000);
          // drawD8(80, 30, 50, TFT_WHITE, randomRoll(8));
          drawD8(80, 29, 50, TFT_WHITE, randomRoll(8));
          break;
      }
      delay(110);
    }
  }
}

void drawD8(int x, int y, int size, uint16_t color, int face) {
  int halfSize = size / 2;
  if(face == 1) {
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("1", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 2){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("2", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 3){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("3", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 4){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("4", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 5) {
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("5", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 6){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("6", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 7){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("7", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  } else if(face == 8){
    tft.fillTriangle(60, 40, 80, 72, 100, 40, color);
    tft.fillTriangle(60, 40, 80, 8, 100, 40, color);
    // tft.fillTriangle(x, y + halfSize + 5, x - halfSize + 5, y + halfSize - 5, x + halfSize - 5, y + halfSize - 5, color); // save for other shapes
    tft.setTextColor(TFT_BLACK, color);
    tft.drawCentreString("8", x, y - 10, 4);
    tft.drawLine(60, 40, 100, 40, TFT_BLACK);
  }
}

// ------------------------------------------------
// D10

void d10(){
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD10(80, 29, 50, TFT_RED, randomRoll(10));
          break;
        case 2:
          drawD10(80, 29, 50, TFT_ORANGE, randomRoll(10));
          break;
        case 3:
          drawD10(80, 29, 50, TFT_YELLOW, randomRoll(10));
          break;
        case 4:
          drawD10(80, 29, 50, TFT_GREEN, randomRoll(10));
          break;
        case 5:
          drawD10(80, 29, 50, TFT_BLUE, randomRoll(10));
          break;
        case 6:
          drawD10(80, 29, 50, TFT_PURPLE, randomRoll(10));
          break;
        case 7:
          drawD10(80, 29, 50, TFT_VIOLET, randomRoll(10));
          break;
        case 8:
          drawD10(80, 29, 50, TFT_BLUE, randomRoll(10));
          break;
        case 9:
          drawD10(80, 29, 50, TFT_GREEN, randomRoll(10));
          break;
        case 10:
          drawD10(80, 29, 50, TFT_YELLOW, randomRoll(10));
          break;
        case 11:
          drawD10(80, 29, 50, TFT_ORANGE, randomRoll(10));
          break;
        case 12:
          drawD10(80, 29, 50, TFT_RED, randomRoll(10));
          break;
        case 13:
          delay(1000);
          // draw10(80, 30, 50, TFT_WHITE, randomRoll(10));
          drawD10(80, 29, 50, TFT_WHITE, randomRoll(10));
          break;
      }
      delay(110);
    }
  }
}

void drawD10(int x, int y, int size, uint16_t color, int face) { // NOTE: Replace triangle logic with lines to avoid visual bugs
  int halfSize = size / 2;
  if(face == 1) {
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_WHITE);
    tft.drawCentreString("1", 80, 30, 4);
  } else if(face == 2){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("2", 80, 30, 4);
  } else if(face == 3){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("3", 80, 30, 4);
  } else if(face == 4){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("4", 80, 30, 4);
  } else if(face == 5) {
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("5", 80, 30, 4);
  } else if(face == 6){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("6", 80, 30, 4);
  } else if(face == 7){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("7", 80, 30, 4);
  } else if(face == 8){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("8", 80, 30, 4);
  } else if(face == 9){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("9", 80, 30, 4);
  } else if(face == 10){
    tft.drawTriangle(48, 40, 80, 8, 64, 38, color);
    tft.drawTriangle(48, 40, 80, 72, 64, 38, color);
    tft.fillTriangle(80, 42, 80, 72, 64, 38, TFT_BLACK);
    tft.fillTriangle(80, 42, 80, 72, 96, 38, TFT_BLACK);
    tft.drawTriangle(112,40, 80, 72, 96, 38, color);
    tft.drawTriangle(112, 40, 80, 8, 96, 38, color);
    tft.drawTriangle(64, 38, 80, 8, 96, 38, color);
    tft.fillTriangle(64, 38, 80, 42, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 72, TFT_BLACK);
    tft.drawLine(96, 38, 80, 72, TFT_BLACK);
    tft.drawLine(64, 38, 96, 38, TFT_BLACK);
    tft.drawLine(64, 38, 80, 42, color);
    tft.drawLine(96, 38, 80, 42, color);
    tft.drawLine(80, 42, 80, 72, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("10", 80, 30, 4);
  }
}

// ------------------------------------------------
// D12

void d12(){
  if (button1Pressed) { // Button is pressed
    button1Pressed = false; // reset flag
    for(int i = 0 ; i < 14 ; i++){
      // Serial.println("Button 1 pressed!");
      // Clear the previous drawing
      tft.fillScreen(TFT_BLACK);
      switch(i){
        case 1:
          drawD12(80, 29, 50, TFT_RED, randomRoll(12));
          break;
        case 2:
          drawD12(80, 29, 50, TFT_ORANGE, randomRoll(12));
          break;
        case 3:
          drawD12(80, 29, 50, TFT_YELLOW, randomRoll(12));
          break;
        case 4:
          drawD12(80, 29, 50, TFT_GREEN, randomRoll(12));
          break;
        case 5:
          drawD12(80, 29, 50, TFT_BLUE, randomRoll(12));
          break;
        case 6:
          drawD12(80, 29, 50, TFT_PURPLE, randomRoll(12));
          break;
        case 7:
          drawD12(80, 29, 50, TFT_VIOLET, randomRoll(12));
          break;
        case 8:
          drawD12(80, 29, 50, TFT_BLUE, randomRoll(12));
          break;
        case 9:
          drawD12(80, 29, 50, TFT_GREEN, randomRoll(12));
          break;
        case 10:
          drawD12(80, 29, 50, TFT_YELLOW, randomRoll(12));
          break;
        case 11:
          drawD12(80, 29, 50, TFT_ORANGE, randomRoll(12));
          break;
        case 12:
          drawD12(80, 29, 50, TFT_RED, randomRoll(12));
          break;
        case 13:
          delay(1000);
          drawD12(80, 29, 50, TFT_WHITE, randomRoll(12));
          break;
      }
      delay(110);
    }
  }
}

void drawD12(int x, int y, int size, uint16_t color, int face) { // NOTE: Replace triangle logic with lines to avoid visual bugs
  int halfSize = size / 2;
  if(face == 1) {
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("1", 80, 30, 4);
  } else if(face == 2){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("2", 80, 30, 4);
  } else if(face == 3){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("3", 80, 30, 4);
  } else if(face == 4){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("4", 80, 30, 4);
  } else if(face == 5) {
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("5", 80, 30, 4);
  } else if(face == 6){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("6", 80, 30, 4);
  } else if(face == 7){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("7", 80, 30, 4);
  } else if(face == 8){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("8", 80, 30, 4);
  } else if(face == 9){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("9", 80, 30, 4);
  } else if(face == 10){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("10", 80, 30, 4);
  } else if(face == 11){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("11", 80, 30, 4);
  } else if(face == 12){
    tft.drawLine(58, 18, 66, 12, color);
    tft.drawLine(66, 12, 94, 12, color);
    tft.drawLine(94, 12, 102, 18, color);
    tft.drawLine(102, 18, 80, 22, color);
    tft.drawLine(80, 22, 58, 18, color);
    tft.drawLine(58, 18, 50, 34, color);
    tft.drawLine(50, 34, 64, 50, color);
    tft.drawLine(64, 50, 80, 40, color);
    tft.drawLine(80, 40, 80, 22, color);
    tft.drawLine(102, 18, 110, 34, color);
    tft.drawLine(110, 34, 100, 66, color);
    tft.drawLine(110, 34, 96, 50, color);
    tft.drawLine(100, 66, 90, 70, color);
    tft.drawLine(90, 70, 96, 50, color);
    tft.drawLine(96, 50, 80, 40, color);
    tft.drawLine(90, 70, 70, 70, color);
    tft.drawLine(70, 70, 60, 66, color);
    tft.drawLine(60, 66, 50, 34, color);
    tft.drawLine(70, 70, 64, 50, color);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawCentreString("12", 80, 30, 4);
  }
}

// ================================================
// Random roll logic

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
// ================================================

void button1ISR() {
    button1Pressed = true; // Set flag on interrupt
}
void button2ISR() {
    button2Pressed = true; // Set flag on interrupt
}
