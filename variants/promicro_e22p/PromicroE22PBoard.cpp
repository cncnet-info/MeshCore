#include <Arduino.h>
#include <Wire.h>

#include "PromicroE22PBoard.h"

#ifdef NRF52_POWER_MANAGEMENT
// Static configuration for power management.
const PowerMgtConfig power_config = {
  .lpcomp_ain_channel = PWRMGT_LPCOMP_AIN,
  .lpcomp_refsel = PWRMGT_LPCOMP_REFSEL,
  .voltage_bootlock = PWRMGT_VOLTAGE_BOOTLOCK
};

void PromicroE22PBoard::initiateShutdown(uint8_t reason) {
  bool enable_lpcomp = (reason == SHUTDOWN_REASON_LOW_VOLTAGE ||
                        reason == SHUTDOWN_REASON_BOOT_PROTECT);
  if (enable_lpcomp) {
    configureVoltageWake(power_config.lpcomp_ain_channel, power_config.lpcomp_refsel);
  }
  enterSystemOff(reason);
}
#endif

void PromicroE22PBoard::begin() {
  NRF52Board::begin();
  btn_prev_state = HIGH;

  pinMode(PIN_VBAT_READ, INPUT);

  #ifdef BUTTON_PIN
    pinMode(BUTTON_PIN, INPUT_PULLUP);
  #endif

  #if defined(PIN_BOARD_SDA) && defined(PIN_BOARD_SCL)
    Wire.setPins(PIN_BOARD_SDA, PIN_BOARD_SCL);
  #endif

  Wire.begin();

  pinMode(SX126X_POWER_EN, OUTPUT);
  digitalWrite(SX126X_POWER_EN, HIGH);
  delay(10); // give sx1262 some time to power up

#ifdef NRF52_POWER_MANAGEMENT
  // Boot voltage protection check (may not return if voltage too low).
  checkBootVoltage(&power_config);
#endif
}
