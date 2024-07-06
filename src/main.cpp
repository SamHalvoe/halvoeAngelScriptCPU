#include <Arduino.h>
#include <elapsedMillis.h>

#include "SerialGFXInterface_atCPU.hpp"

halvoeGPU::atCPU::SerialGFXInterface g_gpuInterface(Serial8);
bool g_shouldUpdate = true;
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
  if (interval >= 10)
  {
    rectX = rectX + 1;
    if (rectX == 320 - 25) { rectX = 5; }
    g_shouldUpdate = true;
    interval = 0;
  }

  if (g_shouldUpdate)
  {
    g_gpuInterface.sendFillScreen();
    g_gpuInterface.sendFillRect(rectX, 5, 25, 25, 255);
    g_gpuInterface.sendSwap();

    g_shouldUpdate = false;
  }
}
