# esphome-ge-dryer-uart
Work in progress for integrating a GE Wifi enabled dryer with Home Assistant using ESPHome.  The dryer has a RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the dryer communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on breadboard for testing.  Debugging the serial connection.

  ![dryer testing](.\dryer testing.jpg)

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

