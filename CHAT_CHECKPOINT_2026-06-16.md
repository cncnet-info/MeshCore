# Chat Checkpoint (2026-06-16)

Tento soubor shrnuje stav práce z předchozího chatu a slouží jako prenos kontextu do projektu MeshCore_116_custom.

## Cil

- Vzít cisty zaklad z `repeater-v1.16.0`.
- Prenest pouze tvoje upravy:
  - synchronizace casu repeateru z advertu trusted admin nodu,
  - varianta desky ProMicro E22P,
  - drzeni casu pres reset na NRF52.

## Novy projekt

- Slozka: `C:/Users/tull/GIT_projekty/MeshCore_116_custom`
- Branch: `custom/on-clean-1.16`
- Base commit/tag:
  - `07a3ca9e` (`repeater-v1.16.0`)

## Prenesene commity

1. `685c925b` Add isolated promicro_e22p variant with NRF52 power management
2. `939601a2` Auto-sync repeater RTC from trusted admin adverts
3. `1f3e596d` Keep time accross resets for NRF52

## Overeni synchronizace casu

- Implementace je v `examples/simple_repeater/MyMesh.cpp` ve funkci `onAdvertRecv(...)`.
- Logika:
  - najde trusted klienta v ACL,
  - overi, ze je admin,
  - pokud `timestamp > curr + 2`, provede `setCurrentTime(timestamp)`.

## Poznamky k verzi

- V predchozich krocich bylo overeno, ze artifacty obsahovaly `v1.16.0` a ne `v1.15.0`.
- Pokud UI na zarizeni stale ukazuje starou verzi, byva to casto cache nebo nahrany starsi soubor.

## Doporucene build targety

- XIAO ESP32S3 + Wio SX1262 repeater:
  - `Xiao_S3_WIO_repeater`
- ProMicro E22P repeater:
  - `ProMicro_E22P_repeater`

## OTA pravidlo (ESP32 web update)

- Pro `/update` nahravat standardni `firmware.bin`.
- Nenahravat merge image (soubor s `merge` v nazvu).

## Poznamka k chatu

- Historii panelu Chat nejde mezi projekty prenest 1:1.
- Tento soubor je oficialni checkpoint pro navazani prace v novem projektu.
