#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define VRX_PIN A0
#define VRY_PIN A1
#define BUTTON_PIN 2

LiquidCrystal_I2C lcd(0x3f, 6, 4);
Servo myServo;

const int DEBOUNCE_DELAY = 50;

int counter;
int xValue = analogRead(A0);
int yValue = analogRead(A1);
int oldxValue;
int oldyValue;
int cursorX;
int cursorY;
int lastSteadyState = LOW;
int lastFlickerableState = LOW;
int currentState;
int motionStateCurrent = LOW;
int motionStatePrevious = LOW;
int pos = 0;

unsigned long lastDebounceTime = 0;

byte selectBox[8] = {
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};

byte selected[8] = {
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000
};


void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(3, HIGH);
  pinMode(11, HIGH);
  myServo.attach(9);
  myServo.write(0);
  lcd.init();
  lcd.cursor();
  lcd.createChar(0, selectBox);
  lcd.createChar(1, selected);
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.write((byte)0);
  lcd.setCursor(1, 0);
  lcd.print("Few Skittles");
  lcd.setCursor(0, 1);
  lcd.write((byte)0);
  lcd.setCursor(1, 1);
  lcd.print("Some Skittles");
  lcd.setCursor(16,0);
  lcd.write((byte)0);
  lcd.setCursor(17,0);
  lcd.print("More Skittles");
  lcd.setCursor(16,1);
  lcd.write((byte)0);
  lcd.setCursor(17,1);
  lcd.print("Most Skittles");
  lcd.setCursor(32, 0);
  lcd.print("Code by");
  lcd.setCursor(32, 1);
  lcd.print("Evan H");

  lcd.home();
  lcd.backlight();
}

