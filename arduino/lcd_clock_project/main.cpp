#include <Arduino.h>

/*  press both button to get settings
 *  in settings, left = change value, right = change selected digit
 *  hold right to exit settings
 */

#include <LiquidCrystal.h>

// LCD to Arduino Pins
#define RS 7
#define E 6
#define DB4 5
#define DB5 4
#define DB6 3
#define DB7 2
// Ground LED-
// Ground V0
// Ground VSS
// Ground R/W
// 5V VDD
// 5V LED+ through 220 Ohm resistor (these were blue in the starter pack)
LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

// Button pin numbers
#define leftButtonPin 12
#define rightButtonPin 11

// to reset the clock every 24 hours
#define msPerDay (24l * 60l * 60l * 1000l)

// button timings
#define longPressLength 1000


// To be printed
byte hours;
byte minutes;
byte seconds;
// To remember the time displayed on the clock
unsigned long clockTime;
// To measure time advancement from the Arduinos clock
unsigned long currentMillis;
unsigned long previousMillis;

/* Classes
 *
 */

class button {
  public:
    // functions
    button(byte pinNumber);                   // constructor
    bool isPressed();                         // returns true if the button is pressed
    bool shortPress();                        // returns true if the button just finished a short press
    bool longPress();                         // returns true if the button is currently long pressed, will need to wait for button release
    void waitForRelease();                    // waits for button to be released before continuing
    void refresh();                           // update the button timings and variables

    // variables
    byte pinNumber;                           // arduino digital pin number
    bool pressHistory[2];                     // bool, [0] is recent [1] is previous refresh
    unsigned long previousMillis = millis();  // value of millis() at last refresh
    unsigned long pressTime;                  // the time in ms that the button has been pressed for

    
    
};
button::button(byte pinNumber) {
  this -> pinNumber = pinNumber;  // set pinNumber
}
bool button::isPressed() {
  // return button digitalRead value
  return pressHistory[0];
}
bool button::shortPress() {
  // if the button was just released and the press time was less than a long press return true
  return ( (pressTime < longPressLength) && (pressHistory[0] == 0) && (pressHistory[1] == 1) );
}
bool button::longPress() {
  // if the button is currently pressed has been pressed longer than current press time
  return ( (pressHistory[0] == 1) && (pressTime > longPressLength) );
}
void button::waitForRelease() {
  // loop until button is released
  while (pressHistory[0] == 1) {
    // update the button again
    this -> refresh();
  }
}
void button::refresh() {
  // update the previous value
  pressHistory[1] = pressHistory[0];
  // take reading from input pin
  bool pinReading = digitalRead(pinNumber);
  // update recent value in pressHistory array
  pressHistory[0] = pinReading;
  // if this is the second refresh where the button is not pressed, then reset pressTime if necessary
  if ((pressHistory[0] == 0) && (pressHistory[1] == 0) ) {
    // if pressTime hasn't been reset, reset it now
    if (pressTime != 0) {
      pressTime = 0;
    }
    // previous millis is current millis
    previousMillis = millis();
  }
  // else if the button is currently pressed, increase pressTime
  else if (pinReading) {
    // remember the current value of millis as millis is used in multiple lines
    unsigned long currentMillis = millis();
    // increase pressTime
    pressTime += (currentMillis - previousMillis);
    // update previousMillis
    previousMillis = currentMillis;
  }
}

/* Object creation
 *
 */

button leftButton(leftButtonPin);
button rightButton(rightButtonPin);

/* Functions
 *  
 */

void millisToTime(unsigned long currentMillis, byte* hoursPointer, byte* minutesPointer, byte* secondsPointer) {
  // definitions
  #define msPerHour (60l * 60l * 1000l)
  #define msPerMinute (60l * 1000l)
  #define msPerSecond (1000l)
  // the same counter will be used for minutes, hours and seconds
  int counter = 0;
  // find the number of hours in currentMillis
  while (currentMillis > msPerHour) {
    currentMillis -= msPerHour;
    counter++;
  }
  // set the hours variable
  *hoursPointer = counter;
  // reset counter
  counter = 0;
  // find the number of minutes remaining in currentMillis
  while (currentMillis > msPerMinute) {
    currentMillis -= msPerMinute;
    counter++;
  }
  // set the minutes variable
  *minutesPointer = counter;
  // reset the counter
  counter = 0;
  // find the number of seconds remaining in currentMillis
  while (currentMillis > msPerSecond) {
    currentMillis -= msPerSecond;
    counter++;
  }
  // set the seconds variable
  *secondsPointer = counter;
  
}

