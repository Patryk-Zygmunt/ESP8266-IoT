#include "GreetingProvider.h";
#include <Arduino.h>;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
}

void loop() {
  GreetingProvider g;
  std::string greeting = g.getGretting();
  // Serial.print(greeting.c_str());
  Serial.write(greeting.c_str());
  delay(1000);
  // put your main code here, to run repeatedly:
}
