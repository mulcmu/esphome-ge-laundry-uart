### Rev 2.0

Reworked design to be better suited for assembly.  DC/DC buck replaced with LDO.  ESP32-C3 module used to be compatibile with FirstBuild design/pinout.

All assembly files ready for JLCPCB PCBA.

![v2 Render](https://github.com/user-attachments/assets/77eab417-817f-48a1-bfa4-fbe587ed5843)


### Rev 1.0

Added 3 resistors in case GEA2 is inverted serial.  The full duplex serial line can now be configured with either pull up or pull down resistors as needed.

### Rev 0.3

Added test points, LED, Push button and two more protection diodes.  Built and tested 3 boards with both washer and dryer.  No issues.

![OnionStraws](https://user-images.githubusercontent.com/10102873/151646053-841ecb00-9c4c-4cec-b6ba-a1de453bc428.png)

### Rev 0.2

Built and tested.  D4 diode wrong way for the half duplex GEA1.  Mounted upside down for bodge fix.  R7 and R3 need removed or changed to pull down instead of pull up.

![2022-01-28 22 47 21](https://user-images.githubusercontent.com/10102873/151646299-4b15c27d-1e0b-475f-a76f-1d3a9e918ef6.jpg)

### Rev 0.1

Ran DRC, didn't see the unconnected nets tab.  Some of the grounds were not connected.  At least Rev 0.2 placed on order before Rev 0.1 shipped.
