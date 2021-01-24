/*
 * LED Light Show
 * 
 * This code is my first Arduino Learning project.  My son and I are learning
 * Arduino coding together as part of Mark Rober's Creative Engineering class.
 * 
 * This code is derived from the Fade example in the Arduino IDE:
 * http://www.arduino.cc/en/Tutorial/Fade
 * 
 * This example code is in the public domain.
*/

int WHITE_LED = 3;
int YELLOW_LED = 5;
int RED_LED = 6;
int BLUE_LED = 11;

int ALL_LEDS[4] = { WHITE_LED, YELLOW_LED, RED_LED, BLUE_LED };
int ALL_LED_COUNT = 4;

int BRIGHTNESS_MIN = 0;
int BRIGHTNESS_MAX = 255;


// the setup routine runs once when you press reset:
void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

// percent is a value from 0.0 to 1.0
int calculateBrightness(float percent)
{
  float floatMax = (float)BRIGHTNESS_MAX;
  float floatResult = floatMax * percent;
  int intResult = (int)floatResult;
  return intResult;
}

//
// Fade's an LED from full off to full brightness in a given amount of time
// 
void fadeOn(int whichLed, int milliseconds)
{
  int list[1] = { whichLed };
  fadeOn(list, 1, milliseconds);
}

void fadeOn(int whichLeds[], int ledCount, int milliseconds)
{
    int elapsedTime = 0;

    int steps = 10;
    int sleepMillis = (int)((float)milliseconds / (float)steps);

    do
    {
      float percentElapsedTime = (float)elapsedTime / (float)milliseconds;
      int brightness = (int)(percentElapsedTime * (float)(BRIGHTNESS_MAX));

      for (int i = 0; i < ledCount; i++)
      {
        analogWrite(whichLeds[i], brightness);
      }

      delay(sleepMillis);
      elapsedTime += sleepMillis;
      
    }
    while (elapsedTime < milliseconds);
    
}

//
// Fade's on LED from full brightness to off in a given amount of time
//
void fadeOff(int whichLed, int milliseconds)
{
  int list[1] = { whichLed };
  fadeOff(list, 1, milliseconds);
}

void fadeOff(int whichLeds[], int ledCount, int milliseconds)
{
    int elapsedTime = 0;

    int steps = 10;
    int sleepMillis = (int)((float)milliseconds / (float)steps);

    do
    {
      float percentElapsedTime = (float)elapsedTime / (float)milliseconds;
      int brightness = BRIGHTNESS_MAX - (int)(percentElapsedTime * (float)(BRIGHTNESS_MAX));

      for (int i = 0; i < ledCount; i++)
      {
        analogWrite(whichLeds[i], brightness);
      }

      delay(sleepMillis);
      elapsedTime += sleepMillis;
      
    }
    while (elapsedTime < milliseconds);

    //analogWrite(whichLed, 0);

    for (int i = 0; i < ledCount; i++)
    {
      analogWrite(whichLeds[i], BRIGHTNESS_MIN);
    }
}

void fadeOnOff(int whichLed, int milliseconds)
{
  int list[1] = { whichLed };
  fadeOnOff(list, 1, milliseconds);
}

void fadeOnOff(int whichLeds[], int ledCount, int milliseconds)
{
  fadeOn(whichLeds, ledCount, milliseconds / 2);
  fadeOff(whichLeds, ledCount, milliseconds / 2);
}

// Fade a single LED on/off a number of times
void flutter(int whichLed, int count, int milliseconds)
{
  for (int i = 0; i < count; i++)
  {
    fadeOnOff(whichLed, milliseconds);
  }
}

void flutter(int whichLeds[], int ledCount, int count, int milliseconds)
{
  for (int i = 0; i < count; i++)
  {
    fadeOnOff(whichLeds, ledCount, milliseconds);
  }
}

void flutterTwo(int whichLed, int whichLedTwo, int count, int milliseconds)
{
  int list[2] = { whichLed, whichLedTwo };
  flutter(list, 2, count, milliseconds);
}

void flutterThree(int whichLed, int whichLedTwo,int whichLedThree, int count, int milliseconds)
{
  int list[3] = { whichLed, whichLedTwo, whichLedThree };
  flutter(list, 3, count, milliseconds);
}

void changeBrightness(int whichLed, float percent)
{
  analogWrite(whichLed, calculateBrightness(percent));
}

void turnOn(int whichLed)
{
  changeBrightness(whichLed, 1.0);
}

void turnOff(int whichLed)
{
  changeBrightness(whichLed, 0.0); 
}

int randomLedIndex()
{
  int val = random(0, ALL_LED_COUNT);
  //Serial.println(val);
  return val;
}

int randomLed()
{
  return ALL_LEDS[randomLedIndex()];
}

void randomLedList(int* list, int* count)
{
  *count = random(1, ALL_LED_COUNT + 1);
  for (int i = 0; i < *count; i++)
  {
    list[i] = randomLed();
  }
}

// the loop routine runs over and over again forever:
void loop() 
{
  int flutterCount = random(2, 20);
  int flutterTime = random(50, 100);

  int count = 0;
  int ledList[ALL_LED_COUNT] = {0,0,0,0};

  randomLedList(ledList, &count);
  flutter(ledList, count, flutterCount, flutterTime);
}
