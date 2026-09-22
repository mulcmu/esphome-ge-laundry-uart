# PCB Rev 2.1

Rev 2.1 is the latest built Rev 2.x design before the corrective Rev 2.2 work. Its KiCad project was migrated to KiCad 9.

> [!WARNING]
> The RX and TX silkscreen labels are swapped. U1 can cause ESP32 boot loops. The manufacturing files are preserved for history and should not be mistaken for a corrected release.

## Files

- [Open the KiCad project](design/OnionStraws.kicad_pro)
- [Schematic source](design/OnionStraws.kicad_sch)
- [PCB source](design/OnionStraws.kicad_pcb)
- [Gerber archive](manufacturing/GERBER-OnionStraws-rev2.1.zip)
- [Bill of materials](manufacturing/BOM-OnionStraws-rev2.1.csv)
- [Component placement list](manufacturing/CPL-OnionStraws-rev2.1.csv)
- [Plated-hole drill map](validation/pth-drill-map.pdf)
- [Non-plated-hole drill map](validation/npth-drill-map.pdf)
- [U1 trace-removal illustration](images/u1-trace-fix.png)

The PCB silkscreen identifies this source as Revision 2.1, while the inherited schematic title block still says 2.0. The historical files are unchanged, and this README calls out the mismatch.

No schematic PDF or board-view image was included with the retained Rev 2.1 artifacts, and those exports were not reconstructed.

[Back to the PCB revision index](../README.md) · [Rev 2 enclosure](../../case/rev2/README.md) · [Firmware examples](../../firmware/README.md)
