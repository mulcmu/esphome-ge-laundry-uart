# esphome-ge-laundry-uart
Work in progress for integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the communication port and provide remaining time and cycle done feedback to HA.

Current Status:

- ESP32 interface circuit built on custom PCB and tested.  My dryer uses half duplex serial connection (GEA1) and washer uses full duplex (GEA3).  

- ESPHome code is working for W&D status items and remaining cycle time.  

- Built one PCB  R0.3 and tested the GEA1. 
  

![Untitled](https://user-images.githubusercontent.com/10102873/147993815-92dd5a8d-6161-4f82-92d9-c3f3c9e52dda.png)


TODO:

- Build more PCB R0.3.  Test GEA3.
- Add ESPHome function for LED and button added in R0.3.
- Post STL for enclosure.  Update Lid for LED & button holes
- Add #define or options of some sort to configure header for either washer or dryer.
- Add missing cycle types / settings from simbaja/gehome
- Add a "setup" yaml & .h.  Broadcast message to see what endpoints respond and check to make sure necessary erds are present. 
- Add build/installation/configuration instructions
- Packets are currently hard coded with address for my appliances.  Make this configurable with correct checksums.
- Test with a GEA2 appliance.
- Test on appliance with integrated wifi.  Will extra bus traffic / processor load cause problems. 
- Add accelerometer to PCB.  Monitor appliance health by looking for changes in vibrations over time.

Related projects:

- https://github.com/puddly/casserole
- https://github.com/GEMakers/green-bean
- https://github.com/doitaljosh/gea-interface-board
- https://github.com/doitaljosh/ge-appliances-re
- https://github.com/doitaljosh/geabus-documentation
- https://github.com/simbaja/gehome

