#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// def @GPU_HW CAN Message (2)
#define GPU_HW_IDE (0U)
#define GPU_HW_DLC (6U)
#define GPU_HW_CANID (0x2U)
// -- OpenHardwareMonitor data for GPU
typedef struct
{

  uint16_t gpuCoreFrequency;                //      Bits=14.  [ 0     , 16383  ]  Unit:''     

  uint16_t gpuMemoryFrequency;              //      Bits=14.  [ 0     , 16383  ]  Unit:''     

  uint8_t gpuTemp;                          //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t gpuUsage;                         //      Bits=08.  [ 0     , 255    ]  Unit:''     
} GPU_HW_t;

// def @RAM_HDD_HW CAN Message (3)
#define RAM_HDD_HW_IDE (0U)
#define RAM_HDD_HW_DLC (4U)
#define RAM_HDD_HW_CANID (0x3U)
// -- OpenHardwareMonitor data for RAM and HDD
typedef struct
{

  uint8_t hddUsage_0;                       //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t hddUsage_1;                       //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t hddUsage_2;                       //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t ramUsage;                         //      Bits=08.  [ 0     , 255    ]  Unit:''     
} RAM_HDD_HW_t;

// def @INFO_PC CAN Message (4)
#define INFO_PC_IDE (0U)
#define INFO_PC_DLC (1U)
#define INFO_PC_CANID (0x4U)
typedef struct
{

  uint8_t INFO_ALIVE_PC;                    //      Bits=08.  [ 0     , 255    ]  Unit:''     
} INFO_PC_t;

// def @INFO_PANEL CAN Message (5)
#define INFO_PANEL_IDE (0U)
#define INFO_PANEL_DLC (5U)
#define INFO_PANEL_CANID (0x5U)
typedef struct
{
  uint32_t INFO_ALIVE_PANEL;                //      Bits=32.  [ 0     , 4294967295 ]  Unit:''     

  uint8_t alive_counter;                    //      Bits=04.  [ 0     , 15     ]  Unit:''  
} INFO_PANEL_t;

// def @CPU_HW CAN Message (1)
#define CPU_HW_IDE (0U)
#define CPU_HW_DLC (5U)
#define CPU_HW_CANID (0x1U)
typedef struct
{

  uint16_t cpuFrequency;                    //      Bits=12.  [ 0     , 4095   ]  Unit:''     

  uint8_t cpuPowerDrawPackage;              //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t cpuTemp;                          //      Bits=08.  [ 0     , 255    ]  Unit:''     

  uint8_t cpuUsage;                         //      Bits=08.  [ 0     , 255    ]  Unit:''     
} CPU_HW_t;

uint32_t Unpack_GPU_HW_hwMonitor(GPU_HW_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_GPU_HW_hwMonitor(const GPU_HW_t* _m, uint8_t* _d);
uint32_t Unpack_RAM_HDD_HW_hwMonitor(RAM_HDD_HW_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_RAM_HDD_HW_hwMonitor(const RAM_HDD_HW_t* _m, uint8_t* _d);
uint32_t Unpack_INFO_PC_hwMonitor(INFO_PC_t *_m, const uint8_t *_d, uint8_t dlc_);
uint32_t Pack_INFO_PC_hwMonitor(const INFO_PC_t *_m, uint8_t *_d);
uint32_t Unpack_INFO_PANEL_hwMonitor(INFO_PANEL_t *_m, const uint8_t *_d, uint8_t dlc_);
uint32_t Pack_INFO_PANEL_hwMonitor(const INFO_PANEL_t *_m, uint8_t *_d);
uint32_t Unpack_CPU_HW_hwMonitor(CPU_HW_t* _m, const uint8_t* _d, uint8_t dlc_);
uint32_t Pack_CPU_HW_hwMonitor(const CPU_HW_t* _m, uint8_t* _d);

#ifdef __cplusplus
}
#endif
