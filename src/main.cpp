#include <Arduino.h>
#include <elapsedMillis.h>

#include "SerialGFXInterface_atCPU.hpp"

halvoeGPU::atCPU::SerialGFXInterface g_gpuInterface(Serial8);
bool g_shouldUpdate = true;
elapsedMillis interval;
uint16_t rectX = 5;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  #ifdef HALVOE_GPU_DEBUG
    Serial.begin(115200);
    while (not Serial) { delay(1000); }
    Serial.println("Serial to USB is ready.");
    Serial.println("call g_gpuInterface.begin()");
  #endif // HALVOE_GPU_DEBUG

  while (not g_gpuInterface.begin()) { digitalWrite(LED_BUILTIN, HIGH); delay(200); digitalWrite(LED_BUILTIN, LOW); }
  
  #ifdef HALVOE_GPU_DEBUG
    Serial.println("g_gpuInterface.begin() finished");
  #endif // HALVOE_GPU_DEBUG

  interval = 0;
}

void loop()
{
  if (g_gpuInterface.isGPUReady())
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
      g_gpuInterface.sendFillScreen(0);
      g_gpuInterface.sendFillRect(rectX, 5, 25, 25, 255);
      g_gpuInterface.sendSwap();

      g_shouldUpdate = false;
    }
  }
}
