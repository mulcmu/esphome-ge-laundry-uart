

*Baseline* ERDS.txt from https://github.com/doitaljosh/ge-appliances-re

##### Common:

| Erd:     | Function:                  |
| -------- | -------------------------- |
| *0x0004* | *LockStatus*               |
| *0x0006* | *ClockFormat*              |
| *0x0007* | *TempUnit*                 |
| *0x0009* |                            |
| *0x000A* | *SoundLevel*               |
| 0x0037   | Subscribed ERD on Dryer U+ |
| *0x0051* |                            |
| *0x0100* |                            |
| *0x0103* |                            |
| *0x510A* |                            |

##### Advantium:

| Erd:     | Function:                                                    |
| -------- | ------------------------------------------------------------ |
| *0x0035* | *UnitType*                                                   |
| *0x0050* |                                                              |
| *0x5109* |                                                              |
| *0x5400* | *Set CookMode	<br />    1:Broil<br/>	2: ConvectionBake<br/>	3: Microwave<br/>	4: MicrowaveSensor<br/>	5: PrecisionCook<br/>	6: PrecisionCookCustom<br/>	7: PrecisionCookStaged<br/>	8: Proof<br/>	9: RemoteCookModeConfig<br/>	10: SteamClean<br/>	11: Toast<br/>	12: Warm* |
| *0x5401* | *Oven Status 1	<br />	1: CookAction<br/>	2: CookMode<br/>	3: CoolingFanStatus<br/>	4: DoorStatus<br/>	5: OvenLightStatus<br/>	6: PreheatStatus<br/>	7: SensingActive<br/>	8: TerminationReason<br/>	9: WarmStatus* |
| *0x5402* | *Oven Status 2<br />	1: CookAction<br/>	2: CookMode<br/>	3: CoolingFanStatus<br/>	4: DoorStatus<br/>	5: OvenLightStatus<br/>	6: PreheatStatus<br/>	7: SensingActive<br/>	8: TerminationReason<br/>	9: WarmStatus* |

##### Laundry:

| Erd:     | Function:                                                    |
| -------- | ------------------------------------------------------------ |
| *0x2000* | *StateDetail*<br />Dryer subscribed                          |
| *0x2001* | *SubCycle*<br />Dryer subscribed                             |
| 0x2002   | Dryer subscribed                                             |
| *0x2007* |                                                              |
| *0x2008* | *<br/>	1: labelFirstTank<br/>	2: labelSecondTank<br/>	3: statusFirstTank<br/>	4: statusSecondTank* |
| *0x2009* | *<br/>	1: isFirstTankEnable<br/>	2: isSecondTankEnable<br/>	3: labelFirstTank<br/>	4: labelSecondTank* |
| *0x200A* | *Cycle*<br />Dryer subscribed<br />0x89:Mixed Load   <br />0x0D:Delicates   <br />0x80:Cottons   <br />0x0B:Jeans   <br />0x8B:Casuals   <br />0x88:Quick Dry   <br />0x06:Towels   <br />0x04:Bulky   <br />0x05:Sanitize   <br />0x85:Air Fluff   <br />0x8C:Warm Up   <br />0x83:Timed Dry |
| *0x2010* | Dryer subscribed                                             |
| *0x2014* | *IsEnable*                                                   |
| *0x2015* | *SoilLevel*                                                  |
| *0x2016* | *TempLevel*                                                  |
| *0x2017* | *SpinTimeLEvel*                                              |
| *0x2018* | *RinseOption*                                                |
| *0x2019* | *Option*                                                     |
| *0x201A* | *DrynessLevel*                                               |
| *0x201B* | *IsExtendedTumble*                                           |
| 0x201D   | Dryer subscribed                                             |
| *0x2020* | *SelectedCycle*                                              |
| *0x2021* |                                                              |
| *0x2022* | *<br/>	1: extraLargeLoadSize<br/>	2: largeLoadSize<br/>	3: mediumLoadSize<br/>	4: smallLoadSize<br/>	5: timedDryerSheetsLoadSize* |
| *0x2023* | *totalDryerSheetsNo*                                         |
| 0x2038   | Dryer subscribed                                             |
| *0x2039* | *<br/>	1: isEnable<br/>	2: status<br/>*<br /><br />Dryer subscribed |
| *0x204D* | *drynessLevel*<br />Dryer subscribed<br />0x01: Damp<br />0x02: Less Dry<br />0x03: Dry<br />0x04 More Dry |
| *0x2050* | *~~option~~*<br />Heat Level<br />Dryer subscribed<br />0x01 Air Fluff<br />0x03 Low <br />0x04 Med <br />0x05 High |
| 0x2051   | Dryer subscribed                                             |
| *0x2052* | *isExtendedTumbleValid*<br />Dryer subscribed<br />          |
| *0x2053* | *isExtendedTumble*<br />Dryer subscribed                     |
| *0x206B* | *selectedCycle*                                              |
| *0x206C* | *isEnable*                                                   |
| *0x206E* | *isAllowable*                                                |
| *0x7003* |                                                              |
| *0x7A00* | *FanSetting*                                                 |
| *0x7A01* | *OperationMode*                                              |
| *0x7A02* |                                                              |
| *0x7A04* | *Status*                                                     |
| *0x7A0F* | *OnOffState*                                                 |
| *0x7B00* |                                                              |
| *0x7B05* | *SleepMode*                                                  |
| *0x7B06* |                                                              |
| *0x7B07* | *AutoSwingMode*                                              |
| *0x8004* | *ErrorCode*                                                  |
| *0x8005* |                                                              |
| *0x8007* | *LowSaltAlert*                                               |
| *0x8033* | *ShutOffValveState*                                          |

##### Dishwasher:

| Erd:     | Function:                                                  |
| -------- | ---------------------------------------------------------- |
| *0x3001* | *DishwasherOperationMode<br />	1: Mode*                 |
| *0x3003* | *RinseAgentStatus*                                         |
| *0x3007* |                                                            |
| *0x300E* | *DishwasherCycleState<br />	1: Cycle<br/>	2: Status* |
| *0x301C* | *<br />    1: length<br/>	2: name*                      |
| *0x301F* |                                                            |
| *0x304E* |                                                            |
| 0xD004   |                                                            |

