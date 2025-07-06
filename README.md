
![v2](https://github.com/user-attachments/assets/f0ecc78b-20a1-45ff-a41a-00d02f6c67e2)

# esphome-ge-laundry-uart
Integrating a GE washer & dryer with Home Assistant using ESPHome.  The GE W&D have an RJ45 style communication port with a serial interface.  ESP32 hardware powered by the communication port provides remaining time and cycle done feedback to HA via ESPHome.

### Current Status:

- Version 2.0 of PCB designed and fabricated.  Uses same ESP32-C3 and pinout as FirstBuild adapter.  PCB assembly files ready for assembly at JLCPCB if you want to order your own.  About $15 per board.
- Better case design
- ESPHome implemented as an external component for better setup and support.
- Washer, dryer, and dishwasher working (at least as well as before).  Washer and dishwasher seems to respond to GEA2 formatted packets, at least for legacy ERDs.  Newer ERDs (unbalanced / rinse aid status) don't get a response.
* [GE Appliances](https://github.com/geappliances) / [FirstBuild](https://firstbuild.com/inventions/home-assistant-adapter/) started releasing hardware and protocol information, picking up where the old GEMakers left off.  They implement GEA2 and GEA3 in Arduino cpp and Home Assistant MQTT interface.


### TODO:

- Add start/stop controls
- Add magnets to v2 Case design
- Add diagnostic function to ping appliance broadcast address
- Finish v2.1 of pcb design.
- Use/copy GE Appliances GEA2/GEA3 implementation.
- Add missing cycle types / settings from ~~simbaja/gehome~~ GE Appliances
- Add build/installation/configuration instructions
- Update to use publish/subscribe instead of constant read polling
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



