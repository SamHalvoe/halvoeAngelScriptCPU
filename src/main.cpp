#include <Arduino.h>
#include <elapsedMillis.h>

#include "SerialGFXInterface_atCPU.hpp"

halvoeGPU::atCPU::SerialGFXInterface g_gpuInterface(Serial8);
const unsigned long g_screenUpdateInterval = 32000;
elapsedMicros timeSinceScreenUpdate;

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
}

void loop()
{
  if (g_gpuInterface.isGPUReady())
  {
    if (timeSinceScreenUpdate >= g_screenUpdateInterval)
    {
      g_gpuInterface.sendFillScreen(0);
      g_gpuInterface.sendSetTextColor(255);
      for (uint16_t y = 35; y < 235; y = y + 10)
      {
        g_gpuInterface.sendSetCursor(5, y);
        g_gpuInterface.sendPrint("Lorem ipsum dolor sit amet, consetetur est halvoe.");
      }
      g_gpuInterface.sendSwap();

      timeSinceScreenUpdate = 0;
    }
  }
}
