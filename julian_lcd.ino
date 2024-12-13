#include <WiFi.h>
#include <time.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define BUTTON_PIN 21 // GPIO21 for the button

unsigned long lastDebounceTime = 0; // For debouncing
unsigned long debounceDelay = 50;   // 50ms debounce time

TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h

int randomNumber; // Declare globally

void setup() {
  Serial.begin(9600);

  // Screen initialization
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button pin with internal pull-up

  randomSeed(analogRead(0)); // Seed the random number generator
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) { // Button is pressed
    randomNumber = random(1, 7); // Generate random number
    Serial.println("Button pressed!");
    Serial.println("Random number: " + String(randomNumber));
    Serial.println("---------------------------------");
    

    // Clear the previous drawing
    tft.fillScreen(TFT_BLACK);

    // Draw the dice with the new random number
    drawD6(80, 40, 50, TFT_RED, randomNumber);
  } else { // Button is not pressed
    Serial.println("Button Released!");
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