void printTime(byte* hoursPointer, byte* minutesPointer, byte* secondsPointer) {
  // set the cursor to the start
  lcd.setCursor(0, 0);
  // if the hours is less than 10 a 0 will be added before the number
  if (*hoursPointer < 10) {
    lcd.print("0");
  }
  // then print the number of hours
  lcd.print(*hoursPointer);
  // print a : to seperate
  lcd.print(":");
  // repeat for minutes and seconds
  // minutes
  if (*minutesPointer < 10) {
    lcd.print("0");
  }
  lcd.print(*minutesPointer);
  lcd.print(":");
  // seconds
  if (*secondsPointer < 10) {
    lcd.print("0");
  }
  lcd.print(*secondsPointer);
}

void changeTime() {
  /* right button moves digit, left button changes the selected digit
   * 01:23:45 digitSelect
   */
  // temporary variable, e.g. if hours = 21 then temp = 1
  unsigned int temp;
  // tell the user their action has been acknowledged
  lcd.setCursor(0, 0);
  lcd.print("Time settings   ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  // wait until no button are being pressed
  while ( (leftButton.isPressed()) || (rightButton.isPressed()) ) {
    leftButton.refresh();
    rightButton.refresh();
  }
  // clear the display
  lcd.clear();
  // loop until user confirms the time they've set
  byte digitSelect = 0; // 0 = 10 hours, 1 = hour, 2 = 10 minutes etc
  while (true) {
    // convert time in milliseconds into readable time
    millisToTime(clockTime, &hours, &minutes, &seconds);
    // print the time
    printTime(&hours, &minutes, &seconds);
    // show which button is currently being pressed, first set the cursor to the start of the line
    lcd.setCursor(0, 1);
    // then print a character where needed
    switch (digitSelect) {
      case 0:
        lcd.print("|               ");
        break;
      case 1:
        lcd.print(" |              ");
        break;
      case 2:
        lcd.print("   |            ");
        break;
      case 3:
        lcd.print("    |           ");
        break;
      case 4:
        lcd.print("      |         ");
        break;
      case 5:
        lcd.print("       |        ");
        break;
    }
    // now print to where the cursor was set
    lcd.print("|");
    
    // check buttons

    // refresh buttons
    leftButton.refresh();
    rightButton.refresh();

    // if the right button is short pressed
    if (rightButton.shortPress()) {
      // move the selected digit accress
      digitSelect++;
      // if the end of the line was reached then go back to the start
      if (digitSelect > 5) {
        digitSelect = 0;
      }
    }
    // else if the left button is pressed then advance the selected digit
    else if (leftButton.shortPress()) {
      // act based on the selected digit
      switch (digitSelect) {
        case 0: // 10s of hours selected
          // if you're currenly at twenty-something hours
          if (hours >= 20) {
            // then you need to decrease the time by 20 hours
            clockTime -= (20l * 60l * 60l * 1000l);
          }
          else {
            // otherwise, if the units are >= 4 then we can't have 20 hours
            temp = hours;
            while (temp >= 10) temp -= 10;  // temp is now equal to units
            // if avoid setting 25 hours etc
            if ( (temp >= 4) && (hours >= 10) ) {
              // reset to avoid having 2X hours
              clockTime -= (10l * 60l * 60l * 1000l);
            }
            // otherwise increase time by 10 hours
            else clockTime += (10l * 60l * 60l * 1000l);
          }
          // break this switch case
          break;
        case 1: // hours selected
          // if its at twenty something hours then it goes to 0 after 3
          if (hours == 23) {
            clockTime -= (3l * 60l * 60l * 1000l);
          }
          // else find the units of hours, e.g. if hours = 19 then set temp = 9
          else {
            temp = hours;
            while (temp >= 10) {
              temp -= 10;
            }
            // if its at twenty something hours then don't go above 24 hours
            if (hours >= 20) {
              // if temp = 3 then subtract 3 hours
              if (temp == 3) {
                clockTime -= (3l * 60l * 60l * 1000l);
              }
              // otherwise add one hour
              else {
                clockTime += (60l * 60l * 1000l);
              }
            }
            else {
              // if temp = 9 then subtract 9 hours
              if (temp == 9) {
                clockTime -= (9l * 60l * 60l * 1000l);
              }
              // otherwise add one hour
              else {
                clockTime += (60l * 60l * 1000l);
              }
            }
          }
          // break case 1
          break;
        case 2: // 10s of minutes
          // if minutes is at fifty something then subtract 50 minutes
          if (minutes >= 50) {
            clockTime -= (50l * 60l * 1000l);
          }
          // otherwise add 10 minutes
          else {
            clockTime += (10l * 60l * 1000l);
          }
          // now break case 2
          break;
        case 3: // minutes
          // if minutes is 34, set temp to 4
          temp = minutes;
          while (temp >= 10) {
            temp -= 10;
          }
          // if temp is 9 then subtract 9 minutes
          if (temp == 9) {
            clockTime -= (9l * 60l * 1000l);
          }
          // otherwise add a minute
          else {
            clockTime += (60l * 1000l);
          }
          // break case 3
          break;
        case 4: // 10s of seconds
          // if seconds is at fifty something then subtract 50 seconds
          if (seconds >= 50) {
            clockTime -= (50l * 1000l);
          }
          // otherwise add 10 seconds
          else {
            clockTime += (10l * 1000l);
          }
          // now break case 4
          break;
        case 5: // seconds
          // if seconds is 34, set temp to 4
          temp = seconds;
          while (temp >= 10) {
            temp -= 10;
          }
          // if temp is 9 then subtract 9 seconds
          if (temp == 9) {
            clockTime -= (9l * 1000l);
          }
          // otherwise add a second
          else {
            clockTime += (1000l);
          }
          // break case 5
          break;
      }
    }
    // else if the left button is long pressed, exit the menu
    else if (rightButton.longPress()) {
      Serial.println("long pressed right button");
      Serial.println(rightButton.pressTime);
      break;
    }
  }
  // tell user they are exiting time settings
  lcd.setCursor(0, 0);
  lcd.print("Exiting settings");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  // wait for user to release both buttons
  while (leftButton.isPressed() || rightButton.isPressed()) {
    leftButton.refresh();
    rightButton.refresh();
  }
  // clear the screen
  lcd.clear();
  // change time variables to prevent time changing after user has set time
  currentMillis = millis();
  previousMillis = currentMillis;
}

/* Main program
 *
 */

void setup() {
  // Start display
  lcd.begin(16, 2);

  // Allow button inputs
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

  // debugging :/
  Serial.begin(9600);

}

void loop() {

  // TEST
  while (false) {
    if (leftButton.shortPress()) {
      Serial.println("left button short press");
    }
    if (leftButton.longPress()) {
      Serial.println("left button long press");
    }
    if (rightButton.shortPress()) {
      Serial.println("right button short press");
    }
    if (rightButton.longPress()) {
      Serial.println("right button long press");
    }
  }


  // recond the current time for this cycle in milliseconds
  currentMillis = millis();
  // add the change in time to the clock
  clockTime += currentMillis - previousMillis;
  // reset if clock is over 24 hours
  if (clockTime >= msPerDay) {
    clockTime -= msPerDay;
  }
  
  // convert clockTime from milliseconds into 24 hours time
  millisToTime(clockTime, &hours, &minutes, &seconds);
  // use a function to print the time to the lcd
  printTime(&hours, &minutes, &seconds);
  // change previousMillis
  previousMillis = currentMillis;
  // update the buttons 
  leftButton.refresh();
  rightButton.refresh();
  // check if the user is pressing both buttons (to allow them to change the time)
  if (leftButton.isPressed() && rightButton.isPressed()) {
    changeTime();
  }
}