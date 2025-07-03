import os

from gen_utils import *


#generate recurenceses and offset for all modules
def gen_srv_ui_serial():
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/srv_ui_serial/srv_ui_serial.cpp"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)

    except_list = ["srv_sys_os","srv_sig_cond","srv_com_mqtt","srv_ui_serial" "app"]

    file = open(file_name, "w")

    file.write("#include \"Arduino.h\"\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("#include \"ecu_modules.h\"\n")
    file.write("#include \"srv_ui_serial.h\"\n")
    file.write("\n")

# #ifndef SRV_UI_SERIAL_BAUDRATE
# #define SRV_UI_SERIAL_BAUDRATE 115200
# #endif
    file.write("#ifndef SRV_UI_SERIAL_BAUDRATE\n")
    file.write("#define SRV_UI_SERIAL_BAUDRATE 115200\n")
    file.write("#endif\n")
    file.write("\n")
# //-----------------------------------------------
# // include Control components reports
    file.write("//-----------------------------------------------\n")
    file.write("// include Control components reports\n")

# #ifdef USE_CTRL_AIR_TEMP_HEAT
# #include "ctrl_air_temp_heat/ctrl_air_temp_heat_term.h"
# #endif
# #ifdef USE_CTRL_AIR_TEMP_VENT
# #include "ctrl_air_temp_vent/ctrl_air_temp_vent_term.h"
# #endif
# #ifdef USE_CTRL_AIR_HUM
# #include "ctrl_air_hum/ctrl_air_hum_term.h"
# #endif
# #ifdef USE_CTRL_SOIL_MOIST
# #include "ctrl_soil_moist/ctrl_soil_moist_term.h"
# #endif
# #ifdef USE_CTRL_AIR_PRESS
# #include "ctrl_air_press/ctrl_air_press_term.h"
# #endif
# #ifdef USE_CTRL_AMB_LIGHT
# #include "ctrl_amb_light/ctrl_amb_light_term.h"
# #endif

    for subfolder in subfolders:
        if subfolder.startswith("ctrl_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f'#include "{subfolder}/{subfolder}_term.h"\n')
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# // include Sensor components reports
    file.write("//-----------------------------------------------\n")
    file.write("// include Sensor components reports\n")
# #ifdef USE_SRV_SNS_AIR_PRESS
# #include "srv_sns_air_press/srv_sns_air_press_term.h"
# #endif
# #ifdef USE_SRV_SNS_AIR_TEMP
# #include "srv_sns_air_temp/srv_sns_air_temp_term.h"
# #endif
# #ifdef USE_SRV_SNS_SOIL_MOIST
# #include "srv_sns_soil_moist/srv_sns_soil_moist_term.h"
# #endif
# #ifdef USE_SRV_SNS_AIR_HUM
# #include "srv_sns_air_hum/srv_sns_air_hum_term.h"
# #endif
# #ifdef USE_SRV_SNS_LIGHT
# #include "srv_sns_amb_light/srv_sns_amb_light_term.h"
# #endif
    for subfolder in subfolders:
        if subfolder.startswith("srv_sns_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f'#include "{subfolder}/{subfolder}_term.h"\n')
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# // include Actuator components reports
    file.write("//-----------------------------------------------\n")
    file.write("// include device drivers components reports\n")
# #ifdef USE_DD_WINDOW
# #include "dd_window/dd_window_term.h"
# #endif
# #ifdef USE_DD_HEATER
# #include "dd_heater/dd_heater_term.h"
# #endif
# #ifdef USE_DD_VALVE
# #include "dd_valve/dd_valve_term.h"
# #endif
# #ifdef USE_DD_AIR_PUMP
# #include "dd_air_pump/dd_air_pump_term.h"
# #endif
# #ifdef USE_DD_LIGHTS
# #include "dd_lights/dd_lights_term.h"
# #endif
    for subfolder in subfolders:
        if subfolder.startswith("dd_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f'#include "{subfolder}/{subfolder}_term.h"\n')
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# // include ECU report components
    file.write("//-----------------------------------------------\n")
    file.write("// include ECU components reports\n")
# #ifdef USE_ED_DHT
# #include "ed_dht/ed_dht_term.h"
# #endif
# #ifdef USE_ED_BMP
# #include "ed_bmp/ed_bmp_term.h"
# #endif
# #ifdef USE_ED_BH1750
# #include "ed_bh1750/ed_bh1750_term.h"
# #endif
# #ifdef USE_ED_SNS_SOIL_MOIST
# #include "ed_sns_soil_moist/ed_sns_soil_moist_term.h"
# #endif
# #ifdef USE_ED_RELAY
# #include "ed_relay/ed_relay_term.h"
# #endif
    for subfolder in subfolders:
        if subfolder.startswith("ed_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f'#include "{subfolder}/{subfolder}_term.h"\n')
            file.write("#endif\n")
    file.write("\n")


# void srv_ui_serial_setup()
# {
#       Serial.begin(SRV_UI_SERIAL_BAUDRATE);
#       Serial.println(F("SRV_SERIAL: Device System started"));
# }

    file.write("//-----------------------------------------------\n")
    file.write("// setup serial service\n")
    file.write("void srv_ui_serial_setup()\n")
    file.write("{\n")
    file.write("      Serial.begin(SRV_UI_SERIAL_BAUDRATE);\n")
    file.write("      Serial.println(F(\"SRV_SERIAL: Device System started\"));\n")
    file.write("}\n")
    file.write("\n")

# void srv_ui_serial_in_green_house(char cmd)
# {
    file.write("//-----------------------------------------------\n")
    file.write("// process command for green house\n")
    file.write("void srv_ui_serial_in_green_house(char cmd)\n")
    file.write("{\n")
# #if defined USE_CTRL_AIR_TEMP_VENT
#       ctrl_air_temp_vent_term_cmd(cmd);
# #elif defined USE_DD_WINDOW
#       dd_window_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 1,2
#       ed_relay_term_cmd(cmd);
# #endif
    file.write("#if defined USE_CTRL_AIR_TEMP_VENT\n")
    file.write("      ctrl_air_temp_vent_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_WINDOW\n")
    file.write("      dd_window_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 1,2\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
    file.write("\n")

# #if defined USE_CTRL_AIR_TEMP_HEAT
#       ctrl_air_temp_heat_term_cmd(cmd);
# #elif defined USE_DD_HEATER
#       dd_heater_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 3
#       ed_relay_term_cmd(cmd);
# #endif

    file.write("#if defined USE_CTRL_AIR_TEMP_HEAT\n")
    file.write("      ctrl_air_temp_heat_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_HEATER\n")
    file.write("      dd_heater_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 3\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
    file.write("\n")

# #if defined USE_CTRL_AIR_HUM
#       ctrl_air_hum_term_cmd(cmd);
# #elif defined USE_DD_VALVE
#       dd_valve_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 4
#       ed_relay_term_cmd(cmd);
# #endif

    file.write("#if defined USE_CTRL_AIR_HUM\n")
    file.write("      ctrl_air_hum_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_VALVE\n")
    file.write("      dd_valve_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 4\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
    file.write("\n")

# #if defined USE_CTRL_SOIL_MOIST
#       ctrl_soil_moist_term_cmd(cmd);
# #elif defined USE_DD_VALVE
#       dd_valve_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 5
#       ed_relay_term_cmd(cmd);
# #endif

    file.write("#if defined USE_CTRL_SOIL_MOIST\n")
    file.write("      ctrl_soil_moist_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_VALVE\n")
    file.write("      dd_valve_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 5\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
    file.write("\n")

# #if defined USE_CTRL_AIR_PRESS
#       ctrl_air_press_term_cmd(cmd);
# #elif defined USE_DD_AIR_PUMP
#       dd_air_pump_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 6
#       ed_relay_term_cmd(cmd);
# #endif

    file.write("#if defined USE_CTRL_AIR_PRESS\n")
    file.write("      ctrl_air_press_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_AIR_PUMP\n")
    file.write("      dd_air_pump_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 6\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
    file.write("\n")

# #if defined USE_CTRL_AMB_LIGHT
#       ctrl_amb_light_term_cmd(cmd);
# #elif defined USE_DD_LIGHTS
#       dd_lights_term_cmd(cmd);
# #elif defined USE_ED_RELAY // 7
#       ed_relay_term_cmd(cmd);
# #endif

    file.write("#if defined USE_CTRL_AMB_LIGHT\n")
    file.write("      ctrl_amb_light_term_cmd(cmd);\n")
    file.write("#elif defined USE_DD_LIGHTS\n")
    file.write("      dd_lights_term_cmd(cmd);\n")
    file.write("#elif defined USE_ED_RELAY // 7\n")
    file.write("      ed_relay_term_cmd(cmd);\n")
    file.write("#endif\n")
# }
    file.write("}\n")
    file.write("\n")
    


# void srv_ui_serial_in_can_steer(char cmd)
# {
# }

# //-----------------------------------------------
# // process command for CAN bus
    file.write("//-----------------------------------------------\n")
    file.write("// process command for CAN bus\n")
    file.write("void srv_ui_serial_in_can_steer(char cmd)\n")
    file.write("{\n")
    file.write("      // TODO: Implement CAN steering command processing\n")
    file.write("}\n")
    file.write("\n")
# //-----------------------------------------------
# // process command for serial input
# void srv_ui_serial_in_loop()
# {
#       if (Serial.available())
#       {
#             char cmd = Serial.read();

#             Serial.print(F("SRV_UI_SERIAL: Recived command: "));
#             Serial.println(cmd);

#             // Process command for green house

#             srv_ui_serial_in_green_house(cmd);
#       }
# }
    file.write("//-----------------------------------------------\n")
    file.write("// process command for serial input\n")
    file.write("void srv_ui_serial_in_loop()\n")
    file.write("{\n")
    file.write("      if (Serial.available())\n")
    file.write("      {\n")
    file.write("            char cmd = Serial.read();\n")
    file.write("            Serial.print(F(\"SRV_UI_SERIAL: Recived command: \"));\n")
    file.write("            Serial.println(cmd);\n")
    file.write("            // Process command for green house\n")
    file.write("            srv_ui_serial_in_green_house(cmd);\n")
    file.write("      }\n")
    file.write("}\n")
    file.write("\n")


# void srv_ui_serial_out_loop()
# {
#       Serial.println(F("=============== MLP: System Report =============== "));

    file.write("//-----------------------------------------------\n")
    file.write("// report system state\n")
    file.write("void srv_ui_serial_out_loop()\n")
    file.write("{\n")
    file.write("      Serial.println(F(\"=============== MLP: System Report =============== \"));\n")

# //-----------------------------------------------
# //  Report Control components state
    file.write("//-----------------------------------------------\n")
    file.write("//  Report Control components state\n")
# #ifdef USE_CTRL_AIR_TEMP_VENT
#       ctrl_air_temp_vent_report();
# #endif
# #ifdef USE_CTRL_AIR_TEMP_HEAT
#       ctrl_air_temp_heat_report();
# #endif
# #ifdef USE_CTRL_AIR_HUM
#       ctrl_air_hum_report();
# #endif
# #ifdef USE_CTRL_SOIL_MOIST
#       ctrl_soil_moist_report();
# #endif
# #ifdef USE_CTRL_AIR_PRESS
#       ctrl_air_press_report();
# #endif
# #ifdef USE_CTRL_AMB_LIGHT
#       ctrl_amb_light_report();
# #endif

    for subfolder in subfolders:
        if subfolder.startswith("ctrl_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f"      {subfolder}_report();\n")
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# //  Report Sensor components state
    file.write("//-----------------------------------------------\n")
    file.write("//  Report Sensor components state\n")
# #ifdef USE_SRV_SNS_AIR_TEMP
#       srv_sns_air_temp_report();
# #endif
# #ifdef USE_SRV_SNS_AIR_HUM
#       srv_sns_air_hum_report();
# #endif
# #ifdef USE_SRV_SNS_SOIL_MOIST
#       srv_sns_soil_moist_report();
# #endif
# #ifdef USE_SRV_SNS_AIR_PRESS
#       srv_sns_air_press_report();
# #endif
# #ifdef USE_SRV_SNS_LIGHT
#       srv_sns_light_report();
# #endif
    for subfolder in subfolders:
        if subfolder.startswith("srv_sns_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f"      {subfolder}_report();\n")
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# //  Report Can Matrix messages state
    file.write("//-----------------------------------------------\n")
    file.write("//  Report Can Matrix messages state\n")
# #ifdef USE_SRV_COM_CAN
#       dd_can_matrix_report();
# #endif
    file.write("#ifdef USE_SRV_COM_CAN\n")
    file.write("      dd_can_matrix_report();\n")
    file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# //  Report Actuator components state
    file.write("//-----------------------------------------------\n")
    file.write("//  Report Device Drivers components\n")
# #ifdef USE_DD_WINDOW
#       dd_window_report();
# #endif
# #ifdef USE_DD_HEATER
#       dd_heater_report();
# #endif
# #ifdef USE_DD_VALVE
#       dd_valve_report();
# #endif
# #ifdef USE_DD_AIR_PUMP
#       dd_air_pump_report();
# #endif
# #ifdef USE_DD_LIGHTS
#       dd_lights_report();
# #endif
    for subfolder in subfolders:
        if subfolder.startswith("dd_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f"      {subfolder}_report();\n")
            file.write("#endif\n")
    file.write("\n")

# //-----------------------------------------------
# //  Report ECU components state
    file.write("//-----------------------------------------------\n")
    file.write("//  Report ECU components state\n")

# #ifdef USE_ED_DHT
#       ed_dht_report();
# #endif
# #ifdef USE_ED_SNS_SOIL_MOIST
#       ed_sns_soil_moist_report();
# #endif
# #ifdef USE_ED_BMP
#       ed_bmp_report();
# #endif
# #ifdef USE_ED_BH1750
#       ed_bh1750_report();
# #endif
# #ifdef USE_ED_RELAY
#       ed_relay_report();
# #endif

    for subfolder in subfolders:
        if subfolder.startswith("ed_") and subfolder not in except_list:
            file.write(f"#ifdef USE_{subfolder.upper()}\n")
            file.write(f"      {subfolder}_report();\n")
            file.write("#endif\n")
    file.write("\n")
    file.write("}\n")
    file.write("\n")    


gen_srv_ui_serial()
