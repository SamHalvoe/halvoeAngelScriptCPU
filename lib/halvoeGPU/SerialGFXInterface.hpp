#pragma once

#include <Fonts/Picopixel.h>

#ifdef ARDUINO_ARCH_RP2040
  #define HALVOE_SERIAL_TYPE SerialUART
#elif __IMXRT1062__
  #define HALVOE_SERIAL_TYPE HardwareSerialIMXRT
#else
  #error Invalid MCU!
#endif // ARDUINO_ARCH_RP2040

#define HALVOE_GPU_DEBUG
//#define HALVOE_GPU_DEBUG_ADD_STRING

namespace halvoeGPU
{
  constexpr const uint16_t g_screenWidth = 320;
  constexpr const uint16_t g_screenHeight = 240;
  constexpr const uint16_t g_colorCount = 256;

  constexpr const unsigned long g_minFrameTimeMicros = 4000;
  constexpr const unsigned long g_oneSecondInMicros = 1000000;

  constexpr const size_t g_maxParameterBufferLength = 16384;
  constexpr const size_t g_zeroTerminatorLength = 1;

  enum class SerialGFXBaud : unsigned long
  {
    Fallback = 9600,
    Min = 115200,
    Quarter = 250000,
    Half = 576000,
    Default = 1000000,
    Double = 2000000,
    Quad = 4000000,
    Max = 6000000
  };

  enum class SerialGFXCommandCode : uint16_t
  {
    invalid = 0,
    noCommand,
    swap,
    fillScreen,
    fillRect,
    drawRect,
    setFont,
    setTextSize,
    setTextColor,
    setCursor,
    print,
    println
  };


  enum class SerialGFXFont : uint8_t
  {
    Default = 0,
    Picopixel
  };

  unsigned long fromSerialGFXBaud(SerialGFXBaud in_baud)
  {
    return static_cast<unsigned long>(in_baud);
  }

  SerialGFXCommandCode toSerialGFXCommandCode(uint16_t in_value)
  {
    switch (static_cast<SerialGFXCommandCode>(in_value))
    {
      case SerialGFXCommandCode::noCommand:
      case SerialGFXCommandCode::swap:
      case SerialGFXCommandCode::fillScreen:
      case SerialGFXCommandCode::fillRect:
      case SerialGFXCommandCode::drawRect:
      case SerialGFXCommandCode::setFont:
      case SerialGFXCommandCode::setTextSize:
      case SerialGFXCommandCode::setTextColor:
      case SerialGFXCommandCode::setCursor:
      case SerialGFXCommandCode::print:
      case SerialGFXCommandCode::println:
        return static_cast<SerialGFXCommandCode>(in_value);
    }

    return SerialGFXCommandCode::invalid;
  }

  uint16_t fromSerialGFXCommandCode(SerialGFXCommandCode in_code)
  {
    return static_cast<uint16_t>(in_code);
  }

  uint8_t fromSerialGFXFont(SerialGFXFont in_font)
  {
    return static_cast<uint8_t>(in_font);
  }

  bool getFontPointer(SerialGFXFont in_font, const GFXfont* out_pointer)
  {
    switch (in_font)
    {
      case SerialGFXFont::Default:   out_pointer = nullptr; break;
      case SerialGFXFont::Picopixel: out_pointer = &Picopixel; break;

      default: return false;
    }

    return true;
  }
}
