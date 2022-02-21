### Rev 0.3

Added test points, LED, Push button and two more protection diodes.  1st board built and tested with dryer.

![OnionStraws](https://user-images.githubusercontent.com/10102873/151646053-841ecb00-9c4c-4cec-b6ba-a1de453bc428.png)

### Rev 0.2

Built and tested.  D4 diode wrong way for the half duplex GEA1.  Mounted upside down for bodge fix.  R7 and R3 need removed or changed to pull down instead of pull up.

![2022-01-28 22 47 21](https://user-images.githubusercontent.com/10102873/151646299-4b15c27d-1e0b-475f-a76f-1d3a9e918ef6.jpg)

### Rev 0.1

Ran DRC, didn't see the unconnected nets tab.  Some of the grounds were not connected.  At least Rev 0.2 placed on order before Rev 0.1 shipped.

### Bill of Material

| Ref                               | Qnty | Value | Description                                                  | Vendor                                                       |
| --------------------------------- | ---- | ----- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| C1, C2, C3, C8, C9, C11,          | 6    | 100nF | 0805 Ceramic Capacitor                                       | Generic                                                      |
| C4, C7,                           | 2    | 1uF   | 0805 Ceramic Capacitor                                       | Generic                                                      |
| C5, C6, C10,                      | 3    | 10uF  | 0805 Ceramic Capacitor                                       | Generic                                                      |
| D1, D2, D3, D4,                   | 4    | -     | BAV99 High-speed switching diodes,  SOT-23                   | Mouser<br />[757-BAV99LM](https://www.mouser.com/ProductDetail/757-BAV99LM) |
| D5,                               | 1    | -     | 5.1V Zener diode SOD-123                                     | Mouser<br />[771-PDZ5.1BGWJ](https://www.mouser.com/ProductDetail/771-PDZ5.1BGWJ) |
| D6, Optional                      | 1    | -     | 5mm Light emitting diode                                     | Generic                                                      |
| D7,                               | 1    | -     | Bidirectional  TVS diode D_SMA                               | Mouser<br />[603-SMAJ20CA/TR13](https://www.mouser.com/ProductDetail/603-SMAJ20CA-TR13) |
| F1,                               | 1    | -     | Resettable fuse, polymeric positive  temperature coefficient 1210 | Mouser<br />[652-MF-USMF020-2](https://www.mouser.com/ProductDetail/652-MF-USMF020-2) |
| J1,                               | 1    | -     | 5V SMPS BUCK Remove Pot and solder jumper                    | Amazon X002R5CJAB                                            |
| J2,                               | 1    | -     | RJ connector, 8P8C Generic                                   | Amazon<br />X001RVBL37                                       |
| Q1, Q2,                           | 2    |       | Si2309CDS P-MOSFET transistor,  gate/source/drain SOT-23     | Mouser<br />[781-SI2309CDS-E3](https://www.mouser.com/ProductDetail/781-SI2309CDS-E3) |
| R1,                               | 1    | DNP   | Resistor 0805                                                | Generic                                                      |
| R2,                               | 1    | 1M    | Resistor 0805                                                | Generic                                                      |
| R3, R17,                          | 2    | 270k  | Resistor 0805                                                | Generic                                                      |
| R4, R11, R12, R14, R15, R16, R18, | 7    | 1K    | Resistor 0805                                                | Generic                                                      |
| R5,                               | 1    | 47k   | Resistor 0805                                                | Generic                                                      |
| R6, R7, R8, R9, R10, R13,         | 6    | 10K   | Resistor 0805                                                | Generic                                                      |
| R19,                              | 1    | 220   | Resistor 0805                                                | Generic                                                      |
| SW1,  Optional                    | 1    | -     | Push button switch 6mmx6mm                                   | Generic                                                      |
| U1, U2                            | 2    | -     | 74LVC2G07 Dual Buffer SOT-23-6                               | Mouser<br />[621-74LVC2G07W6-7](https://www.mouser.com/ProductDetail/621-74LVC2G07W6-7) |
| U3,                               | 1    | -     | 38 pin ESP32 [Devboard](https://smile.amazon.com/KeeYees-Development-Bluetooth-Microcontroller-ESP-WROOM-32/dp/B07QCP2451/ref=sr_1_4?crid=7RLJMKQ7J1G4&keywords=esp32+38+pin&qid=1645407308&sprefix=esp32+38pin%2Caps%2C394&sr=8-4) or similar 19 pins x 0.9" apart Optional Female Pin Headers | Amazon<br />‎B07QCP2451                                       |
| U4,                               | 1    | -     | APX803L Voltage Supervisor SOT-23 5V 450ms reset             | Mouser<br />[621-APX803L40-50SA-7](https://www.mouser.com/ProductDetail/621-APX803L40-50SA-7) |
