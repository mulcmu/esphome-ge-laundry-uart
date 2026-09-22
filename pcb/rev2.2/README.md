# PCB Rev 2.2 manufacturing candidate

This directory contains the matched files needed to quote a small revision 2.2 prototype batch. Revision 2.2 is not a proven hardware release until physical boards pass bring-up testing.

Start with the [KiCad project](design/OnionStraws.kicad_pro). Use the shared [PCB ordering guide](../ORDERING.md) with the three matched Rev 2.2 manufacturing files; do not substitute files from an older revision.

## What changed

- `U1` is an optional voltage-monitor chip intended to reset the ESP32 when its supply is too low. It caused repeated boot loops on existing Rev 2 boards, so Rev 2.2 leaves it uninstalled. Its small footprint remains on the board for rework, but the factory BOM and placement data exclude it. R3 still keeps the ESP32 enabled. Neither board button is wired as a reset button; reset requires a power cycle or an external reset connection.
- The rear silkscreen identifies the board as revision 2.2.
- The appliance-facing connector labels now use the adapter/ESP perspective:
  - pin 5, `Full TX`: adapter/ESP TX to appliance RX;
  - pin 4, `Full RX`: appliance TX to adapter/ESP RX.
- `Q1` is one of two identical power-control transistors. Its supplier catalog field was blank, while `Q2` already identified the correct part. Rev 2.2 gives both the same LCSC catalog number so JLCPCB can source the part automatically. This is purchasing metadata only and does not change the circuit.
- `J1` retains the original low-cost EVERCOM `5301-8P8C` (`C3097717`). Its eight signal holes now use the manufacturer's recommended 0.90 mm diameter; the connector position and two 3.20 mm locating holes are unchanged. Confirm the connector orientation and drill pattern in the vendor preview and prototype batch before production use.
- `JP1` and `JP2` are existing three-pad solder selectors on the bottom of the board. `JP1` selects the FirstBuild-compatible signal mapping. `JP2` selects the normal or alternate appliance power input. Both default to pads 1-2 because that copper bridge is part of the manufactured board; changing one requires cutting that bridge and soldering pads 2-3.

Rev 2.2 does not add a new user-operated jumper, programming connector, or automatic pin-1/pin-3 power-selection circuit. The service pads and solder selectors described below already existed in Rev 2.1 and remain unpopulated. Do not combine the [Rev 2.1 package](../rev2.1/README.md) with Rev 2.2 files.

## Debug and programming access

Rev 2.2 preserves two service interfaces, both excluded from factory assembly:

- `J2` is a row of six 2.54 mm through-holes carrying, from square pin 1 to pin 6, 3.3 V, ground, boot, board transmit, board receive, and enable. Revision 2.2 leaves these holes unpopulated. A header may be soldered into them later, or a custom pogo fixture may contact them.
- `J3` carries the same six signals on a flat, bottom-side Tag-Connect `TC2030-IDC-NL` pattern. It has copper contacts and three alignment holes but no connector component, so it adds no BOM or assembly cost. A compatible cable or reusable pogo clip can make a no-solder connection.

Neither interface is USB. Connecting a Mac requires a 3.3 V USB-to-UART adapter plus the matching cable or fixture; do not connect 5 V logic to these signals. The current Rev 2 enclosure covers both service areas and is unchanged in this revision.

## Manufacturing files

- [`GERBER-OnionStraws-rev2.2.zip`](manufacturing/GERBER-OnionStraws-rev2.2.zip): two-layer Gerbers, plated and non-plated drill files, and the Gerber job file.
- [`BOM-OnionStraws-rev2.2.csv`](manufacturing/BOM-OnionStraws-rev2.2.csv): JLCPCB-ready assembly BOM with DNP parts excluded.
- [`CPL-OnionStraws-rev2.2.csv`](manufacturing/CPL-OnionStraws-rev2.2.csv): JLCPCB-ready top-side placement data for the installed parts, including through-hole J1. U1 and the unpopulated J2 header are excluded.

## Validation exports

- [Schematic PDF](validation/schematic.pdf)
- [Top-side 2D board view](validation/board-top.png)
- [Bottom-side 2D board view](validation/board-bottom.png)

These exports are generated from the Rev 2.2 KiCad sources without editor chrome, grid, or net labels. The J1 footprint intentionally has no 3D model until an exact EVERCOM model is verified.

The red X marks in the schematic are KiCad **Do Not Populate** indicators. They identify footprints intentionally left unassembled, including U1 and the optional service interfaces; they are not broken wires or ERC errors. The embedded board rendering is an orientation aid and may omit components for which no verified 3D model is available.

## Parts to recheck when ordering

These are the intended parts. Inventory changes, so confirm them on the order screen.

| Designator | Value/package | Part | LCSC | Notes |
| --- | --- | --- | --- | --- |
| R22 | 4K7 / 0805 | UNI-ROYAL `0805W8F4701T5E` | [C17673](https://lcsc.com/product-detail/Chip-Resistor-Surface-Mount_Uniroyal-Elec-0805W8F4701T5E_C17673.html) | 4.7 kΩ, ±1%, 125 mW, 150 V, −55 to +155 °C, 0805; check current stock |
| R18, R21 | 220k / 0805 | RALEC `RTT052203FTP` | [C104108](https://www.lcsc.com/product-detail/C104108.html) | 220 kΩ, ±1%, 125 mW, 150 V, −55 to +155 °C, 0805; check current stock |
| U4, U5 | 74LVC2G07 / SOT-23-6 | DIODES `74LVC2G07W6-7` | [C151607](https://www.lcsc.com/product-detail/C151607.html) | Correct package and pinout; check current stock |
| U6 | AP2205-3.3 / SOT-89-3 | TECH PUBLIC `TPAP2205-33Y` | [C19268131](https://www.lcsc.com/product-detail/C19268131.html) | 3.3 V, 200 mA, 30 V LDO, SOT-89-3; LCSC lists it as a substitute for the original `C5205181`; confirm current stock |

## Current status

Rev 2.2 is the recommended manufacturing candidate, but physical bring-up testing is still pending. A JLCPCB quote checked on September 19, 2026 was **$78.07 before shipping and tax for five fully assembled boards**, or about **$15.61 per board**. See the [ordering guide](../ORDERING.md) for the short ordering process.

## Rev 2.2 order and test checks

- Upload only the Rev 2.2 Gerber ZIP, BOM, and CPL together. Confirm the preview shows a 2-layer, 1.6 mm, approximately 88.6 mm by 30.0 mm board.
- Confirm all 59 assembled designators are recognized and U1 and J2 are absent. Recheck the listed catalog parts and U4/U5/U6 availability in the live quote.
- Confirm J1 is EVERCOM `5301-8P8C` (`C3097717`), its socket opens toward the short board edge, and its eight pins and two locating posts align with the drill preview. Stop if the assembler will not install it unless hand soldering is acceptable.
- Confirm whether the target appliance supplies power on connector pin 1 or pin 3. Rev 2.2 retains the existing pin-1 default through `JP2`; selecting pin 3 requires cutting and soldering the bottom-side selector.
- During first bring-up, power the adapter from one source at a time, verify the 5 V and 3.3 V rails, and confirm repeated stable boots without U1.

KiCad 9.0.9 reports the same ERC and DRC issues as Rev 2.1, with no new categories. The Gerber ZIP also passes its integrity check. Physical testing is still outstanding.

[Back to the PCB revision index](../README.md) · [Ordering guide](../ORDERING.md) · [Rev 2 enclosure](../../case/rev2/README.md) · [Firmware examples](../../firmware/README.md)
