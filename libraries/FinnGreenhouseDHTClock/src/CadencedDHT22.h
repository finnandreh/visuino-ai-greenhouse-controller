// Experimental queued-clock adapter; no installed vendor file is changed.
#pragma once
#include <Mitov_DHT_Sensor.h>

namespace FinnGreenhouse {
template<class Pin, Pin &PinInstance, class... Properties>
class CadencedDHT22 : public Mitov::DHTSensor_DHT22<Pin, PinInstance, Properties...> {
  using Base = Mitov::DHTSensor_DHT22<Pin, PinInstance, Properties...>;
  uint32_t acceptedStart = 0;
  bool hasAcceptedStart = false;
  bool clockPending = false;

  void TryPendingClock() {
    if (!this->Enabled.GetValue()) {
      clockPending = false;
      return;
    }
    if (!clockPending || this->FStartReadState != 0)
      return;
    const uint32_t now = millis();
    if (hasAcceptedStart && uint32_t(now - acceptedStart) < 2000UL)
      return;
    this->FLastReadTime = now - 2000UL;
    Base::ClockInputPin_o_Receive(nullptr);
    if (this->FStartReadState == 1) {
      acceptedStart = now;
      hasAcceptedStart = true;
      clockPending = false;
    }
  }

public:
  void SystemInit() {
    Base::SystemInit();
    hasAcceptedStart = false;
    clockPending = false;
  }
  void ClockInputPin_o_Receive(void *) {
    clockPending = true;
    TryPendingClock();
  }
  void SystemLoopBegin() {
    Base::SystemLoopBegin();
    TryPendingClock();
  }
};
} // namespace FinnGreenhouse
