# esphome-ge-dryer-uart
Work in progress for integrating a GE Wifi enabled dryer with Home Assistant using ESPHome.  The dryer has a RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the dryer communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on breadboard for testing.  Debugging the serial connection.  The TXS0104E level shifting chip works okay when testing as loopback but ESP32 doesn't receive any data from the dryer.  Chip has internal 10k pull-up so no easy work around.  2N7000 level shifting circuit didn't work either.  No data from dryer.
- Dryer sends these packets: `E2:BF:0B:24:A0:01:60:03:9B:51:E3:E2:BF:0B:24:A0:01:60:03:9B:51:E3:E2:BF:0B:24:A0:01:60:03:9B:51:E3` about once a second.   *ESP32 inputs are 5v tolerant so RX can be hooked right to dryer 5v signal*.




TODO:

- Design PCB for the interface hardware.
- All the rest of the software.
- Add support for washer as well.

Related projects:

- https://github.com/puddly/casserole
- https://github.com/GEMakers/green-bean
- https://github.com/doitaljosh/gea-interface-board
- https://github.com/doitaljosh/ge-appliances-re
- https://github.com/doitaljosh/geabus-documentation

