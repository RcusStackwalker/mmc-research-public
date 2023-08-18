#include <maps_desc.h>

DECLARE_VALUE_DESC(flash_romid, "ECU", "ECU ID", "ECU ID");

DECLARE_ARRAY_DESC(flash_mode_flags0_init,
	"ECU Options",
	"ECU Options Set #1",
	"blobbits",
	"\t\t<table name=\"Periphery Bit Number\" type=\"Static Y Axis\" flipy=\"true\" elements=\"16\">\n"
	"\t\t\t<data>bit.15</data>\n"
	"\t\t\t<data>bit.14</data>\n"
	"\t\t\t<data>bit.13</data>\n"
	"\t\t\t<data>bit.12</data>\n"
	"\t\t\t<data>bit.11</data>\n"
	"\t\t\t<data>bit.10</data>\n"
	"\t\t\t<data>bit.09</data>\n"
	"\t\t\t<data>bit.08</data>\n"
	"\t\t\t<data>bit.07</data>\n"
	"\t\t\t<data>bit.06</data>\n"
	"\t\t\t<data>bit.05</data>\n"
	"\t\t\t<data>bit.04</data>\n"
	"\t\t\t<data>bit.03</data>\n"
	"\t\t\t<data>bit.02</data>\n"
	"\t\t\t<data>bit.01</data>\n"
	"\t\t\t<data>bit.00</data>\n"
	"\t\t</table>\n");


DECLARE_ARRAY_DESC(flash_mode_flags1_init,
	"ECU Options",
	"ECU Options Set #2",
	"blobbits",
	"\t\t<table name=\"Periphery Bit Number\" type=\"Static Y Axis\" flipy=\"true\" elements=\"16\">\n"
	"\t\t\t<data>bit.15                                                </data>\n"
	"\t\t\t<data>bit.14 0=Disable O2 Heaters                           </data>\n"
	"\t\t\t<data>bit.13                                                </data>\n"
	"\t\t\t<data>bit.12 0=Disable Purge Control                        </data>\n"
	"\t\t\t<data>bit.11                                                </data>\n"
	"\t\t\t<data>bit.10                                                </data>\n"
	"\t\t\t<data>bit.09 0=Disable Warmup Spark Retard                  </data>\n"
	"\t\t\t<data>bit.08                                                </data>\n"
	"\t\t\t<data>bit.07 0=Disable Knock Control                        </data>\n"
	"\t\t\t<data>bit.06 0=Disable Speed Limit fuel cut                 </data>\n"
	"\t\t\t<data>bit.05                                                </data>\n"
	"\t\t\t<data>bit.04 1=Enable Closed Loop, 0=Enable pot trimmed idle</data>\n"
	"\t\t\t<data>bit.03 0=Disable Immobilizer                          </data>\n"
	"\t\t\t<data>bit.02                                                </data>\n"
	"\t\t\t<data>bit.01 0=Disable O2 Rear Sensor                       </data>\n"
	"\t\t\t<data>bit.00                                                </data>\n"
	"\t\t</table>\n");

DECLARE_ARRAY_DESC(flash_mode_flags2_init,
	"ECU Options",
	"ECU Options Set #3",
	"blobbits",
	"\t\t<table name=\"Periphery Bit Number\" type=\"Static Y Axis\" flipy=\"true\" elements=\"16\">\n"
	"\t\t\t<data>bit.15                                       </data>\n"
	"\t\t\t<data>bit.14                                       </data>\n"
	"\t\t\t<data>bit.13 0=Disable CAN Operation               </data>\n"
	"\t\t\t<data>bit.12                                       </data>\n"
	"\t\t\t<data>bit.11                                       </data>\n"
	"\t\t\t<data>bit.10                                       </data>\n"
	"\t\t\t<data>bit.09                                       </data>\n"
	"\t\t\t<data>bit.08 0=Disable Use of APPS_SUB power       </data>\n"
	"\t\t\t<data>bit.07                                       </data>\n"
	"\t\t\t<data>bit.06 0=Disable Fuel Level Sensor           </data>\n"
	"\t\t\t<data>bit.05                                       </data>\n"
	"\t\t\t<data>bit.04 0=Disable A/C Pressure Sensor         </data>\n"
	"\t\t\t<data>bit.03                                       </data>\n"
	"\t\t\t<data>bit.02                                       </data>\n"
	"\t\t\t<data>bit.01 0=Disable High Speed Cruise enrichment</data>\n"
	"\t\t\t<data>bit.00 0=Disable Lean Spool                  </data>\n"
	"\t\t</table>\n");

DECLARE_ARRAY_DESC(flash_mode_flags3_init,
	"ECU Options",
	"ECU Options Set #4",
	"blobbits",
	"\t\t<table name=\"Periphery Bit Number\" type=\"Static Y Axis\" flipy=\"true\" elements=\"16\">\n"
	"\t\t\t<data>bit.15 - 0=Disable slow solenoid valves check</data>\n"
	"\t\t\t<data>bit.14 - 0=Disable extensive evap check</data>\n"
	"\t\t\t<data>bit.13 - 0=Disable extensive purge flow check</data>\n"
	"\t\t\t<data>bit.12</data>\n"
	"\t\t\t<data>bit.11 - 0=Disable O2 Heaters check: P0155, P0161, P0135, P0141</data>\n"
	"\t\t\t<data>bit.10 - 0=Disable Manifold Differential Pressure Sensor check</data>\n"
	"\t\t\t<data>bit.09 - 0=Disable EGR Valve check, Flow Check : P0400</data>\n"
	"\t\t\t<data>bit.08 - 0=Disable Idle check</data>\n"
	"\t\t\t<data>bit.07 - 0=Disable Fuel Trim check</data>\n"
	"\t\t\t<data>bit.06 - 0=Disable Coolant Temperature low check</data>\n"
	"\t\t\t<data>bit.05</data>\n"
	"\t\t\t<data>bit.04 - 0=Disable Misfire check</data>\n"
	"\t\t\t<data>bit.03 - 0=Disable O2 Front Sensor rich check</data>\n"
	"\t\t\t<data>bit.02</data>\n"
	"\t\t\t<data>bit.01 - 0=Disable Catalyst check</data>\n"
	"\t\t\t<data>bit.00 - 1=Delayed use of O2 sensors</data>\n"
	"\t\t</table>\n");

DECLARE_ARRAY_DESC(flash_mode_flags4_init,
	"ECU Options",
	"ECU Options Set #5",
	"blobbits",
	"\t\t<table name=\"Periphery Bit Number\" type=\"Static Y Axis\" flipy=\"true\" elements=\"16\">\n"
	"\t\t\t<data>bit.15</data>\n"
	"\t\t\t<data>bit.14</data>\n"
	"\t\t\t<data>bit.13, P0425 - Catalyst Temperature Sensor fault</data>\n"
	"\t\t\t<data>bit.12</data>\n"
	"\t\t\t<data>bit.11 - 0=Disable fuel temperature sensor</data>\n"
	"\t\t\t<data>bit.10</data>\n"
	"\t\t\t<data>bit.09</data>\n"
	"\t\t\t<data>bit.08</data>\n"
	"\t\t\t<data>bit.07</data>\n"
	"\t\t\t<data>bit.06</data>\n"
	"\t\t\t<data>bit.05</data>\n"
	"\t\t\t<data>bit.04</data>\n"
	"\t\t\t<data>bit.03</data>\n"
	"\t\t\t<data>bit.02</data>\n"
	"\t\t\t<data>bit.01</data>\n"
	"\t\t\t<data>bit.00</data>\n"
	"\t\t</table>\n");
