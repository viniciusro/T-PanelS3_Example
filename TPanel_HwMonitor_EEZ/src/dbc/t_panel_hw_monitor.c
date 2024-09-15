#include "t_panel_hw_monitor.h"

// --------------------------------------------------------------------------
uint32_t Unpack_GPU_HW_hwMonitor(GPU_HW_t *_m, const uint8_t *_d, uint8_t dlc_)
{
  _m->gpuCoreFrequency = ((_d[1] & (0x3FU)) << 8) | (_d[0] & (0xFFU));
  _m->gpuMemoryFrequency = ((_d[3] & (0x3FU)) << 8) | (_d[2] & (0xFFU));
  _m->gpuTemp = (_d[4] & (0xFFU));
  _m->gpuUsage = (_d[5] & (0xFFU));
  return GPU_HW_CANID;
}

uint32_t Pack_GPU_HW_hwMonitor(const GPU_HW_t *_m, uint8_t *_d)
{
  uint8_t i;
  for (i = 0; i < GPU_HW_DLC; _d[i++] = 0);

  _d[0] |= (_m->gpuCoreFrequency & (0xFFU));
  _d[1] |= ((_m->gpuCoreFrequency >> 8) & (0x3FU));
  _d[2] |= (_m->gpuMemoryFrequency & (0xFFU));
  _d[3] |= ((_m->gpuMemoryFrequency >> 8) & (0x3FU));
  _d[4] |= (_m->gpuTemp & (0xFFU));
  _d[5] |= (_m->gpuUsage & (0xFFU));
  //*_len = 6;
  //*_ide = 0;
  return GPU_HW_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_RAM_HDD_HW_hwMonitor(RAM_HDD_HW_t *_m, const uint8_t *_d, uint8_t dlc_)
{
  _m->hddUsage_0 = (_d[0] & (0xFFU));
  _m->hddUsage_1 = (_d[1] & (0xFFU));
  _m->hddUsage_2 = (_d[2] & (0xFFU));
  _m->ramUsage = (_d[3] & (0xFFU));
  return RAM_HDD_HW_CANID;
}

uint32_t Pack_RAM_HDD_HW_hwMonitor(const RAM_HDD_HW_t *_m, uint8_t *_d)
{
  uint8_t i;
  for (i = 0; i < RAM_HDD_HW_DLC; _d[i++] = 0);

  _d[0] |= (_m->hddUsage_0 & (0xFFU));
  _d[1] |= (_m->hddUsage_1 & (0xFFU));
  _d[2] |= (_m->hddUsage_2 & (0xFFU));
  _d[3] |= (_m->ramUsage & (0xFFU));
  // *_len = 4;
  // *_ide = 0;
  return RAM_HDD_HW_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_INFO_PC_hwMonitor(INFO_PC_t *_m, const uint8_t *_d, uint8_t dlc_)
{
  _m->INFO_ALIVE_PC = (_d[0] & (0xFFU));
  return INFO_PC_CANID;
}

uint32_t Pack_INFO_PC_hwMonitor(const INFO_PC_t *_m, uint8_t *_d)
{
  uint8_t i; 
  for (i = 0; i < INFO_PC_DLC; _d[i++] = 0);

  _d[0] |= (_m->INFO_ALIVE_PC & (0xFFU));

  return INFO_PC_CANID;
}
// --------------------------------------------------------------------------
uint32_t Unpack_INFO_PANEL_hwMonitor(INFO_PANEL_t *_m, const uint8_t *_d, uint8_t dlc_)
{
  _m->INFO_ALIVE_PANEL = ((_d[3] & (0xFFU)) << 24) | ((_d[2] & (0xFFU)) << 16) | ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->alive_counter = (_d[4] & (0x0FU));
  return INFO_PANEL_CANID;
}

uint32_t Pack_INFO_PANEL_hwMonitor(const INFO_PANEL_t *_m, uint8_t *_d)
{
  uint8_t i; 
  for (i = 0; i < INFO_PANEL_DLC; _d[i++] = 0);

  _d[0] |= (_m->INFO_ALIVE_PANEL & (0xFFU));
  _d[1] |= ((_m->INFO_ALIVE_PANEL >> 8) & (0xFFU));
  _d[2] |= ((_m->INFO_ALIVE_PANEL >> 16) & (0xFFU));
  _d[3] |= ((_m->INFO_ALIVE_PANEL >> 24) & (0xFFU));
  _d[4] |= (_m->alive_counter & (0x0FU));

  return INFO_PANEL_CANID;
}

// --------------------------------------------------------------------------
uint32_t Unpack_CPU_HW_hwMonitor(CPU_HW_t *_m, const uint8_t *_d, uint8_t dlc_)
{
  _m->cpuFrequency = ((_d[1] & (0x0FU)) << 8) | (_d[0] & (0xFFU));
  _m->cpuPowerDrawPackage = (_d[2] & (0xFFU));
  _m->cpuTemp = (_d[3] & (0xFFU));
  _m->cpuUsage = (_d[4] & (0xFFU));
  return CPU_HW_CANID;
}

uint32_t Pack_CPU_HW_hwMonitor(const CPU_HW_t *_m, uint8_t *_d)
{
  uint8_t i;
  for (i = 0; i < CPU_HW_DLC; _d[i++] = 0);

  _d[0] |= (_m->cpuFrequency & (0xFFU));
  _d[1] |= ((_m->cpuFrequency >> 8) & (0x0FU));
  _d[2] |= (_m->cpuPowerDrawPackage & (0xFFU));
  _d[3] |= (_m->cpuTemp & (0xFFU));
  _d[4] |= (_m->cpuUsage & (0xFFU));
  // *_len = 5;
  // *_ide = 0;
  return CPU_HW_CANID;
}