void loop()
{
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  currentState = digitalRead(BUTTON_PIN);
  
  if (oldxValue <= 1000 && xValue >= 1000)
  {
    lcd.scrollDisplayLeft();
    oldxValue = xValue;
    cursorX = cursorX + 1;
  }
  else if (oldxValue >= 1000 && xValue <= 1000)
  {
    oldxValue = xValue;
  }

  if (oldxValue >= 23 && xValue <= 23)
  {
    lcd.scrollDisplayRight();
    oldxValue = xValue;
    cursorX = cursorX - 1;
  }
  else if (oldxValue <= 23 && xValue >= 23)
  {
    oldxValue = xValue;
  }

  if (oldyValue <= 1000 && yValue >= 1000)
  {
    cursorY = cursorY + 1;
    oldyValue = yValue;
  }
  else if (oldyValue >= 1000 && yValue <= 1000)
  {
    oldyValue = yValue;
  }

  if (oldyValue >= 23 && yValue <= 23)
  {
    cursorY = cursorY - 1;
    oldyValue = yValue;
  }
  else if (oldyValue <= 23 && yValue >= 23)
  {
    oldyValue = yValue;
  }

  if (cursorX > 39)
    cursorX = 0;

  if (cursorX < 0)
    cursorX = 39;

  if (cursorY > 1)
    cursorY = 1;

  if (cursorY < 0)
    cursorY = 0;


  if (currentState != lastFlickerableState)
  {
    lastDebounceTime = millis();
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    if (lastSteadyState == HIGH && currentState == LOW)
    {
      if (cursorX == 0 && cursorY == 0)//Few Skittles
        {
          myServo.attach(10);
          lcd.write((byte)1);
          lcd.setCursor(0, 0);
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(500);
          for (pos = 40; pos >= 0; pos -= 5)
            {
              myServo.write(pos);
              delay(15);
            }
          lcd.write((byte)0);
          lcd.setCursor(0, 0);
          myServo.attach(9);
          delay(100);
          lcd.clear();
          lcd.print("You're welcome");
          lcd.setCursor(0, 1);
          lcd.print("Enjoy! -Evan");
          lcd.noCursor();
          delay(5000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.write((byte)0);
          lcd.setCursor(1, 0);
          lcd.print("Few Skittles");
          lcd.setCursor(0, 1);
          lcd.write((byte)0);
          lcd.setCursor(1, 1);
          lcd.print("Some Skittles");
          lcd.setCursor(16,0);
          lcd.write((byte)0);
          lcd.setCursor(17,0);
          lcd.print("More Skittles");
          lcd.setCursor(16,1);
          lcd.write((byte)0);
          lcd.setCursor(17,1);
          lcd.print("Most Skittles");
          lcd.setCursor(32, 0);
          lcd.print("Code by");
          lcd.setCursor(32, 1);
          lcd.print("Evan H");
          lcd.cursor();
          cursorX = 0;
          cursorY = 0;
        } 
      else if(cursorX == 0 && cursorY == 1)//Some Skittles
        {
          myServo.attach(10);
          lcd.write((byte)1);
          lcd.setCursor(0, 1);
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(1000);
          for (pos = 40; pos >= 0; pos -= 5)
            {
              myServo.write(pos);
              delay(15);
            }
          lcd.write((byte)0);
          lcd.setCursor(0, 1);
          myServo.attach(9);
          delay(100);
          lcd.clear();
          lcd.print("You're welcome");
          lcd.setCursor(0, 1);
          lcd.print("Enjoy! -Evan");
          lcd.noCursor();
          delay(5000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.write((byte)0);
          lcd.setCursor(1, 0);
          lcd.print("Few Skittles");
          lcd.setCursor(0, 1);
          lcd.write((byte)0);
          lcd.setCursor(1, 1);
          lcd.print("Some Skittles");
          lcd.setCursor(16,0);
          lcd.write((byte)0);
          lcd.setCursor(17,0);
          lcd.print("More Skittles");
          lcd.setCursor(16,1);
          lcd.write((byte)0);
          lcd.setCursor(17,1);
          lcd.print("Most Skittles");
          lcd.setCursor(32, 0);
          lcd.print("Code by");
          lcd.setCursor(32, 1);
          lcd.print("Evan H");
          lcd.cursor();
          cursorX = 0;
          cursorY = 0;
        }
      else if(cursorX == 16 && cursorY == 0)//More Skittles
        {
          myServo.attach(10);
          lcd.write((byte)1);
          lcd.setCursor(16, 0);
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(750);
          for (pos = 0; pos <= 35; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(750);
          for (pos = 40; pos >= 0; pos -= 5)
            {
              myServo.write(pos);
              delay(15);
            }
          lcd.write((byte)0);
          lcd.setCursor(16, 0);
          myServo.attach(9);
          delay(100);
          lcd.clear();
          lcd.print("You're welcome");
          lcd.setCursor(0, 1);
          lcd.print("Enjoy! -Evan");
          lcd.noCursor();
          delay(5000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.write((byte)0);
          lcd.setCursor(1, 0);
          lcd.print("Few Skittles");
          lcd.setCursor(0, 1);
          lcd.write((byte)0);
          lcd.setCursor(1, 1);
          lcd.print("Some Skittles");
          lcd.setCursor(16,0);
          lcd.write((byte)0);
          lcd.setCursor(17,0);
          lcd.print("More Skittles");
          lcd.setCursor(16,1);
          lcd.write((byte)0);
          lcd.setCursor(17,1);
          lcd.print("Most Skittles");
          lcd.setCursor(32, 0);
          lcd.print("Code by");
          lcd.setCursor(32, 1);
          lcd.print("Evan H");
          lcd.cursor();
          cursorX = 0;
          cursorY = 0;
        }
      else if(cursorX == 16 && cursorY == 1)//Most Skittles
        {
          myServo.attach(10);
          lcd.write((byte)1);
          lcd.setCursor(16, 1);
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(1000);
          for (pos = 0; pos <= 35; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          for (pos = 0; pos <= 40; pos += 5)
            {
              myServo.write(pos);
              delay(15);
            }
          delay(1000);
          for (pos = 40; pos >= 0; pos -= 5)
            {
              myServo.write(pos);
              delay(15);
            }
          lcd.write((byte)0);
          lcd.setCursor(16, 1);
          myServo.attach(9);
          delay(100);
          lcd.clear();
          lcd.print("You're welcome");
          lcd.setCursor(0, 1);
          lcd.print("Enjoy! -Evan");
          lcd.noCursor();
          delay(5000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.write((byte)0);
          lcd.setCursor(1, 0);
          lcd.print("Few Skittles");
          lcd.setCursor(0, 1);
          lcd.write((byte)0);
          lcd.setCursor(1, 1);
          lcd.print("Some Skittles");
          lcd.setCursor(16,0);
          lcd.write((byte)0);
          lcd.setCursor(17,0);
          lcd.print("More Skittles");
          lcd.setCursor(16,1);
          lcd.write((byte)0);
          lcd.setCursor(17,1);
          lcd.print("Most Skittles");
          lcd.setCursor(32, 0);
          lcd.print("Code by");
          lcd.setCursor(32, 1);
          lcd.print("Evan H");
          lcd.cursor();
          cursorX = 0;
          cursorY = 0;
        }
      }
    lastSteadyState = currentState;
  }

  lcd.setCursor(cursorX, cursorY);
  
}
