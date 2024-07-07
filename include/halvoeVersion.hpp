#pragma once

#pragma message "Build timestamp: " __DATE__ " " __TIME__

namespace halvoeAngelScriptCPU
{
  constexpr const char* buildVersion = "0.0.2";
  constexpr const char* buildTimestamp = __DATE__ " " __TIME__;
}
