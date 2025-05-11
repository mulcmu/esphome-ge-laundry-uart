# esphome-ge-laundry-uart
Integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the communication port and provide remaining time and cycle done feedback to HA.

### Current Status:

- ESP32 interface circuit built on custom PCB and tested.  My dryer uses half duplex serial connection (GEA2) and washer uses full duplex (GEA3).  

- This branch starts implementation as espHome external component.  *Custom components were removed in 2025*

* [GE Appliances](https://github.com/geappliances) / [FirstBuild](https://firstbuild.com/inventions/home-assistant-adapter/) started releasing hardware and protocol information, picking up where the old GEMakers left off.  They implement GEA2 and GEA3 in Arduino cpp and Home Assistant MQTT interface.
* I bought a GE dishwasher.

### TODO:

- Make it a proper ESPhome external component.  
- Copy GE Appliances GEA2/GEA3 implementation.
- Add dishwasher support.
- Add missing cycle types / settings from ~~simbaja/gehome~~ GE Appliances
- Add a "setup" yaml & .h.  Broadcast message to see what endpoints respond and check to make sure necessary erds are present. 
- Add build/installation/configuration instructions
- Packets are currently hard coded with address for my appliances.  Make this configurable with correct checksums.
- Test on appliance with integrated wifi.  Will extra bus traffic / processor load cause problems. 

### Related projects:

- https://github.com/puddly/casserole
- https://github.com/GEMakers/green-bean
- https://github.com/doitaljosh/gea-interface-board
- https://github.com/doitaljosh/ge-appliances-re
- https://github.com/doitaljosh/geabus-documentation
- https://github.com/simbaja/gehome
- https://github.com/geappliances/home-assistant-adapter
- https://github.com/geappliances/home-assistant-examples
- https://github.com/geappliances/home-assistant-bridge



