# Greenhouse demonstration behavior

These are the implementation and test requirements for the greenhouse teaching
project. Values are demonstration choices, not plant-specific recommendations.
A behavior contract is not evidence of passing execution. See BUILD-STATUS.json
and the exact-artifact reports under tests/ for the current qualification.

## Input interpretation and time

Sample analog and debounced digital inputs every 50 ms. A switch must retain
its changed raw state for at least 40 ms before acceptance; with this sampling
period acceptance is expected 40–100 ms after a stable physical edge, plus one
loop of output latency. Document measured runtime latency rather than assuming
the browser's action timestamp is the firmware input timestamp.

For the initial fixture, soil ADC 0 means dry and 1023 means wet. This is a
relative demonstration scale requiring actual Lab polarity verification.
Compare integer products before division: `100 * adc` against `threshold * 1023`.
Use at least 32-bit intermediates on Uno. Thus dry <=30% maps to ADC <=306;
wet >=55% maps to ADC >=563. Do not round the displayed percentage and feed it
back into the control comparison. ADC 0/1023 alone cannot prove a disconnected
soil sensor and must not be advertised as a disconnection detector.

Both LDR channels use the same relative 0–100 scale, brighter = larger ADC.
Inside low <=35 maps to ADC <=358; high >=45 maps to ADC >=461. Outside light
is measured/displayed independently and does not replace inside feedback.

Use unsigned elapsed subtraction for all millisecond durations. DHT22 sampling
interval is 2 s. Only successful decoded updates in temperature -40..80 C and
humidity 0..100% refresh the climate freshness timer. A failed transaction does
not refresh it. At age >=6 s climate data is stale. Start invalid; require two
consecutive valid updates to clear a climate fault. Verify native access to
decode-success/freshness; a cached numeric temperature alone is insufficient.

The RTC uses 24-hour dates in 2000–2099. Start with lighting permission false.
Require valid calendar decoding and observed civil-time advancement before
granting permission. At elapsed >=3500 ms without advancement, clock becomes
stale and permission false. The current RTC-only probe does not implement this
guard. Repeated equal dates may be accepted during one second but never refresh
the advancement timer. After failure, require two successive advancing valid
samples, each 1–2 civil seconds apart, before re-enabling permission. An explicit
valid calendar jump resets acquisition and forces OFF until reacquired. A silent
bus failure is detectable only through this freshness deadline in this graph.

## Irrigation and arbitration

Dry requests set at <=30% and clear at >=55%; retain prior request in between.
Each zone has its own request memory. Initial arbitration preference is zone 1;
after a zone starts, next preference becomes the other zone. Choose the preferred
eligible zone if both request, otherwise choose the sole eligible zone.

In AUTO, eligibility follows the dry request. In MANUAL, eligibility follows
the held, debounced zone button; both modes retain reservoir and timeout guards.
A selected valve and pump turn off when that zone becomes wet in AUTO, its
button is released in MANUAL, source becomes empty, mode changes, or run age
reaches 10000 ms. Only one valve may be ON. Pump equals the OR of the two
valves after all final interlocks. Never write pump separately from these guards.

Every ordinary completion and mode change starts a 15000 ms all-OFF rest.
Source loss also starts rest and requires both manual buttons released before
manual re-arm. Reservoir fault clears after accepted source recovery, but
watering cannot start until the rest deadline and applicable re-arm are satisfied.
AUTO may resume an outstanding dry request after these guards pass.

At run age >=10000 ms, latch TIMEOUT even if other demand persists. Timeout
blocks irrigation until MANUAL, source available, both buttons held continuously
for >=2000 ms, and outputs OFF. Clear the latch at the end of the hold but keep
watering inhibited until BOTH buttons have been released. A held reset gesture
is never interpreted as a watering request. Reset completion starts a new rest.
Mode changes require both buttons released before manual requests are accepted.

On each scan, handle empty source and faults before start arbitration. At an
exact simultaneous timeout/wet event, stop safely and retain TIMEOUT to avoid
silently masking the maximum-duration event.

## Climate and lighting

| Control | Set condition | Clear condition |
|---|---|---|
| Heater request | valid temperature <=18 C | temperature >=20 C |
| Fan request | valid temperature >=28 C | temperature <=26 C |
| Overtemperature | valid temperature >=35 C | valid temperature <=33 C |
| Inside low-light request | inside relative light <=35 | inside relative light >=45 |

Keep request memory within each band. Final heater = valid, non-overtemperature
heater request AND NOT final fan. Overtemperature forces fan ON, heater OFF
and alarm ON. Climate invalid/stale also commands heater OFF, fan ON and alarm
ON; this is a demonstration command policy, not proof of real cooling capacity.
Humidity is monitoring only. Climate faults do not bypass irrigation interlocks.

Lighting permission is valid fresh acquired clock AND civil time >=06:00:00
AND <22:00:00. Grow light follows the inside low-light request only while
permission is true. Minimum ordinary ON and OFF dwell are each 5000 ms.
Startup and forced permission loss set output OFF and restart the OFF dwell.
At 22:00:00, invalid/stale clock or acquisition reset, force OFF immediately
regardless of ON dwell. A returning permission waits the remaining OFF dwell.
Darkness never generates a heater request. Temperature never generates a light
request. Firmware must evaluate both channels independently.

Alarm is the OR of reservoir-empty, irrigation TIMEOUT, climate fault,
overtemperature and clock fault. LCD fault priority is TIMEOUT, EMPTY,
TEMP INVALID, OVER TEMP, CLOCK INVALID, then normal state. Keep independent
fault bits observable even when the display shows only the highest priority.

## Timing acceptance and evidence

The stop conditions are never relaxed by a minimum dwell. For scan-driven
deadlines, accept no early transition and no later than deadline +100 ms plus
one measured loop; record runtime speed and sample rate. For DHT/RTC failure,
measure from the last successful update/advancement, not from UI manipulation.
Poll-based simulator controls must report their actual input-application time.
If the runtime cannot produce that evidence, label timing unverified.

The native project, generated source and Lab trace must be checked against
these rules. The CSV files under tests/ define required observations; their
planning labels are separate from measured results. Historical baseline reports
refer to their own artifact and must not be attributed to a newer source file.
The display uses four padded20-character rows with2Hz refresh. This document
does not simulate output or replace executable firmware and physical tests.
