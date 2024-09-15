/*
 * @Description: LVGL
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-09-22 11:59:37
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-03-01 11:16:00
 * @License: GPL 3.0
 */
// #define TOUCH_MODULES_GT911
// #define TOUCH_MODULES_CST_SELF
#define TOUCH_MODULES_CST_MUTUAL
// #define TOUCH_MODULES_ZTW622
// #define TOUCH_MODULES_L58
// #define TOUCH_MODULES_FT3267
// #define TOUCH_MODULES_FT5x06
#include "lvgl.h"
#include "Arduino_GFX_Library.h"
#include "pin_config.h"
#include "TouchLib.h"

#include "ui/ui.h"
#include "ui/vars.h"
#include "ui/screens.h"

#include "driver/twai.h"
#include "dbc/t_panel_hw_monitor_binUtil.h"
#include "dbc/t_panel_hw_monitor.h"

#include <WiFi.h>
#include <WiFiUdp.h>

#define LVGL_TICK_INTERVAL_MS 5
#define UDP_TICK_INTERVAL_MS 1000
#define CAN_TICK_INTERVAL_MS 500

#define UDP_PORT 12345

void lvglUpdate(void *pvParameters);
TaskHandle_t lvglUpdateTask;
void udpUpdate(void *pvParameters);
TaskHandle_t udpUpdateTask;
void canUpdate(void *pvParameters);
TaskHandle_t canUpdateTask;

static bool Touch_Int_Flag = false;
static bool driver_installed = false;
static bool toggle_can = false;
    
// Check if alert happened
uint32_t alerts_triggered;

// UDP
WiFiUDP udp;
const char *ssid = "";        // Replace with your WiFi SSID
const char *password = ""; // Replace with your WiFi password

uint8_t cpuTempUdp = 0;
uint8_t cpuUsageUdp = 0;
uint8_t cpuPowerDrawPackageUdp = 0;
uint16_t cpuFrequencyUdp = 0;
uint8_t gpuTempUdp = 0;
uint8_t gpuUsageUdp = 0;
uint16_t gpuCoreFrequencyUdp = 0;
uint16_t gpuMemoryFrequencyUdp = 0;
uint8_t ramUsageUdp = 0;
uint8_t hddUsage_0Udp = 0;
uint8_t hddUsage_1Udp = 0;
uint8_t hddUsage_2Udp = 0;

uint8_t alive_counter = 0;

TouchLib touch(Wire, TOUCH_SDA, TOUCH_SCL, CST3240_ADDRESS);

Arduino_DataBus *bus = new Arduino_XL9535SWSPI(IIC_SDA /* SDA */, IIC_SCL /* SCL */, -1 /* XL PWD */,
                                               XL95X5_CS /* XL CS */, XL95X5_SCLK /* XL SCK */, XL95X5_MOSI /* XL MOSI */);
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    -1 /* DE */, LCD_VSYNC /* VSYNC */, LCD_HSYNC /* HSYNC */, LCD_PCLK /* PCLK */,
    LCD_B0 /* B0 */, LCD_B1 /* B1 */, LCD_B2 /* B2 */, LCD_B3 /* B3 */, LCD_B4 /* B4 */,
    LCD_G0 /* G0 */, LCD_G1 /* G1 */, LCD_G2 /* G2 */, LCD_G3 /* G3 */, LCD_G4 /* G4 */, LCD_G5 /* G5 */,
    LCD_R0 /* R0 */, LCD_R1 /* R1 */, LCD_R2 /* R2 */, LCD_R3 /* R3 */, LCD_R4 /* R4 */,
    1 /* hsync_polarity */, 20 /* hsync_front_porch */, 2 /* hsync_pulse_width */, 0 /* hsync_back_porch */,
    1 /* vsync_polarity */, 30 /* vsync_front_porch */, 8 /* vsync_pulse_width */, 1 /* vsync_back_porch */,
    10 /* pclk_active_neg */, 6000000L /* prefer_speed */, false /* useBigEndian */,
    0 /* de_idle_high*/, 0 /* pclk_idle_high */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */, rgbpanel, 2 /* rotation */, true /* auto_flush */,
    bus, -1 /* RST */, st7701_type9_init_operations, sizeof(st7701_type9_init_operations));

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

