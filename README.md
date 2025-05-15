# esphome-ge-laundry-uart
Integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  Goal is to have ESP32 hardware powered by the communication port and provide remaining time and cycle done feedback to HA.

### Current Status:

- ESP32 interface circuit built on custom PCB and tested.  My dryer uses half duplex serial connection (GEA2) and washer uses full duplex (GEA3).  

- This branch implementation as espHome external component.  *Custom components were removed in 2025*

- Washer and dryer working (at least as well as before).  Washer seems to respond to GEA2 formatted packets, at least for legacy ERDs.  Newer ERDs (unbalanced) don't get a response.

* [GE Appliances](https://github.com/geappliances) / [FirstBuild](https://firstbuild.com/inventions/home-assistant-adapter/) started releasing hardware and protocol information, picking up where the old GEMakers left off.  They implement GEA2 and GEA3 in Arduino cpp and Home Assistant MQTT interface.
* I bought a GE dishwasher.

### TODO:

- Use/copy GE Appliances GEA2/GEA3 implementation.
- Add dishwasher support.
- Add missing cycle types / settings from ~~simbaja/gehome~~ GE Appliances
- Add build/installation/configuration instructions
- Test on appliance with integrated wifi.  Will extra bus traffic / processor load cause problems.
- Change repository name again, external component flexible for other appliance types

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



