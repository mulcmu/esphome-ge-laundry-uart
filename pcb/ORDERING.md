# Order a Rev 2.2 board

You do not need KiCad to order the board. This guide uses JLCPCB, but another PCB assembly company can use the same files.

[Back to the project overview](../README.md) · [PCB revision index](README.md)

> [!NOTE]
> Rev 2.2 has not yet been tested as an assembled board. Order the minimum quantity first. If you want to wait for tested hardware, check the [Rev 2.2 status](rev2.2/README.md) before ordering.

## Download these three files

- [Gerber ZIP](rev2.2/manufacturing/GERBER-OnionStraws-rev2.2.zip): the board itself
- [BOM](rev2.2/manufacturing/BOM-OnionStraws-rev2.2.csv): the parts list
- [CPL](rev2.2/manufacturing/CPL-OnionStraws-rev2.2.csv): where the parts go

Keep these three Rev 2.2 files together. Do not use a BOM or CPL from an older revision.

## Place the order

1. Open the JLCPCB PCB quote page and upload the Gerber ZIP.
2. The site should detect a 2-layer board about 88.6 mm by 30.0 mm. Use the standard 1.6 mm board thickness.
3. Choose five PCBs and enable PCB assembly for all five boards.
4. Select economic, top-side assembly.
5. Upload the Rev 2.2 BOM and CPL when prompted.
6. Review the board and component-placement previews. Resolve any missing, unselected, or obviously misplaced parts before continuing.

## Current price estimate

A JLCPCB quote checked on September 19, 2026 was **$78.07 before shipping and tax for five fully assembled boards**, or about **$15.61 per board**. Treat this as a dated estimate because component stock and pricing change.

## Before paying

Before continuing, check that:

- The board is about 88.6 mm by 30.0 mm and has two layers.
- Assembly is enabled for all five boards on the top side.
- The component-placement preview looks aligned with the board.
- The parts list has no unresolved or unselected items.

The [Rev 2.2 page](rev2.2/README.md) has the full part list and board images if you need to compare them with the order screen.

## When the boards arrive

1. Check for bent connectors, loose parts, or visible solder bridges.
2. Follow the [firmware setup guide](../firmware/README.md) to flash the board.
3. Do not connect it to an appliance until the 3.3 V and 5 V power rails have been checked. Rev 2.2 is still awaiting its first assembled-board test.

If you do not have the tools to check the power rails, wait until the first Rev 2.2 batch has been tested and the results are posted.
