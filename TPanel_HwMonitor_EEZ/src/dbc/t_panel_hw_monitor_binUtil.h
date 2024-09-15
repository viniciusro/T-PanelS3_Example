#pragma once

#include "t_panel_hw_monitor.h"

typedef struct
{
  GPU_HW_t GPU_HW;                // TX [T_Panel]. RX [PC ].
  RAM_HDD_HW_t RAM_HDD_HW;        // TX [T_Panel]. RX [PC ].
  INFO_PC_t INFO_PC;              // TX [PC].      RX [T_Panel ].
  CPU_HW_t CPU_HW;                // TX [T_Panel]. RX [PC ].
} hwMonitor_rx_t;

typedef struct
{
  GPU_HW_t GPU_HW;                // TX [T_Panel]. RX [PC ].
  RAM_HDD_HW_t RAM_HDD_HW;        // TX [T_Panel]. RX [PC ].
  INFO_PANEL_t INFO_PANEL;        // TX [T_Panel]. RX [PC ].
  CPU_HW_t CPU_HW;                // TX [T_Panel]. RX [PC ].
} hwMonitor_tx_t;


uint32_t hwMonitor_Receive(hwMonitor_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_);


// define @__DEF_HWMONITOR__ in the @dbccodeconf.h file for allocation in utility source code.
#ifdef __DEF_HWMONITOR__

extern hwMonitor_rx_t hwMonitor_rx;
extern hwMonitor_tx_t hwMonitor_tx;

#endif

