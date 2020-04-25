# EspressIO
EspressIO is an Arduino-based Espresso Machine Firmware Project.\
The aim is to create a user-friendly, professional grade custom Espresso Machine.
## Implementation Details
The cost to implement the machine will be highly dependent on your choice of implementation;
for example, retrofitting an old Espresso Machine would be relatively inexpensive,
while building from scratch would be expensive, time consuming and require a workshop.\
For this reason, the scope of this repository is limited to the core Logic & Control System,
while the peripherals will be mostly abstracted.
## Bill of Materials
* An appropriate Arduino board
* Scales
  * This can be implemented using a load cell and amplifier circuit
  * Consideration should be taken that this should be waterproof
* A Boiler or Thermoblock
* A Thermistor to regulate the boiler
  * This can be replaced with a Thermostat if you would rather do this in hardware
* A water pump
* A [SP3T Switch](https://en.wikipedia.org/wiki/Switch) to control 'standby', 'diffuse' and 'pump' states
  * Shorting contact configuration is preferred
    * Otherwise, an RC Network can remedy the switch being caught in the 'off' state between 'diffuse' and 'pump'
  * It is recommended that the "pump on" position is non-latching, to avoid... disasters
* A [SPST](https://en.wikipedia.org/wiki/Switch) Power Switch
* An appropriate fuse
