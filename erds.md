

*Baseline* ERDS.txt from https://github.com/doitaljosh/ge-appliances-re

**GE docx & code** from hawk dryer interface https://github.com/doitaljosh/ge-appliances-re

##### Common:

| Erd:       | Function:                                                    |
| ---------- | ------------------------------------------------------------ |
| **0x0001** | **modelNumber<br />Ascii**                                   |
| **0x0002** | **serialNumber<br />Ascii**                                  |
| **0x0003** | **remoteEnable**                                             |
| *0x0004*   | *LockStatus*                                                 |
| **0x0005** | **clockTime<br />            "hours:UInt8",<br/>            "minutes:UInt8",<br/>            "seconds:UInt8",** |
| *0x0006*   | *ClockFormat*                                                |
| *0x0007*   | *TempUnit*                                                   |
| **0x0008** | **Appliance type**<br />Dryer polls at U+ startup            |
| *0x0009*   | **sabbathMode**                                              |
| *0x000A*   | *SoundLevel*                                                 |
| 0x0035     | Dryer U+ Polls<br />[0x0035:<00 00 00 01>]                   |
| 0x0037     | Subscribed ERD on Dryer U+                                   |
| 0x0039     | Dryer U+ Polls<br />[0x0039:<01 00 03 00>]                   |
| 0x003A     | Dryer U+ Polls<br />0x003A:<01 00 01 2C>]                    |
| 0x003B     | Dryer U+ Polls<br />[0x003B:<01 2C 01 00>]                   |
| *0x0051*   |                                                              |
| 0x0089     | Dryer U+ attempts to poll                                    |
| 0x008F     | Dryer U+ Power on broadcast                                  |
| 0x0090     | Dryer U+ Polls<br />0x0090:<E0 00 01 00>]                    |
| 0x0094     | Dryer U+ Power on broadcast                                  |
| 0x0095     | Dryer U+ Power on broadcast                                  |
| 0x0096     | Dryer U+ Power on broadcast                                  |
| 0x0097     | Dryer U+ Power on broadcast                                  |
| 0x0099     | Dryer U+ Power on broadcast                                  |
| *0x0100*   |                                                              |
| *0x0103*   |                                                              |
| 0x0106     | Dryer U+ attempts to subscribe at boot<br />Attempts to poll later |
| 0x107      | Dryer U+ attempts to subscribe at boot<br />Attempts to poll later |
| 0x0108     | Dryer U+ Power on broadcast                                  |
| *0x510A*   |                                                              |

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

