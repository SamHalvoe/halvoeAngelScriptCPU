#include <Arduino.h>
#include <elapsedMillis.h>

#include "SerialGFXInterface_atCPU.hpp"

halvoeGPU::atCPU::SerialGFXInterface g_gpuInterface(Serial8);
elapsedMillis interval;
uint16_t rectX = 5;

void setup()
{
  Serial.begin(115200);
  while (not Serial) { delay(1000); }
  Serial.println("Serial to USB is ready.");
  while (not g_gpuInterface.begin()) { delay(1000); }
  Serial.println("Serial to GPU is ready.");
  interval = 0;
}

void loop()
{
  if (interval >= 1000)
  {
    rectX = rectX + 5;
    if (rectX == 320 - 25) { rectX = 5; }

    interval = 0;
  }

  g_gpuInterface.sendFillScreen();
  g_gpuInterface.sendFillRect(rectX, 5, 25, 25, 255);
  g_gpuInterface.sendSwap();
}
