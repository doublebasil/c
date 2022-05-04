// You should first install WiFiNINA in the Library Manager

// Looks like wifi status is 4 if it's not gonna work, and 3 if its working

#include <WiFiNINA.h>
#include <SPI.h>

void setup() {
  // Setup basic Arduino functions
  Serial.begin(9600);
  while (!Serial) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup magical Wireless functions
  char ssid[] = "FRITZ!Box 7530 NN";
  char password[] = ""; // Your wifi password
  while (true) {
    Serial.print("Attempting to connect to: ");
    for (int i = 0; i < (sizeof(ssid) / sizeof(char)); i++) {
      Serial.print(ssid[i]);
    }
    Serial.println(" ");
    WiFi.begin(ssid, password);
    if (WiFi.status() != 3) {
      Serial.print("wifi_status=");
      Serial.print(WiFi.status());
      Serial.println(" (should be 3), going to attempt to restart");
      WiFi.disconnect();
    }
    else {
      break;
    }
  }
}

void loop() {

  unsigned long unixtime = WiFi.getTime();
  if (unixtime == 0) {
    Serial.print("No response from WiFi, wifi_status=");
    Serial.println(WiFi.status());
  }
  else {
    Serial.print("wifi_status=");
    Serial.print(WiFi.status());
    Serial.print(", unix=");
    Serial.print(unixtime);
    Serial.print(", date=");
    printDate(unixtime);
  }

  delay(1000);
}

#define SECONDS_NORM_YEAR (365l * 24l * 60l * 60l)
#define SECONDS_LEAP_YEAR (366l * 24l * 60l * 60l)
#define SECONDS_PER_DAY (24l * 60l * 60l)

void printDate(unsigned long unixtime) {
  unsigned long timeRemaining = unixtime;
  // Year
  int year = 1970;
  while (true) {
    if (isLeapYear(year)) {
      if (timeRemaining > SECONDS_LEAP_YEAR) {
        year++;
        timeRemaining -= SECONDS_LEAP_YEAR;
      }
      else {
        break;
      }
    } 
    else {
      if (timeRemaining > SECONDS_NORM_YEAR) {
        year++;
        timeRemaining -= SECONDS_NORM_YEAR;
      }
      else {
        break;
      }
    }
  }
  // Months
  unsigned char daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char monthNames[] = "January,Febrary,March,April,May,June,July,August,September,November,December";
  unsigned char monthCounter = 0;
  unsigned long secondsCurrentMonth;
  while (true) {
    secondsCurrentMonth = daysPerMonth[monthCounter] * SECONDS_PER_DAY;
    if (timeRemaining > secondsCurrentMonth) {
      timeRemaining -= secondsCurrentMonth;
      monthCounter++;
    }
    else {
      break;
    }
  }
  unsigned int day = floor((float) timeRemaining / SECONDS_PER_DAY) + 1;
  timeRemaining -= (day - 1) * SECONDS_PER_DAY;
  // Now get time
  unsigned int hour = 0;
  unsigned int minute = 0;
  while (timeRemaining > 3600) {
    hour++;
    timeRemaining -= 3600;
  }
  while (timeRemaining > 60) {
    minute++;
    timeRemaining -= 60;
  }
  // Now print everything
  Serial.print(day);
  Serial.print(" ");
  Serial.print(monthCounter + 1);
  Serial.print(" ");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(timeRemaining);
  Serial.println(" ");
}

bool isLeapYear(signed int year) {
  return (year % 4 == 0);
}