| Erd:       | Function:                                                    |
| ---------- | ------------------------------------------------------------ |
| *0x2000*   | *StateDetail*<br />Dryer subscribed<br />**i.	0 = Idle<br/>ii.	1 = Standby<br/>iii.	2 = Run<br/>iv.	3 = Pause<br/>v.	4 = EOC<br/>vi.	5 = DSMDelayRun<br/>vii.	6 = DelayRun<br/>viii.	7 = DelayPause<br/>ix.	8 = DrainTimeout<br/>x.	9 to 127 =  Not used<br/>xi.	128 = Clean Speak** |
| *0x2001*   | *SubCycle*<br />Dryer subscribed<br />**i.	0 = Not applicable<br/>ii.	1 = Fill (washer only)<br/>iii.	2 = Soak(washer only)<br/>iv.	3 = Wash (washer only)<br/>v.	4 = Rinse(washer only)<br/>vi.	5 = Spin(washer only)<br/>vii.	6 = Drain(washer only)<br/>viii.	7 = Extra Spin(washer only)<br/>ix.	8 = Extra Rinse(washer only)<br/>x.	9 = Tumble (Dryer only)<br/>xi.	10 = Load Size Detection (washer or dryer)<br/>xii.	11 to 127 = Not used<br/>xiii.	128 =  Drying (dryer)<br/>xiv.	129 =  Mist Steam (dryer)<br/>xv.	130 = Cool Down (dryer)<br/>xvi.	131 = Extended Tumble (dryer)<br/>xvii.	132 = Damp (dryer)<br/>xviii.	133 = Airfluff (dryer)** |
| 0x2002     | **End of Cycle**<br />Dryer subscribed                       |
| **0x2003** | **Cycle Count**<br />U16 returned indicating the number of cycles unit has run. |
| **0x2004** | **Service Error Codes **                                     |
| **0x2005** | **Demand Response Overrides Allowed**                        |
| *0x2007*   | **Cycle Time Remaining**<br />U16 Dryer polls<br />Washer polls |
| *0x2008*   | *<br/>	1: labelFirstTank<br/>	2: labelSecondTank<br/>	3: statusFirstTank<br/>	4: statusSecondTank* |
| *0x2009*   | *<br/>	1: isFirstTankEnable<br/>	2: isSecondTankEnable<br/>	3: labelFirstTank<br/>	4: labelSecondTank* |
| *0x200A*   | *Cycle*<br />Dryer subscribed<br />0x89:Mixed Load   <br />0x0D:Delicates   <br />0x80:Cottons   <br />0x0B:Jeans   <br />0x8B:Casuals   <br />0x88:Quick Dry   <br />0x06:Towels   <br />0x04:Bulky   <br />0x05:Sanitize   <br />0x85:Air Fluff   <br />0x8C:Warm Up   <br />0x83:Timed Dry<br />0x14:Colors<br />0x09:Whites<br />0x82: Active Wear<br />0x1D:Quick Wash<br />0x02: Drain & Spin<br />0x1A: Deep Clean |
| **0x200E** | **Operating Mode**<br/>i.	0 = Consumer Mode<br/>ii.	1 = Service Mode<br/>iii.	2 = Native Mode<br/>iv.	3 = Continuous Cycle/Evaluation Mode<br/>v.	4 - Rapid Relay Mode<br/>vi.	5 = FCT Mode (EOL on M1 Laundry)<br/>vii.	6 = Model Plug Entry Mode<br/>viii.	7 = Demo Mode<br/>ix.	8 = Consumer Error Mode<br/>x.	9 = Floor Type Selection Mode |
| **0x200F** | **Critical Response**                                        |
| *0x2010*   | **Delay Time Remaining** (resolution minutes)<br />Dryer subscribed<br /> |
| 0x2012     | Dryer Polls<br />1 at startup<br />Washer Polls as well      |
| *0x2014*   | *IsEnable*                                                   |
| *0x2015*   | *SoilLevel*<br />0x01 Light<br />0x02 Normal<br />0x03 Heavy<br />0x04 Ex Heavy |
| *0x2016*   | *TempLevel*<br />0x10 Tap cold<br />0x11 Cold<br />0x12 Cool<br />0x13 Colors<br />0x14 Warm<br />0x15 Hot |
| *0x2017*   | *SpinTimeLEvel*<br />0x00 No Spin<br />0x02 Normal<br />0x03 More<br />0x04 Max |
| *0x2018*   | *RinseOption*<br />Appears bit mapped<br />bit 0: Deep Rinse On/Off<br />bit 1: Extra Rinse On/Off |
| *0x2019*   | *Option*                                                     |
| *0x201A*   | *DrynessLevel*                                               |
| *0x201B*   | *IsExtendedTumble*                                           |
| 0x201C     | Dryer Polls                                                  |
| 0x201D     | Dryer subscribed                                             |
| *0x2020*   | *SelectedCycle*                                              |
| *0x2021*   |                                                              |
| *0x2022*   | Dryer polls 5 bytes returned*<br/>	1: extraLargeLoadSize<br/>	2: largeLoadSize<br/>	3: mediumLoadSize<br/>	4: smallLoadSize<br/>	5: timedDryerSheetsLoadSize* |
| *0x2023*   | *totalDryerSheetsNo*<br />Dryer Polls                        |
| 0x2038     | Dryer subscribed                                             |
| *0x2039*   | *<br/>	1: isEnable<br/>	2: status<br/>*<br /><br />Dryer subscribed |
| 0x2040     | Dryer Polls                                                  |
| 0x2041     | Dryer Polls                                                  |
| *0x204D*   | *drynessLevel*<br />Dryer subscribed<br />0x01: Damp<br />0x02: Less Dry<br />0x03: Dry<br />0x04 More Dry |
| *0x2050*   | *~~option~~*<br />Heat Level<br />Dryer subscribed<br />0x01 Air Fluff<br />0x03 Low <br />0x04 Med <br />0x05 High |
| 0x2051     | Dryer subscribed                                             |
| *0x2052*   | *isExtendedTumbleValid*<br />Dryer subscribed<br />          |
| *0x2053*   | *isExtendedTumble*<br />Dryer subscribed                     |
| *0x206B*   | *selectedCycle*                                              |
| *0x206C*   | *isEnable*                                                   |
| *0x206E*   | *isAllowable*                                                |
| *0x7003*   |                                                              |
| *0x7A00*   | *FanSetting*                                                 |
| *0x7A01*   | *OperationMode*                                              |
| *0x7A02*   |                                                              |
| *0x7A04*   | *Status*                                                     |
| *0x7A0F*   | *OnOffState*                                                 |
| *0x7B00*   |                                                              |
| *0x7B05*   | *SleepMode*                                                  |
| *0x7B06*   |                                                              |
| *0x7B07*   | *AutoSwingMode*                                              |
| *0x8004*   | *ErrorCode*                                                  |
| *0x8005*   |                                                              |
| *0x8007*   | *LowSaltAlert*                                               |
| *0x8033*   | *ShutOffValveState*                                          |

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

Random erds at end of capture11.txt  Looks like they get polled at 5 min intervals

0xE101 4 bytes

0xE103 8 bytes

0xE119 8 bytes

0xE13B 8 bytes



Capture 1 read near start

0xE000

[0xE100:<00 01 01 00 00 1F 00 0A 00 10 00 14>
