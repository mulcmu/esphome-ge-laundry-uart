# esphome-ge-dryer-uart
Work in progress for integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on custom PCB and tested.  My dryer uses half duplex serial connection (GEA1) and washer uses full duplex (GEA3).  

- ESPHome code is working for W&D status items and remaining cycle time.  

- 
- PCB design R0.3 posted to fix some mistakes on R0.2. 
  

![Untitled](https://user-images.githubusercontent.com/10102873/147993815-92dd5a8d-6161-4f82-92d9-c3f3c9e52dda.png)


TODO:

- Build and test PCB Rev 0.3.  Add BOM
- Post STL for enclosure
- Add #define or options of some sort to configure header for either washer or dryer.
- Packets are currently hard coded with address for my appliances.  Make this configurable with correct checksums.
- Change repository name to esphome-ge-laundry-uart
- Test with a GEA2 appliance.

Related projects:

- https://github.com/puddly/casserole
- https://github.com/GEMakers/green-bean
- https://github.com/doitaljosh/gea-interface-board
- https://github.com/doitaljosh/ge-appliances-re
- https://github.com/doitaljosh/geabus-documentation
- https://github.com/simbaja/gehome

