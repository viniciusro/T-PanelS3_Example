#include "t_panel_hw_monitor_binUtil.h"

#ifdef __DEF_HWMONITOR__

hwMonitor_rx_t hwMonitor_rx;
hwMonitor_tx_t hwMonitor_tx;

#endif

uint32_t hwMonitor_Receive(hwMonitor_rx_t *_m, const uint8_t *_d, uint32_t _id, uint8_t dlc_)
{
    uint32_t recid = 0;
    if (_id >= 0x1U && _id < 0x3U)
    {
        if (_id == 0x1U)
        {
            recid = Unpack_CPU_HW_hwMonitor(&(_m->CPU_HW), _d, dlc_);
        }
        else if (_id == 0x2U)
        {
            recid = Unpack_GPU_HW_hwMonitor(&(_m->GPU_HW), _d, dlc_);
        }
    }
    else
    {
        if (_id == 0x3U)
        {
            recid = Unpack_RAM_HDD_HW_hwMonitor(&(_m->RAM_HDD_HW), _d, dlc_);
        }
        else if (_id == 0x4U)
        {
            recid = Unpack_INFO_PC_hwMonitor(&(_m->INFO_PC), _d, dlc_);
        }
    }

    return recid;
}