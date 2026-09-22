# Contributing

Please discuss substantial hardware changes in an issue before preparing a pull request. Keep each change bounded to one board revision or one repository concern.

## Repository conventions

- Put board-specific files under `pcb/<revision>/` and enclosure-specific files under `case/<revision>/`.
- Keep editable KiCad files in `design/`, files used for ordering in `manufacturing/`, review files in `validation/`, and documentation photographs or renders in `images/`.
- Keep each manufacturing package self-contained. Never combine a Gerber archive, BOM, or CPL from different revisions.
- Use repository-relative links and direct README links so readers do not have to discover files by browsing directories.
- Do not commit KiCad local state, automatic backups, Python bytecode, extracted duplicate Gerbers, or vendor project databases.

## Hardware validation

KiCad 9 is the current source format. Before submitting PCB changes:

1. Open the project from a clean clone and confirm symbols, footprints, and 3D models resolve.
2. Run ERC and DRC and explain any accepted violations.
3. Regenerate the schematic, board views, Gerbers, BOM, and CPL from the committed source.
4. Confirm reference designators agree across the schematic, PCB, BOM, and CPL.
5. State which checks were run and which hardware tests still need to be completed.

Use focused Conventional Commit messages such as `fix(pcb): correct rev2.2 uart labels` or `docs(case): document rev3a print orientation`.
