#include "Arduino.h"
#include "srv_sys_os_freertos.h"
#include "ecu_modules.h"

//=============================================================================
// Task modules declarations
//-----------------------------------------------------------------------------

// Control modules
void ctrl_air_hum_task(void *pvParameters);
void ctrl_air_press_task(void *pvParameters);
void ctrl_amb_light_task(void *pvParameters);
void ctrl_servo_adc_dc_task(void *pvParameters);
void ctrl_soil_moist_task(void *pvParameters);
void ctrl_air_temp_heat_task(void *pvParameters);
void ctrl_air_temp_vent_task(void *pvParameters);
void ctrl_can_steer_task(void *pvParameters);
void ctrl_wheel_steer_task(void *pvParameters);
void ctrl_wheel_tract_task(void *pvParameters);

//-----------------------------------------------------------------------------
// Device Abstraction components
void dd_air_pump_task(void *pvParameters);
void dd_dc_motor_task(void *pvParameters);
void dd_heater_task(void *pvParameters);
void dd_joystick_task(void *pvParameters);
void dd_lights_task(void *pvParameters);
void dd_valve_task(void *pvParameters);
void dd_water_pump_task(void *pvParameters);
void dd_window_task(void *pvParameters);

//-----------------------------------------------------------------------------
// ECU modules
void ed_bh1750_task(void *pvParameters);
void ed_bmp_task(void *pvParameters);
void ed_buzzer_task(void *pvParameters);
void ed_can_mcp_task(void *pvParameters);
void ed_contact_task(void *pvParameters);
void ed_dc_esc_task(void *pvParameters);
void ed_dht_task(void *pvParameters);
void ed_encoder_task(void *pvParameters);
void ed_l298_task(void *pvParameters);
void ed_relay_task(void *pvParameters);
void ed_servo_task(void *pvParameters);
void ed_sns_soil_moist_task(void *pvParameters);

//-----------------------------------------------------------------------------
// Service modules
void srv_com_can_task(void *pvParameters);
void srv_com_lora_task(void *pvParameters);
void srv_com_modbus_task(void *pvParameters);
void srv_com_mqtt_task(void *pvParameters);
void srv_control_task(void *pvParameters);
void srv_heartbeat_task(void *pvParameters);

// Sensor modules
void srv_sns_air_hum_task(void *pvParameters);
void srv_sns_air_press_task(void *pvParameters);
void srv_sns_air_temp_task(void *pvParameters);
void srv_sns_amb_light_task(void *pvParameters);
void srv_sns_soil_moist_task(void *pvParameters);

// Service modules
void srv_ui_bt_task(void *pvParameters);
void srv_ui_lcd_task(void *pvParameters);
void srv_ui_serial_out_task(void *pvParameters);
void srv_ui_serial_in_task(void *pvParameters);

