#include <Arduino.h>

elapsedMillis timeSince;
uint32_t counter = 0;

void setup()
{
  Serial.begin(115200);
  Serial8.begin(9600);
  while (not Serial) { delay(1000); }
  Serial.println("Serial to USB is ready.");
  while (not Serial8) { delay(1000); }
  Serial.println("Serial to GPU is ready.");

  timeSince = 2000;
}

void loop()
{
  if (timeSince >= 2000)
  {
    Serial8.print("from CPU: ");
    Serial8.print(counter);
    Serial8.write('\0');
    Serial.println("Serial8.print(...)");
    ++counter;
    timeSince = 0;
  }
}
