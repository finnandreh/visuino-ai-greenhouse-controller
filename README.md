# Visuino AI Greenhouse Controller

A modular Arduino Uno teaching project with two-zone irrigation, an empty-reservoir stop, manual requests, temperature-controlled heating and ventilation, daylight-compensating grow light, a daily lighting window, alarms and a 20 × 4 I2C display. Seven indicator commands represent the actuators. Heating responds to temperature; darkness alone never requests heat.

The corrected 93-component native v3 is simulator-qualified: **32 functional requirements and 30 boundary checks pass**, with separate unchanged-program timer-wrap evidence. An ordinary browser Build/Run produces the exact native firmware. The Lab candidate also passes its complete 971-test regression. The edited video and Instructables article are still in preparation.

## Download and build

1. Install the [project-owned DHT library ZIP](downloads/FinnGreenhouseDHTClock-0.1.0.zip) using the [installation instructions](libraries/FinnGreenhouseDHTClock/README.md).
2. Open [Greenhouse.visuino](Greenhouse.visuino) in Visuino Pro 8.0.0.169 with its matching licensed dependencies.
3. Inspect the [behavior contract](BEHAVIOR-CONTRACT.md) and [wiring guide](wiring/WIRING-GUIDE.md), then generate and compile for Arduino Uno R3.
4. The actual [generated sketch](Greenhouse/Greenhouse.ino) is included. Its header preserves the original generator filename for provenance.

Keep DHT22 DATA on D7 with its pull-up and set D7 InitialValue=true. The project-owned queued clock retains sensor requests until the existing driver is ready. No licensed vendor library or installer is distributed. The actual downloadable library ZIP was independently extracted and used to rebuild the byte-identical native firmware.

The build uses **24,238 bytes flash and 1,069 bytes static RAM**, leaving 979 bytes before runtime stack/heap use. See [build status and artifact hashes](BUILD-STATUS.json).

## Wiring

- [Editable Fritzing drawing](wiring/Greenhouse.fzz)
- [Breadboard image](wiring/Greenhouse-breadboard.png) and [vector export](wiring/Greenhouse-breadboard.svg)
- [Step-by-step connections and pin mapping](wiring/WIRING-GUIDE.md)
- [Drawing authors and license](wiring/ATTRIBUTION.md)

The LCD at 0x27 and DS3231 at 0x68 share A4/A5. Soil and light values are relative ADC measurements. The drawing is a breadboard teaching layout; no PCB design is supplied.

## What was verified

- [Final exact-program qualification](tests/NATIVE-V3-QUALIFICATION.json): native/ordinary firmware match, browser controls, LCD, timing and regression scope.
- [All 62 requirement results](tests/NATIVE-V3-RUNTIME-SUMMARY.json): individual IDs and measured evidence categories.
- [Six cold-boot sensor transactions](tests/NATIVE-V3-CADENCE.json): all five measured intervals meet 2000 ±100 ms.

The raw functional matrix retains GH32 as NOT_RUN. A separate fresh fixture verifies the unchanged program across unsigned timer wrap under the original minimum-five-second dwell contract, supplying its effective PASS. The 4999 ms scan holds the light; the first eligible 5050 ms scan switches it off. Earlier failed results remain historical evidence. [BASELINE-RESULTS.json](tests/BASELINE-RESULTS.json) belongs to the older 92-component baseline and must not be used as the current result.

These tests execute actual compiled AVR firmware with simulated devices in a private Lab candidate. Public Lab deployment compatibility is a separate check. Physical sensor accuracy, real pumps/heaters/load drivers, crop suitability and runtime stack headroom require their own verification.

## Project links

- Project repository: https://github.com/finnandreh/visuino-ai-greenhouse-controller
- Project page: https://finnandre.no/ressurser/visuino-ai-drivhus/

Final video and Instructables links will be added after review and publication. Drawing attribution does not grant a license to proprietary vendor software, trademarks, music or video. Credentials, private infrastructure records and raw private recordings are excluded.
