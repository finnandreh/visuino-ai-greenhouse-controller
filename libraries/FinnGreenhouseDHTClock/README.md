# Greenhouse Clocked DHT22 for Visuino

A project-owned queued-clock adapter for the existing Visuino DHT22 driver.
It retains a clock request while the driver is busy and starts an accepted
request no sooner than 2000ms after the previous accepted request. The existing
sensor implementation performs the protocol read; no vendor decoder is copied.

## Install

Use the matching licensed Visuino/Mitov8.0.0.169 environment and Arduino Uno.
Copy this complete FinnGreenhouseDHTClock folder into the Arduino sketchbook's
libraries folder. Keep its Visuino subfolder, icon and empty visuino.library
marker. Restart/rescan Visuino and search for Greenhouse Clocked DHT22.
Back up an existing same-name installation before replacing it.

Open the supplied Greenhouse.visuino. QueuedDHT must have its external0.5Hz
clock connected. DHT22 DATA goes to D7 with the external pull-up; NC stays
unconnected. Arduino Digital[7].InitialValue must remain true so the line
starts high before sensor initialization. Keep all other configured pin values.

The toolbar type is TArduinoFinnGreenhouseClockedDHT22; the saved project type
has the FinnGreenhouse namespace prefix. Ask the native catalogue for the type
instead of guessing an unsupported namespace-qualified toolbar identifier.

The header, component declaration, icon and marker match the tested package
byte for byte; this copy updates descriptive documentation and library metadata
only. See the project BUILD-STATUS.json and test reports for the exact tested
firmware and current qualification. Compilation alone is not a runtime pass.
No physical sensor calibration or real greenhouse load operation is claimed.
