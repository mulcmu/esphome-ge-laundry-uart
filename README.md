
![v2](https://github.com/user-attachments/assets/f0ecc78b-20a1-45ff-a41a-00d02f6c67e2)

# esphome-ge-laundry-uart
The project started out as integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  ESP32 hardware powered by the communication port provides remaining time and cycle done feedback to HA via ESPHome.  Initial software was an custom component, which was then migrated to an external component.  Initially lots of research into the GEA2 and GEA3 implementation with a U+ Connect module.  [GE Appliances](https://github.com/geappliances) / [FirstBuild](https://firstbuild.com/inventions/home-assistant-adapter/) started releasing hardware and protocol information, picking up where the old GEMakers left off.  They implement GEA2 and GEA3 in Arduino cpp and Home Assistant MQTT interface.  Modern and flexible ESPhome external component is now located here: https://github.com/mguaylam/esphome-gea.   Legacy code is available in a branch if needed.

### Current Status:

- Version 2.0 of PCB designed and fabricated.  Uses same ESP32-C3 and pinout as FirstBuild adapter.  PCB assembly files ready for assembly at JLCPCB if you want to order your own.  About $15 per board.
  Current version 2.0 and 2.1 PCB have error on silk screen RX and TX pins are mismarked.  Also the U1 reset IC is problematic and causes ESP boot loops.
- Better 3d printed case design.
- Recommend using this ESPhome custom component.  https://github.com/mguaylam/esphome-gea.  Baseline yaml are provided for the version 2.x PCBs here for reference.

### TODO:

- PCB Updates, add USB hardware to avoid serial programming.  Remove U1.  Do a proper DC/DC regulator for the 5v supply.  Fix silk screen.
- See if the GEA2 subscribe/publish logic can be worked out for quicker response.

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
- https://github.com/mguaylam/esphome-gea