void setupWiFi()
{
    // Connect to Wi-Fi
    WiFi.mode(WIFI_MODE_STA);
    WiFi.setSleep(false); // Disable Wi-Fi power-saving mode
    WiFi.begin(ssid, password);
    int timeout = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(50);
        Serial.print(".");
        timeout++;
        if (timeout > 2000)
        {
            Serial.print("ESP.restart");
            ESP.restart(); // Reset the ESP32 if not connected within the timeout
        }
    }

    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
    // gfx->print(WiFi.localIP());

    // Initialize UDP
    udp.begin(UDP_PORT);
    Serial.println("udp.begin");
}

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}
/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (Touch_Int_Flag == true)
    {
        Touch_Int_Flag = false;

        touch.read();
        if (touch.getPointNum() > 0)
        {
            TP_Point t = touch.getPoint(0);

            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = t.x;
            data->point.y = t.y;

            // Serial.print("Data x ");
            // Serial.printf("%d\n", x[0]);

            // Serial.print("Data y ");
            // Serial.printf("%d\n", y[0]);
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void lvgl_initialization(void)
{
    lv_init();

    uint32_t screen_width = gfx->width();
    uint32_t screen_height = gfx->height();

    // PSRAM
    lv_color_t *buf_1 = (lv_color_t *)heap_caps_malloc(48 * 1024, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    lv_color_t *buf_2 = (lv_color_t *)heap_caps_malloc(48 * 1024, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    while ((!buf_1) || (!buf_2))
    {
        // Serial.println("LVGL disp_draw_buf allocate failed!");
        delay(1000);
    }

    // lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, 48 * 1024 * 2);
    lv_disp_draw_buf_init(&draw_buf, buf_1, NULL, 48 * 1024);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screen_width;
    disp_drv.ver_res = screen_height;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = 1; // 双缓冲全像素刷新
    // disp_drv.rotated = LV_DISP_ROT_180;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

void CAN_Drive_Initialization()
{
    // Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX, (gpio_num_t)CAN_RX, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    g_config.tx_queue_len = 10;
    g_config.rx_queue_len = 10;
    // gpio_pulldown_en((gpio_num_t)CAN_RX);

    // Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
    {
        Serial.println("Driver installed");
    }
    else
    {
        Serial.println("Failed to install driver");
        return;
    }

    // Start TWAI driver
    if (twai_start() == ESP_OK)
    {
        Serial.println("Driver started");
    }
    else
    {
        Serial.println("Failed to start driver");
        return;
    }

    uint32_t alerts_to_enable = TWAI_ALERT_TX_IDLE | TWAI_ALERT_TX_SUCCESS |
                                TWAI_ALERT_TX_FAILED | TWAI_ALERT_ERR_PASS |
                                TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_DATA |
                                TWAI_ALERT_RX_QUEUE_FULL;
    if (twai_reconfigure_alerts(alerts_to_enable, NULL) == ESP_OK)
    {
        Serial.println("CAN Alerts reconfigured");
    }
    else
    {
        Serial.println("Failed to reconfigure alerts");
        return;
    }

    // TWAI driver is now successfully installed and started
    driver_installed = true;
}

void Twai_Send_Message()
{
    /* CPU */
    CPU_HW_t CPU_HW;
    twai_message_t CPU_HW_TWAI;

    CPU_HW.cpuFrequency = cpuFrequencyUdp;
    CPU_HW.cpuPowerDrawPackage = cpuPowerDrawPackageUdp;
    CPU_HW.cpuTemp = cpuTempUdp;
    CPU_HW.cpuUsage = cpuUsageUdp;

    CPU_HW_TWAI.identifier = CPU_HW_CANID;
    CPU_HW_TWAI.data_length_code = CPU_HW_DLC;
    CPU_HW_TWAI.flags = TWAI_MSG_FLAG_NONE;
    Pack_CPU_HW_hwMonitor(&CPU_HW, CPU_HW_TWAI.data);
    twai_transmit(&CPU_HW_TWAI, pdMS_TO_TICKS(1));

    /* GPU */
    GPU_HW_t GPU_HW;
    twai_message_t GPU_HW_TWAI;

    GPU_HW.gpuCoreFrequency = gpuCoreFrequencyUdp;
    GPU_HW.gpuMemoryFrequency = gpuMemoryFrequencyUdp;
    GPU_HW.gpuTemp = gpuTempUdp;
    GPU_HW.gpuUsage = gpuUsageUdp;

    GPU_HW_TWAI.identifier = GPU_HW_CANID;
    GPU_HW_TWAI.data_length_code = GPU_HW_DLC;
    GPU_HW_TWAI.flags = TWAI_MSG_FLAG_NONE;
    Pack_GPU_HW_hwMonitor(&GPU_HW, GPU_HW_TWAI.data);
    twai_transmit(&GPU_HW_TWAI, pdMS_TO_TICKS(1));

    /* RAM_HDD */
    RAM_HDD_HW_t RAM_HDD_HW;
    twai_message_t RAM_HDD_HW_TWAI;

    RAM_HDD_HW.ramUsage = ramUsageUdp;
    RAM_HDD_HW.hddUsage_0 = hddUsage_0Udp;
    RAM_HDD_HW.hddUsage_1 = hddUsage_1Udp;
    RAM_HDD_HW.hddUsage_2 = hddUsage_2Udp;

    RAM_HDD_HW_TWAI.identifier = RAM_HDD_HW_CANID;
    RAM_HDD_HW_TWAI.data_length_code = RAM_HDD_HW_DLC;
    RAM_HDD_HW_TWAI.flags = TWAI_MSG_FLAG_NONE;
    Pack_RAM_HDD_HW_hwMonitor(&RAM_HDD_HW, RAM_HDD_HW_TWAI.data);
    twai_transmit(&RAM_HDD_HW_TWAI, pdMS_TO_TICKS(1));

    /* INFO */
    INFO_PANEL_t INFO_PANEL;
    twai_message_t INFO_TWAI;

    INFO_PANEL.alive_counter = alive_counter;
    alive_counter = (alive_counter + 1) % 16;
    INFO_PANEL.INFO_ALIVE_PANEL = strtoul(lv_label_get_text(objects.sys_ticks), NULL, 10);

    INFO_TWAI.identifier = INFO_PANEL_CANID;
    INFO_TWAI.data_length_code = INFO_PANEL_DLC;
    INFO_TWAI.flags = TWAI_MSG_FLAG_NONE;
    Pack_INFO_PANEL_hwMonitor(&INFO_PANEL, INFO_TWAI.data);
    twai_transmit(&INFO_TWAI, pdMS_TO_TICKS(1));
}

void Twai_Receive_Message(void)
{
    hwMonitor_rx_t hwMonitor_rcvBuff;
    twai_message_t message_rx;
    message_rx.flags = TWAI_MSG_FLAG_NONE;

    if (alerts_triggered & TWAI_ALERT_RX_DATA)
    {
        if (twai_receive(&message_rx, pdMS_TO_TICKS(0)) == ESP_OK)
        {
            switch (message_rx.identifier)
            {
            case INFO_PC_CANID:
                INFO_PC_t INFO_PC;
                Unpack_INFO_PC_hwMonitor(&INFO_PC, message_rx.data, INFO_PC_DLC);
                //if (INFO_PC.INFO_ALIVE_PC >= 0 && INFO_PC.INFO_ALIVE_PC <= 255)
                //    lv_led_set_brightness(objects.led_comm_can, INFO_PC.INFO_ALIVE_PC);
                // Serial.println(INFO_PC.INFO_ALIVE_PC);
                // update_label(objects., INFO_PC.INFO_ALIVE_PC);
                break;
            default:
                break;
            }
        }
    }
}

void parseUDPData(const String &data)
{
    // Split the data string by commas
    int index = 0;
    String tempStr = "";
    String tempData = data;

    while (tempData.length() > 0)
    {
        int commaIndex = tempData.indexOf('|');
        if (commaIndex == -1)
        {
            commaIndex = tempData.length();
        }

        tempStr = tempData.substring(0, commaIndex);
        tempData = tempData.substring(commaIndex + 1);

        int32_t value = tempStr.toInt();

        switch (index)
        {
        case 0:
            cpuTempUdp = value;
            break;
        case 1:
            cpuUsageUdp = value;
            break;
        case 2:
            cpuPowerDrawPackageUdp = value;
            break;
        case 3:
            cpuFrequencyUdp = value;
            break;
        case 4:
            gpuTempUdp = value;
            break;
        case 5:
            gpuUsageUdp = value;
            break;
        case 6:
            gpuCoreFrequencyUdp = value;
            break;
        case 7:
            gpuMemoryFrequencyUdp = value;
            break;
        case 8:
            ramUsageUdp = value;
            break;
        case 9:
            hddUsage_0Udp = value;
            break;
        case 10:
            hddUsage_1Udp = value;
            break;
        case 11:
            hddUsage_2Udp = value;
            break;
        default:
            break;
        }
        index++;
    }
}

void Udp_ReceiveParse(void)
{
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
        char packetBuffer[255];
        int len = udp.read(packetBuffer, 255);
        if (len > 0)
        {
            packetBuffer[len] = 0; // Null-terminate the packet buffer
        }
        String data(packetBuffer);
        // Parse the received data
        parseUDPData(data);

        check_active_screen();
    }
}

void parseSerialData(const String &data)
{
    // Split the data string by commas
    int index = 0;
    String tempStr = "";
    String tempData = data;

    while (tempData.length() > 0)
    {
        int commaIndex = tempData.indexOf('|');
        if (commaIndex == -1)
        {
            commaIndex = tempData.length();
        }

        tempStr = tempData.substring(0, commaIndex);
        tempData = tempData.substring(commaIndex + 1);

        int32_t value = tempStr.toInt();

        switch (index)
        {
        case 0:
            cpuTempUdp = value;
            break;
        case 1:
            cpuUsageUdp = value;
            break;
        case 2:
            cpuPowerDrawPackageUdp = value;
            break;
        case 3:
            cpuFrequencyUdp = value;
            break;
        case 4:
            gpuTempUdp = value;
            break;
        case 5:
            gpuUsageUdp = value;
            break;
        case 6:
            gpuCoreFrequencyUdp = value;
            break;
        case 7:
            gpuMemoryFrequencyUdp = value;
            break;
        default:
            break;
        }
        index++;
    }
}

void Serial_ReceiveParse(void)
{
    static bool toggle_uart = false;

    // Check if data is available on the serial port
    if (Serial.available() > 0)
    {
        lv_led_set_brightness(objects.led_comm_uart, toggle_uart ? 255 : 0);
        toggle_uart = !toggle_uart;
        // Read the incoming data into a string
        String receivedData = Serial.readStringUntil('\n'); // Read until newline character

        // Parse the received data
        parseSerialData(receivedData);

        check_active_screen();

        // Print the parsed values for verification
        /*
        Serial.print("CPU Temp: ");
        Serial.println(cpuTemp);
        Serial.print("CPU Usage: ");
        Serial.println(cpuUsage);
        Serial.print("CPU Power Draw (Package): ");
        Serial.println(cpuPowerDrawPackage);
        Serial.print("CPU Frequency: ");
        Serial.println(cpuFrequency);
        Serial.print("GPU Temp: ");
        Serial.println(gpuTemp);
        Serial.print("GPU Usage: ");
        Serial.println(gpuUsage);
        Serial.print("GPU Core Frequency: ");
        Serial.println(gpuCoreFrequency);
        Serial.print("GPU Memory Frequency: ");
        Serial.println(gpuMemoryFrequency);
        */
    }
}

void update_label(lv_obj_t *label, int value)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%d", value);
    lv_label_set_text(label, buf);
}

void update_label_text(lv_obj_t *label, int value, const char *pre_text, const char *pos_text)
{
    char buf[128];
    snprintf(buf, sizeof(buf), "%s%d%s", pre_text, value, pos_text);
    lv_label_set_text(label, buf);
}

void check_active_screen()
{
    // Get the currently active screen
    lv_obj_t *active_screen = lv_scr_act();

    if (active_screen == objects.main)
    {
        /* CPU */
        update_label_text(objects.t1_cpu_temp, cpuTempUdp, "", "C");
        update_label_text(objects.t1_cpu_usage, cpuUsageUdp, "", "%");
        update_label_text(objects.t1_cpu_power, cpuPowerDrawPackageUdp, "", "W");
        update_label_text(objects.t1_cpu_frequency, cpuFrequencyUdp, "", "MHz");

        lv_bar_set_value(objects.t2_temp_bar, cpuTempUdp, LV_ANIM_ON);
        update_label_text(objects.t2_temp_label, cpuTempUdp, "", " °C");
        lv_bar_set_value(objects.t2_clock_bar, cpuFrequencyUdp, LV_ANIM_ON);
        update_label_text(objects.t2_clock_label, cpuFrequencyUdp, "", " MHz");

        update_label_text(objects.t1_cpu_temp_1, cpuTempUdp, "", "C");
        update_label_text(objects.t1_cpu_usage_1, cpuUsageUdp, "", "%");
        update_label_text(objects.t1_cpu_power_1, cpuPowerDrawPackageUdp, "", "W");
        update_label_text(objects.t1_cpu_frequency_1, cpuFrequencyUdp, "", "MHz");

        /* GPU */
        update_label_text(objects.t1_gpu_temp, gpuTempUdp, "", "C");
        update_label_text(objects.t1_gpu_usage, gpuUsageUdp, "", "%");
        update_label_text(objects.t1_gpu_core_frequency, gpuCoreFrequencyUdp, "", "MHz");
        update_label_text(objects.t1_gpu_memory_freq, gpuMemoryFrequencyUdp, "", "MHz");

        lv_bar_set_value(objects.t3_temp_bar, gpuTempUdp, LV_ANIM_ON);
        update_label_text(objects.t3_temp_label, gpuTempUdp, "", " °C");
        lv_bar_set_value(objects.t3_clock_bar, gpuUsageUdp, LV_ANIM_ON);
        update_label_text(objects.t3_clock_label, gpuCoreFrequencyUdp, "", " MHz");

        update_label_text(objects.t1_gpu_temp_1, gpuTempUdp, "", "C");
        update_label_text(objects.t1_gpu_usage_1, gpuUsageUdp, "", "%");
        update_label_text(objects.t1_gpu_core_frequency_1, gpuCoreFrequencyUdp, "", "MHz");
        update_label_text(objects.t1_gpu_memory_freq_1, gpuMemoryFrequencyUdp, "", "MHz");

        /* RAM */
        update_label_text(objects.t1_ram_usage, ramUsageUdp, "", "%");

        update_label_text(objects.t4_ram_usage, ramUsageUdp, "", "%");

        /* HDD */
        update_label_text(objects.t1_hdd_usage0, hddUsage_0Udp, "", "%");
        update_label_text(objects.t1_hdd_usage1, hddUsage_1Udp, "", "%");
        update_label_text(objects.t1_hdd_usage2, hddUsage_2Udp, "", "%");

        update_label_text(objects.t4_hdd_usage0, hddUsage_0Udp, "", "%");
        update_label_text(objects.t4_hdd_usage1, hddUsage_1Udp, "", "%");
        update_label_text(objects.t4_hdd_usage2, hddUsage_2Udp, "", "%");
    }
    else if (active_screen == objects.main)
    {
        // update_label(objects.t2_cpu_usage, cpuUsage);
    }
    else
    {
        printf("Unknown screen is active.\n");
    }
}

void checkPSRAM()
{
    Serial.print(F("Total heap  "));
    Serial.println(ESP.getHeapSize());
    Serial.print(F("Free heap   "));
    Serial.println(ESP.getFreeHeap());
    Serial.print(F("Total psram "));
    Serial.println(ESP.getPsramSize());
    Serial.print(F("Free psram  "));
    Serial.println(ESP.getFreePsram());
    Serial.println(F(" "));
}

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);

    // Connect to Wi-Fi
    setupWiFi();

    CAN_Drive_Initialization();

    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, HIGH);

    attachInterrupt(
        TOUCH_INT,
        []
        {
            Touch_Int_Flag = true;
        },
        FALLING); // Triggered every 1ms

    Wire.begin(IIC_SDA, IIC_SCL);
    Serial.println("Wire.begin");

    gfx->begin();
    gfx->fillScreen(BLACK);
    gfx->setRotation(0);

    gfx->XL_digitalWrite(TOUCH_RST, LOW);
    delay(200);
    gfx->XL_digitalWrite(TOUCH_RST, HIGH);
    delay(200);
    Serial.println("gfx->begin");

    touch.init();
    Serial.println("touch.begin");

    lvgl_initialization();
    Serial.println("lvgl.begin");

    ui_init();
    Serial.println("ui.begin");

    checkPSRAM();

    // lv_timer_t *timer = lv_timer_create(SerialParse, 5000, NULL);

    xTaskCreatePinnedToCore(
        lvglUpdate,      // Function to implement the task
        "lvglUpdate",    // Name of the task
        9216,            // Stack size in bytes
        NULL,            // Task input parameter
        7,              // Priority of the task
        &lvglUpdateTask, // Task handle.
        1                // Core where the task should run
    );

    xTaskCreatePinnedToCore(
        udpUpdate,      // Function to implement the task
        "udpUpdate",    // Name of the task
        9216,           // Stack size in bytes
        NULL,           // Task input parameter
        1,              // Priority of the task
        &udpUpdateTask, // Task handle.
        1               // Core where the task should run
    );

    xTaskCreatePinnedToCore(
        canUpdate,      // Function to implement the task
        "canUpdate",    // Name of the task
        9216,           // Stack size in bytes
        NULL,           // Task input parameter
        5,              // Priority of the task
        &canUpdateTask, // Task handle.
        1               // Core where the task should run
    );
}

