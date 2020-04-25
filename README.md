# EspressIO
EspressIO is an Arduino-based Espresso Machine Firmware Project.\
The aim is to provide firmware for the creation of very simple custom built Espresso Machines
for makers and hobbyists.
## Implementation Details
The cost to implement the machine will be highly dependent on your choice of implementation;
for example, retrofitting an old Espresso Machine would be relatively inexpensive,
while building from scratch would be expensive, time consuming and require a workshop.\
Since there are a wide variety of options here, the scope of this repository is limited to the core Logic & Control System, while the peripherals will be mostly abstracted.
## Bill of Materials
* An appropriate Arduino board
* A Boiler or Thermoblock controlled by a relay
* A Thermistor to regulate the boiler temperature
  * This can be omitted if the boiler has a built-in thermostat
* A water pump controlled by a relay
* An [SP3T](https://en.wikipedia.org/wiki/Switch) Switch to control 'STANDBY', 'DIFFUSING' and 'POURING' states
  * Shorting contact configuration is preferred, but not required
  * It is recommended that the "pump on" position is non-latching, to avoid... disasters
* An [SPST](https://en.wikipedia.org/wiki/Switch) Power Switch