//=============================================================================
// Task modules initialization
//-----------------------------------------------------------------------------
// the setup function runs once when you press reset or power the board
void srv_sys_os_freertos_setup()
{
    // Set up Tasks to run independently.

//---------------------------------------------------------------------------------------------
// Control modules
#ifdef USE_CTRL_AIR_HUM
    xTaskCreate(ctrl_air_hum_task, "ctrl_air_hum_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
    xTaskCreate(ctrl_air_press_task, "ctrl_air_press_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AMB_LIGHT
    xTaskCreate(ctrl_amb_light_task, "ctrl_amb_light_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
    xTaskCreate(ctrl_servo_adc_dc_task, "ctrl_servo_adc_dc_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
    xTaskCreate(ctrl_soil_moist_task, "ctrl_soil_moist_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_HEAT
    xTaskCreate(ctrl_air_temp_heat_task, "ctrl_air_temp_heat_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_VENT
    xTaskCreate(ctrl_air_temp_vent_task, "ctrl_air_temp_vent_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_CAN_STEER
    xTaskCreate(ctrl_can_steer_task, "ctrl_can_steer_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
    xTaskCreate(ctrl_wheel_steer_task, "ctrl_wheel_steer_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
    xTaskCreate(ctrl_wheel_tract_task, "ctrl_wheel_tract_task", 1024, NULL, 1, NULL);
#endif
//=============================================================================
// Device abstraction modules
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
    xTaskCreate(dd_air_pump_task, "dd_air_pump_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
    xTaskCreate(dd_dc_motor_task, "dd_dc_motor_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
    xTaskCreate(dd_heater_task, "dd_heater_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
    xTaskCreate(dd_joystick_task, "dd_joystick_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
    xTaskCreate(dd_lights_task, "dd_lights_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
    xTaskCreate(dd_valve_task, "dd_valve_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
    xTaskCreate(dd_water_pump_task, "dd_water_pump_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
    xTaskCreate(dd_window_task, "dd_window_task", 1024, NULL, 1, NULL);
#endif

//=============================================================================
// ECU abstraction modules
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
    xTaskCreate(ed_bh1750_task, "ed_bh1750_task", 2048, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
    xTaskCreate(ed_bmp_task, "ed_bmp_task", 4096, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
    xTaskCreate(ed_buzzer_task, "ed_buzzer_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
    xTaskCreate(ed_can_mcp_task, "ed_can_mcp_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
    xTaskCreate(ed_contact_task, "ed_contact_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
    xTaskCreate(ed_dc_esc_task, "ed_dc_esc_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
    xTaskCreate(ed_dht_task, "ed_dht_task", 2048, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
    xTaskCreate(ed_encoder_task, "ed_encoder_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
    xTaskCreate(ed_l298_task, "ed_l298_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
    xTaskCreate(ed_relay_task, "ed_relay_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
    xTaskCreate(ed_servo_task, "ed_servo_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
    xTaskCreate(ed_sns_soil_moist_task, "ed_sns_soil_moist_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------

//=============================================================================
// Service modules
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
    xTaskCreate(srv_com_can_task, "srv_com_can_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
    xTaskCreate(srv_com_lora_task, "srv_com_lora_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
    xTaskCreate(srv_com_modbus_task, "srv_com_modbus_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
    xTaskCreate(srv_com_mqtt_task, "srv_com_mqtt_task", 4096, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
    xTaskCreate(srv_control_task, "srv_control_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
    xTaskCreate(srv_heartbeat_task, "srv_heartbeat_task" ,2048 , NULL, 1, NULL);
#endif

//-----------------------------------------------------------------------------
// Sensor service modules
#ifdef USE_SRV_SNS_AIR_HUM
    xTaskCreate(srv_sns_air_hum_task, "srv_sns_air_hum_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
    xTaskCreate(srv_sns_air_press_task, "srv_sns_air_press_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
    xTaskCreate(srv_sns_air_temp_task, "srv_sns_air_temp_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
    xTaskCreate(srv_sns_amb_light_task, "srv_sns_amb_light_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
    xTaskCreate(srv_sns_soil_moist_task, "srv_sns_soil_moist_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
    xTaskCreate(srv_ui_bt_task, "srv_ui_bt_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
    xTaskCreate(srv_ui_lcd_task, "srv_ui_lcd_task", 1024, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
    xTaskCreate(srv_ui_serial_out_task, "srv_ui_serial_out_task", 4096, NULL, 1, NULL);
    xTaskCreate(srv_ui_serial_in_task, "srv_ui_serial_in_task", 2048, NULL, 1, NULL);
#endif
//-----------------------------------------------------------------------------

    // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

//=============================================================================
// Task modules declarations
//-----------------------------------------------------------------------------
// Control modules
//-----------------------------------------------------------------------------
// Task for air humidity control
#ifdef USE_CTRL_AIR_HUM
void ctrl_air_hum_task(void *pvParameters)
{
    ctrl_air_hum_setup();
    vTaskDelay(CTRL_AIR_HUM_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_air_hum_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AIR_HUM_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for pressure control with isolation
#ifdef USE_CTRL_AIR_PRESS
void ctrl_air_press_task(void *pvParameters)
{
    ctrl_air_press_setup();
    vTaskDelay(CTRL_AIR_PRESS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_air_press_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AIR_PRESS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for light control
#ifdef USE_CTRL_AMB_LIGHT
void ctrl_amb_light_task(void *pvParameters)
{
    ctrl_amb_light_setup();
    vTaskDelay(CTRL_AMB_LIGHT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_amb_light_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AMB_LIGHT_REC / portTICK_PERIOD_MS);
    }
}
#endif
//-----------------------------------------------------------------------------
// Task for CTRL_SERVO_ADC_DC
#ifdef USE_CTRL_SERVO_ADC_DC
void ctrl_servo_adc_dc_task(void *pvParameters)
{
    ctrl_servo_adc_dc_setup();
    vTaskDelay(CTRL_SERVO_ADC_DC_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_servo_adc_dc_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_SERVO_ADC_DC_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for soil moisture control
#ifdef USE_CTRL_SOIL_MOIST
void ctrl_soil_moist_task(void *pvParameters)
{
    ctrl_soil_moist_setup();
    vTaskDelay(CTRL_SOIL_MOIST_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_SOIL_MOIST_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for temperature control with heater
#ifdef USE_CTRL_AIR_TEMP_HEAT
void ctrl_air_temp_heat_task(void *pvParameters)
{
    ctrl_air_temp_heat_setup();
    vTaskDelay(CTRL_AIR_TEMP_HEAT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_air_temp_heat_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AIR_TEMP_HEAT_REC / portTICK_PERIOD_MS);
    }
}
#endif
//-----------------------------------------------------------------------------
// Task for temperature control with ventilation`
#ifdef USE_CTRL_AIR_TEMP_VENT
void ctrl_air_temp_vent_task(void *pvParameters)
{
    ctrl_air_temp_vent_setup();
    vTaskDelay(CTRL_AIR_TEMP_VENT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_air_temp_vent_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_AIR_TEMP_VENT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//=============================================================================
// Service modules
//-----------------------------------------------------------------------------
// Task for CTRL_CAN_STEER
#ifdef USE_CTRL_CAN_STEER
void ctrl_can_steer_task(void *pvParameters)
{
    ctrl_can_steer_setup();
    vTaskDelay(CTRL_CAN_STEER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_can_steer_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_CAN_STEER_REC / portTICK_PERIOD_MS);
    }
}
#endif


//-----------------------------------------------------------------------------
// Task for CTRL_WHEEL_STEER
#ifdef USE_CTRL_WHEEL_STEER
void ctrl_wheel_steer_task(void *pvParameters)
{
    ctrl_wheel_steer_setup();
    vTaskDelay(CTRL_WHEEL_STEER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_wheel_steer_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_WHEEL_STEER_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for CTRL_WHEEL_TRACT
#ifdef USE_CTRL_WHEEL_TRACT
void ctrl_wheel_tract_task(void *pvParameters)
{
    ctrl_wheel_tract_setup();
    vTaskDelay(CTRL_WHEEL_TRACT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ctrl_wheel_tract_loop();
        vTaskDelayUntil(&xLastWakeTime, CTRL_WHEEL_TRACT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//=============================================================================
// Device abstraction modules
//-----------------------------------------------------------------------------
// Task for managing the air pump
#ifdef USE_DD_AIR_PUMP
void dd_air_pump_task(void *pvParameters)
{
    dd_air_pump_setup();
    vTaskDelay(DD_AIR_PUMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_air_pump_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_AIR_PUMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for DD_DC_MOTOR
#ifdef USE_DD_DC_MOTOR
void dd_dc_motor_task(void *pvParameters)
{
    dd_dc_motor_setup();
    vTaskDelay(DD_DC_MOTOR_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_dc_motor_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_DC_MOTOR_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the heater
#ifdef USE_DD_HEATER
void dd_heater_task(void *pvParameters)
{
    dd_heater_setup();
    vTaskDelay(DD_HEATER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_heater_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_HEATER_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for DD_JOYSTICK
#ifdef USE_DD_JOYSTICK
void dd_joystick_task(void *pvParameters)
{
    dd_joystick_setup();
    vTaskDelay(DD_JOYSTICK_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_joystick_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_JOYSTICK_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the lights
#ifdef USE_DD_LIGHTS
void dd_lights_task(void *pvParameters)
{
    dd_lights_setup();
    vTaskDelay(DD_LIGHTS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_lights_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_LIGHTS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the valve
#ifdef USE_DD_VALVE
void dd_valve_task(void *pvParameters)
{
    dd_valve_setup();
    vTaskDelay(DD_VALVE_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_valve_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_VALVE_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the water pump
#ifdef USE_DD_WATER_PUMP
void dd_water_pump_task(void *pvParameters)
{
    dd_water_pump_setup();
    vTaskDelay(DD_WATER_PUMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_water_pump_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_WATER_PUMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the windows
#ifdef USE_DD_WINDOW
void dd_window_task(void *pvParameters)
{
    dd_window_setup();
    vTaskDelay(DD_WINDOW_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        dd_window_loop();
        vTaskDelayUntil(&xLastWakeTime, DD_WINDOW_REC / portTICK_PERIOD_MS);
    }
}
#endif

//=============================================================================
// ECU modules
//-----------------------------------------------------------------------------
// Task for collecting data from the BH1750 sensor
#ifdef USE_ED_BH1750
void ed_bh1750_task(void *pvParameters)
{
    ed_bh1750_setup();
    vTaskDelay(ED_BH1750_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_bh1750_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_BH1750_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the BMP sensor
#ifdef USE_ED_BMP
void ed_bmp_task(void *pvParameters)
{
    ed_bmp_setup();
    vTaskDelay(ED_BMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_bmp_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_BMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for ED_BUZZER
#ifdef USE_ED_BUZZER
void ed_buzzer_task(void *pvParameters)
{
    ed_buzzer_setup();
    vTaskDelay(ED_BUZZER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_buzzer_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_BUZZER_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for ED_CAN_MCP
#ifdef USE_ED_CAN_MCP
void ed_can_mcp_task(void *pvParameters)
{
    ed_can_mcp_setup();
    vTaskDelay(ED_CAN_MCP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        // ed_can_mcp_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_CAN_MCP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for ED_CONTACT
#ifdef USE_ED_CONTACT
void ed_contact_task(void *pvParameters)
{
    ed_contact_setup();
    vTaskDelay(ED_CONTACT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_contact_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_CONTACT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for ED_DC_ESC
#ifdef USE_ED_DC_ESC
void ed_dc_esc_task(void *pvParameters)
{
    ed_dc_esc_setup();
    vTaskDelay(ED_DC_ESC_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_dc_esc_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_DC_ESC_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the DHT11 sensor
#ifdef USE_ED_DHT
void ed_dht_task(void *pvParameters)
{
    ed_dht_setup();
    vTaskDelay(ED_DHT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_dht_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_DHT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing ED_ENCODER
#ifdef USE_ED_ENCODER
void ed_encoder_task(void *pvParameters)
{
    ed_encoder_setup();
    vTaskDelay(ED_ENCODER_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_encoder_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_ENCODER_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for ED_L298
#ifdef USE_ED_L298
void ed_l298_task(void *pvParameters)
{
    ed_l298_setup();
    vTaskDelay(ED_L298_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_l298_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_L298_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing the relay
#ifdef USE_ED_RELAY
void ed_relay_task(void *pvParameters)
{
    ed_relay_setup();
    vTaskDelay(ED_RELAY_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_relay_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_RELAY_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing ED_SERVO
#ifdef USE_ED_SERVO
void ed_servo_task(void *pvParameters)
{
    ed_servo_setup();
    vTaskDelay(ED_SERVO_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_servo_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_SERVO_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the soil moisture sensor
#ifdef USE_ED_SNS_SOIL_MOIST
void ed_sns_soil_moist_task(void *pvParameters)
{
    ed_sns_soil_moist_setup();
    vTaskDelay(ED_SNS_SOIL_MOIST_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ed_sns_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, ED_SNS_SOIL_MOIST_REC / portTICK_PERIOD_MS);
    }
}
#endif

//=============================================================================
// Service modules
//-----------------------------------------------------------------------------
// Task for managing SRV_COM_CAN
#ifdef USE_SRV_COM_CAN
void srv_com_can_task(void *pvParameters)
{
    // srv_com_can_setup();
    // vTaskDelay(SRV_COM_CAN_OFFSET / portTICK_PERIOD_MS);
    // TickType_t xLastWakeTime = xTaskGetTickCount();

    // for (;;)
    // {
    //     srv_com_can_loop();
    //     vTaskDelayUntil(&xLastWakeTime, SRV_COM_CAN_REC / portTICK_PERIOD_MS);
    // }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing SRV_COM_LORA
#ifdef USE_SRV_COM_LORA
void srv_com_lora_task(void *pvParameters)
{
    srv_com_lora_setup();
    vTaskDelay(SRV_COM_LORA_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_com_lora_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_COM_LORA_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing SRV_COM_MODBUS
#ifdef USE_SRV_COM_MODBUS
void srv_com_modbus_task(void *pvParameters)
{
    srv_com_modbus_setup();
    vTaskDelay(SRV_COM_MODBUS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_com_modbus_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_COM_MODBUS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for handling MQTT communication
#ifdef USE_SRV_COM_MQTT
void srv_com_mqtt_task(void *pvParameters)
{
    srv_com_mqtt_setup();
    vTaskDelay(SRV_COM_MQTT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_com_mqtt_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_COM_MQTT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing SRV_CONTROL
#ifdef USE_SRV_CONTROL
void srv_control_task(void *pvParameters)
{
    srv_control_setup();
    vTaskDelay(SRV_CONTROL_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_control_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_CONTROL_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for periodic reporting HEARTBEAT
#ifdef USE_SRV_HEARTBEAT
void srv_heartbeat_task(void *pvParameters)
{
    srv_heartbeat_setup();
    vTaskDelay(SRV_HEARTBEAT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_heartbeat_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_HEARTBEAT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the air humidity sensor
#ifdef USE_SRV_SNS_AIR_HUM
void srv_sns_air_hum_task(void *pvParameters)
{
    srv_sns_air_hum_setup();
    vTaskDelay(SRV_SNS_AIR_HUM_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_air_hum_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AIR_HUM_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the pressure sensor
#ifdef USE_SRV_SNS_AIR_PRESS
void srv_sns_air_press_task(void *pvParameters)
{
    srv_sns_air_press_setup();
    vTaskDelay(SRV_SNS_AIR_PRESS_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_air_press_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AIR_PRESS_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the air temperature sensor
#ifdef USE_SRV_SNS_AIR_TEMP
void srv_sns_air_temp_task(void *pvParameters)
{
    srv_sns_air_temp_setup();
    vTaskDelay(SRV_SNS_AIR_TEMP_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_air_temp_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AIR_TEMP_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the ambient light sensor
#ifdef USE_SRV_SNS_AMB_LIGHT
void srv_sns_amb_light_task(void *pvParameters)
{
    srv_sns_amb_light_setup();
    vTaskDelay(SRV_SNS_AMB_LIGHT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_amb_light_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_AMB_LIGHT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for collecting data from the soil moisture sensor
#ifdef USE_SRV_SNS_SOIL_MOIST
void srv_sns_soil_moist_task(void *pvParameters)
{
    srv_sns_soil_moist_setup();
    vTaskDelay(SRV_SNS_SOIL_MOIST_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_sns_soil_moist_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_SNS_SOIL_MOIST_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing SRV_UI_BT
#ifdef USE_SRV_UI_BT
void srv_ui_bt_task(void *pvParameters)
{
    srv_ui_bt_setup();
    vTaskDelay(SRV_UI_BT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_bt_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_UI_BT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for managing SRV_UI_LCD
#ifdef USE_SRV_UI_LCD
void srv_ui_lcd_task(void *pvParameters)
{
    srv_ui_lcd_setup();
    vTaskDelay(SRV_UI_LCD_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_lcd_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_UI_LCD_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for periodic reporting of signals in serial terminal
#ifdef USE_SRV_UI_SERIAL
void srv_ui_serial_out_task(void *pvParameters)
{
    srv_ui_serial_setup();
    vTaskDelay(SRV_UI_SERIAL_OUT_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_serial_out_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_UI_SERIAL_OUT_REC / portTICK_PERIOD_MS);
    }
}
#endif

//-----------------------------------------------------------------------------
// Task for reading commands from the serial terminal
#ifdef USE_SRV_UI_SERIAL
void srv_ui_serial_in_task(void *pvParameters)
{
    srv_ui_serial_setup();
    vTaskDelay(SRV_UI_SERIAL_IN_OFFSET / portTICK_PERIOD_MS);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        srv_ui_serial_in_loop();
        vTaskDelayUntil(&xLastWakeTime, SRV_UI_SERIAL_IN_REC / portTICK_PERIOD_MS);
    }
}
#endif

