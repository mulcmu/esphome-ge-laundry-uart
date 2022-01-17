# esphome-ge-dryer-uart
Work in progress for integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on breadboard for testing.  My dryer uses half duplex serial connection (GEA1) and washer uses full duplex (GEA3).  Schematic for support hardware in the PCB folder.

- Test code is working for W&D status items and remaining cycle time.  Dryer response packets are sent 3x because code doesn't send `e1` to acknowledge packets.
  

![Untitled](https://user-images.githubusercontent.com/10102873/147993815-92dd5a8d-6161-4f82-92d9-c3f3c9e52dda.png)

TODO:

- Design PCB for the interface hardware.
- Test dryer sending acknowledge response to packets
- Add #define to configure header for either washer or dryer.
- Test with a GEA2 appliance.

Related projects:

- https://github.com/puddly/casserole
- https://github.com/GEMakers/green-bean
- https://github.com/doitaljosh/gea-interface-board
- https://github.com/doitaljosh/ge-appliances-re
- https://github.com/doitaljosh/geabus-documentation

