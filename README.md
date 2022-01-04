# esphome-ge-dryer-uart
Work in progress for integrating a GE Wifi enabled dryer with Home Assistant using ESPHome.  The dryer has a RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the dryer communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on breadboard for testing.  Debugging the serial connection.  The TXS0104E level shifting chip works okay when testing as loopback but ESP32 doesn't receive any data from the dryer.  Chip has internal 10k pull-up so no easy work around.  2N7000 level shifting circuit didn't work either.  No data from dryer.    *ESP32 inputs are 5v tolerant so RX can be hooked right to dryer 5v signal*.  SN74LVC2G07 wired into with a 4.7k resistor and N4148 diode for TX.  Working so far.

![Untitled](https://user-images.githubusercontent.com/10102873/147997039-5b29cf8d-d787-451e-ac31-3656dd7a5a63.png)

- Dryer sends these packets, about every 5 seconds.  Looks like it repeats message 3 times if no `E1` response to acknowledge. 
  `E2:BF:0B:24:A0:01:60:03:9B:51:E3`
  
  `E2:BF:0B:24:A0:01:60:03:9B:51:E3`
  
  `E2:BF:0B:24:A0:01:60:03:9B:51:E3` 
  
- `BE` is the address for the U+ connect.  Maybe `BF` above is internal wifi board?  Using `BB` for this ESPHome integration.
- Test code is working for status items and remaining cycle time.  Dryer response packets are sent 3x because code doesn't send `e1` to acknowledge.

![Untitled](https://user-images.githubusercontent.com/10102873/147993815-92dd5a8d-6161-4f82-92d9-c3f3c9e52dda.png)

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

