# Greenhouse bench wiring — draft

This is the wiring companion for the editable `Greenhouse-Wiring-DRAFT.fzz`.
The complete greenhouse candidate compiles in native Visuino; actual Lab tests are pending. The seven LEDs
represent actuator commands. No pumps, valves, heaters or mains loads are wired.

1. Place the Uno and establish the shared 5 V and GND connections shown in the
   drawing. Use the module labels rather than assuming a connector order.
2. Connect zone 1 soil SIG to A0 and zone 2 SIG to A1; both sensors share the
   supply and ground. Relative ADC values require separate dry/wet calibration;
   this artwork does not establish calibrated moisture percentages.
3. Build two separate light dividers. Each LDR connects from 5 V to its sample
   node; a 10 kohm resistor connects that node to GND. Outside uses A2 and inside
   uses A3. This topology gives a higher ADC reading as LDR resistance falls
   with brighter light. It is relative light, not a lux measurement.
4. Connect DHT22 VCC and GND, DATA to D7, and a 10 kohm pull-up from DATA to
   5 V. Leave NC disconnected. The illustrated four-pin interface is not a
   promise that every packaged DHT module uses the same physical pin order.
5. Connect both I2C devices to the shared bus: SDA to A4 and SCL to A5, with
   common supply and ground. The intended addresses are LCD 0x27 and DS3231
   0x68. Actual backpack addresses and board electrical details must be checked.
   The DS3231 Lab model is still a pending dependency.
6. Connect the mode switch D3, manual-zone buttons D4/D5 and empty-source
   switch D6 to GND when asserted. The final firmware must enable their internal
   pull-ups. Thus open/high means AUTO for D3, and closed/low means MANUAL;
   closed/low on D6 means reservoir empty.
7. For each output, connect its pin through a separate 330 ohm resistor to
   LED anode; connect LED cathode to GND. D2=pump, D8=valve 1, D9=valve 2,
   D10=fan, D11=heater, D12=grow light, D13=alarm. D13 may also illuminate
   the Uno's built-in LED. D0/D1 remain reserved for serial diagnostics.

Drawing colors: red supply, dark grey ground, green analog/SDA, purple SCL,
blue digital inputs, orange output chains. Wire crossings do not imply a
connection; the native connectors and static net report define connectivity.

Keep three checks distinct: native Fritzing opening/routing, static net
verification, and actual generated firmware execution. Only the first two have
evidence at this stage. Physical calibration and load operation are untested.
