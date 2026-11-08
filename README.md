# Visuino AI Greenhouse Controller

**Work in progress — measured baseline: 57 PASS, 4 FAIL, 1 NOT_RUN. Source corrections are still being tested.**

A modular Arduino Uno teaching project: two-zone irrigation, source-empty protection, manual/automatic operation, independent temperature and grow-light control, DS3231 clock guard, combined alarm and20x4 I2C display. Bench LEDs represent commands.

## Current verification

This candidate is the complete 92-component project rebuilt from empty during recording. It compiles successfully with Visuino8.0.0.169 for Uno:23808bytes flash and1059bytes staticRAM, leaving989bytes for the runtime stack and heap. Source SHA256:36a0b0d90f6690281db4cb6bf9358aa3a363727904ae47cf977fbdeea78cda79. Loadable HEX SHA256:56fd2e2d5d574f71259e4ce30fcdc193be943e82a166b27d5bd6a24cad518378. This is a different build from the earlier reference candidate; it has not yet passed whole-program Lab execution.

The exact baseline has now been compiled through the Lab toolchain and executed in a private simulator candidate. Its ordinary-build HEX matches the native build byte for byte. All 32 functional and 30 boundary rows were classified: **57 PASS, 4 FAIL, 1 NOT_RUN**. The [measured baseline results](tests/BASELINE-RESULTS.json) contain row-specific UART, GPIO, ADC, I2C, LCD and timing evidence. The CSV files remain the test definitions; their original planning status is not the measured result.

Known baseline defects:

- Fan and heater commands briefly overlap during a transition: 351 simulated CPU cycles, about 21.94 microseconds. This fails GH19 and GH31.
- Fresh DHT transactions are about 4 seconds apart rather than the required 2 seconds. This fails GH29 and the climate-recovery boundary case.
- GH32 rollover remains NOT_RUN for this baseline because a supported near-rollover clock fixture was not available in that run.

A separately recorded output guard is being retested. A separate DHT scheduling prototype has compiled but has not run in the Lab. Their results are not attributed to the source files currently published here. The baseline is not a completed controller release. RTC/LCD support was exercised in this private candidate; that does not establish availability in a public Lab service. Runtime stack headroom and physical sensor/load operation are not established. The final greenhouse video and public Instructables article are not yet available. The [homepage project page](https://finnandre.no/ressurser/visuino-ai-drivhus/) remains a work-in-progress overview.

## Files and tools

Open Greenhouse.visuino in the matching installed Visuino version. The generated Arduino sketch is Greenhouse/Greenhouse.ino. It requires the matching vendor-supplied Visuino/Mitov and OpenWire dependencies installed under their own licenses; no vendor headers, libraries or installers are bundled. The .ino header retains the original generator source filename for provenance.

![Labeled greenhouse connection guide](wiring/Greenhouse-breadboard.png)

Open wiring/Greenhouse.fzz in Fritzing. Native Routing completed and static connectivity checks cover27nets/29parts/216wiresegments. Those checks establish drawing connectivity, not physical operation. Inspect actual module labels before adapting the illustrative DHT/LCD interfaces.

## Wiring

D2pump;D3mode(HIGH=AUTO);D4/D5manual requests(activeLOW);D6empty(activeLOW);D7DHT22data;D8/D9valves;D10fan;D11heater;D12growlight;D13alarm. D3..D6 use internal pull-ups. A0/A1soil,A2outside light,A3inside light,A4SDA/A5SCL. LCD0x27/RTC0x68 share I2C. D0/D1UART115200. Full steps are in wiring/WIRING-GUIDE.md.

## Behavior and tests

See BEHAVIOR-CONTRACT.md for exact thresholds, run/rest/reset guards, climate validity and clock/light permissions. Heating follows temperature independently of darkness. The test CSVs define required actual-firmware observations; a successful compile is not a substitute. ADC percentages are relative teaching scales, not calibrated moisture/lux. No physical pump/heater/load-driving hardware is demonstrated.

## Attribution and distribution

Drawing artwork and custom interfaces: see wiring/ATTRIBUTION.md for existing CC BY-SA3.0 terms and original part authors. This does not license proprietary vendor software or trademarks. No additional software license is asserted by this candidate package. Internal infrastructure documents, private libraries, credentials, chat history and raw recordings are excluded.
