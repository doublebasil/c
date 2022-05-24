#include "ext.hpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Apple obj;
  
  Serial.println(obj.foo());
}

void loop() {
  // put your main code here, to run repeatedly:

}