void loop()
{
#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif
}

void lvglUpdate(void *pvParameters)
{
    // Get the IP address as a string
    String ipAddress = WiFi.localIP().toString();
    // Convert String to a C-style string for LVGL
    const char *ipChar = ipAddress.c_str();
    lv_label_set_text(objects.ip_text, ipChar);

    for (;;)
    {
        lv_timer_handler();
        ui_tick();

        // lv_led_set_brightness(objects.led_comm_can, toggle_can ? 255 : 0);

        // Delay to control the loop frequency
        vTaskDelay(pdMS_TO_TICKS(LVGL_TICK_INTERVAL_MS));
    }
}

void udpUpdate(void *pvParameters)
{
    static bool toggle_udp = false;

    for (;;)
    {
        Udp_ReceiveParse();

        // lv_led_set_brightness(objects.led_comm_udp, toggle_udp ? 255 : 0);
        // toggle_udp = !toggle_udp;

        // Delay to control the loop frequency
        vTaskDelay(pdMS_TO_TICKS(UDP_TICK_INTERVAL_MS));
    }
}

void canUpdate(void *pvParameters)
{
    for (;;)
    {
        if (driver_installed)
        {
            twai_read_alerts(&alerts_triggered, pdMS_TO_TICKS(2));
            twai_status_info_t twaistatus;
            twai_get_status_info(&twaistatus);

            Twai_Receive_Message();
            Twai_Send_Message();

            // toggle_can = !toggle_can;
        }

        // Delay to control the loop frequency
        vTaskDelay(pdMS_TO_TICKS(CAN_TICK_INTERVAL_MS));
    }
}

// Function that will be called by the LVGL task
void SerialParse(lv_timer_t *timer)
{
    Serial.println("lv_timer_t: SerialParse");
}