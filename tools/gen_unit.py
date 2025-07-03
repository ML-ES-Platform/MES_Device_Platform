import os
import json

from gen_utils import *
global unit_id

def gen_unit_head( base_dir, unit_name, config_json):

    file_name = base_dir + "/"+ unit_name + "/" + unit_name + ".h"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    file.write("#ifndef "+unit_name.upper()+"_H\n")
    file.write("#define "+unit_name.upper()+"_H\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("\n")
    file.write("void "+unit_name+"_setup();\n")
    file.write("void "+unit_name+"_loop();\n")
    file.write("\n")
    
    component_json = config_get_component_json(unit_name, config_json)
    signals = config_get_signals(component_json)
    
    for signal_id in signals:
        signal_name = config_get_signal_name(signals[signal_id])
        signal_dir = config_get_signal_dir(signals[signal_id])
        signal_type = config_get_signal_type(signals[signal_id])

        if signal_dir == "input":
            file.write("void "+unit_name+"_set_"+signal_name+"("+signal_type+" value);\n")
        elif signal_dir == "output":
            file.write(""+signal_type+" "+unit_name+"_get_"+signal_name+"(void);\n")
            file.write("int "+unit_name+"_get_"+signal_name+"_error(void);\n")
        else:
            file.write("void "+unit_name+"_set_"+signal_name+"("+signal_type+" value);\n")
            file.write(""+signal_type+" "+unit_name+"_get_"+signal_name+"(void);\n")
            file.write("int "+unit_name+"_get_"+signal_name+"_error(void);\n")
        file.write("\n")

    file.write("#endif // "+unit_name.upper()+"_H\n")
    file.write("\n")
    file.close()





def gen_unit_src( base_dir, unit_name, config_json):
    
    file_name = base_dir + "/"+ unit_name + "/" + unit_name + ".cpp"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    component_json = config_get_component_json(unit_name, config_json)
    signals = config_get_signals(component_json)

    file.write("#include \""+unit_name+".h\"\n")
    for signal_id in signals:
        signal_dependency = config_get_signal_dependency(signals[signal_id])
        if signal_dependency != "":
            file.write("#include \""+signal_dependency+"/"+signal_dependency+".h\"\n")
    file.write("\n")
    for signal_id in signals:
        signal_name = config_get_signal_name(signals[signal_id])
        signal_default_value = config_get_signal_default_value(signals[signal_id])
        signal_type = config_get_signal_type(signals[signal_id])

        file.write(""+signal_type+" "+unit_name+"_"+signal_name+" = "+signal_default_value+";\n")
        file.write("int "+unit_name+"_"+signal_name+"_error = 0;\n")
        file.write("\n")

    file.write("\n")

    for signal_id in signals:
        signal_name = config_get_signal_name(signals[signal_id])
        signal_type = config_get_signal_type(signals[signal_id])

        file.write(""+signal_type+" "+unit_name+"_get_"+signal_name+"(void)\n")
        file.write("{\n")
        file.write("return "+unit_name+"_"+signal_name+";\n")
        file.write("}\n")
        file.write("\n")
        file.write("int "+unit_name+"_get_"+signal_name+"_error(void)\n")
        file.write("{\n")
        file.write("return "+unit_name+"_"+signal_name+"_error;\n")
        file.write("}\n")
        file.write("\n")

    file.write("\n")
    file.write("void "+unit_name+"_setup()\n")
    file.write("{\n")
    file.write("\n")
    file.write("}\n")
    file.write("\n")
    file.write("void "+unit_name+"_loop()\n")
    file.write("{\n")
    file.write("\n")
    file.write("}\n")
    file.write("\n")
    file.close()
    # json_file = file_to_json(file_name)
    # #write tha json file to the file .json
    # file = open(file_name + ".json", "w")
    # file.write(json_file)
    # file.close()

def gen_unit_term_head( base_dir, unit_name, config_json):
    
    file_name = base_dir + "/"+ unit_name + "/" + unit_name + "_term.h"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    file.write("#ifndef "+unit_name.upper()+"_TERM_H\n")
    file.write("#define "+unit_name.upper()+"_TERM_H\n")
    file.write("\n")
    file.write("// Include any necessary libraries or headers\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("\n")
    file.write("// Define any constants or macros\n")
    file.write("\n")
    file.write("// Declare any function prototypes\n")
    file.write("void "+unit_name+"_report();\n")
    file.write("\n")
    file.write("#endif // "+unit_name.upper()+"_TERM_H\n")



def gen_unit_term_src( base_dir, unit_name, config_json):
    
    file_name = base_dir + "/"+ unit_name + "/" + unit_name + "_term.cpp"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    file.write("#include \""+unit_name+"_term.h\"\n")
    file.write("#include \""+unit_name+".h\"\n")
    file.write("#include \"Arduino.h\"\n")
    file.write("\n")
    file.write("void "+unit_name+"_report()\n")
    file.write("{\n")

    component_json = config_get_component_json(unit_name, config_json)
    signals = config_get_signals(component_json)
    
    for signal_id in signals:
        signal_name = config_get_signal_name(signals[signal_id])
        signal_units = config_get_signal_units(signals[signal_id])
        signal_type = config_get_signal_type(signals[signal_id])

        file.write("  "+signal_type+" "+ signal_name +" = " + unit_name + "_get_"+signal_name+"();\n")
        file.write("  Serial.print(F(\"" + unit_name.upper()+"| "+signal_name+": ));\n")
        file.write("  Serial.print("+signal_name+", 5);\n")
        file.write("  Serial.print(F(\" "+signal_units+"\"));\n")
        file.write("\n")
        file.write("  int error = " + unit_name + "_get_"+signal_name+"_error();\n")
        file.write("  Serial.print(F(\" | Error: \"));\n")
        file.write("  if(error == 0)\n")
        file.write("  {\n")
        file.write("    Serial.print(F(\"OK\"));\n")
        file.write("  }\n")
        file.write("  else\n")
        file.write("  {\n")
        file.write("    Serial.print(F(\"N_OK\"));\n")
        file.write("  }\n")
        file.write("\n")
        file.write("  Serial.println();\n" )
        file.write("\n")

    file.write("}\n")
    # file.write("\n")

    file.close()


def gen_unit_mqtt_head( base_dir, unit_name, config_json):

    file_name = base_dir + "/"+ unit_name + "/" + unit_name + "_mqtt.h"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    file.write("#ifndef "+unit_name.upper()+"_MQTT_H_\n")
    file.write("#define "+unit_name.upper()+"_MQTT_H_\n")
    file.write("\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("\n")
    file.write("#include <WiFi.h>\n")
    file.write("#include <PubSubClient.h>\n")
    file.write("#include <WiFiClientSecure.h>\n")
    file.write("#include <ArduinoJson.h>\n")
    file.write("\n")
    file.write("#ifndef "+unit_name.upper()+"_MQTT_PUBLISH_TOPIC\n")
    file.write("#define "+unit_name.upper()+"_MQTT_PUBLISH_TOPIC \"MES_Device_Platform/"+unit_name+"\"\n")
    file.write("#endif\n")
    file.write("\n")
    file.write("#ifndef "+unit_name.upper()+"_MQTT_SUBSCRIBE_TOPIC\n")
    file.write("#define "+unit_name.upper()+"_MQTT_SUBSCRIBE_TOPIC \"MES_Device_Platform/"+unit_name+"/set\"\n")
    file.write("#endif\n")
    file.write("\n")
    file.write("// Include any necessary libraries here\n")
    file.write("\n")
    file.write("// Define any constants or macros here\n")  
    file.write("\n")
    file.write("// Declare any function prototypes here\n")
    file.write("\n")
    file.write("void "+unit_name+"_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);\n")
    file.write("int "+unit_name+"_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);\n")
    file.write("void "+unit_name+"_mqtt_subscribe(PubSubClient &mqttClient);\n")
    file.write("\n")
    file.write("#endif // "+unit_name.upper()+"_MQTT_H\n")
    file.write("\n")

    file.close()


def gen_unit_mqtt_src( base_dir, unit_name, config_json):



    # Generate the file name based on the unit name
    # and the base directory
    file_name = base_dir + "/"+ unit_name + "/" + unit_name + "_mqtt.cpp"
    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)  

    file = open(file_name, "w", encoding="utf-8")

    component_json = config_get_component_json(unit_name, config_json)
    signals = config_get_signals(component_json)

    file.write("#include \""+unit_name+"_mqtt.h\"\n")
    file.write("#include \""+unit_name+".h\"\n")
    file.write("#include \"dd_valve/dd_valve.h\"\n")
    file.write("#include \"Arduino.h\"\n")
    file.write("\n")
    char_variable_sub = unit_name.upper() + "_MQTT_SUBSCRIBE_TOPIC"
    file.write("char "+char_variable_sub.lower()+"[] = "+unit_name.upper()+"_MQTT_SUBSCRIBE_TOPIC;\n")
    char_variable_pub = unit_name.upper() + "_MQTT_PUBLISH_TOPIC"
    file.write("char "+char_variable_pub.lower()+"[] = "+unit_name.upper()+"_MQTT_PUBLISH_TOPIC;\n")
    file.write("\n")
    file.write("//----------------------------------------------------------\n")
    file.write("// Subscribe to "+unit_name+" MQTT topic\n")
    file.write("void "+unit_name+"_mqtt_subscribe(PubSubClient &mqttClient)\n")
    file.write("{\n")
    file.write("\n")
    file.write("#ifdef USE_"+unit_name.upper()+"\n")
    file.write("\n")
    file.write("  Serial.println(F(\""+unit_name.upper()+"_MQTT: "+unit_name+"_mqtt_subscribe\"));\n")
    file.write("\n")
    file.write("  if (mqttClient.subscribe("+char_variable_sub.lower()+"))\n")
    file.write("  {\n")
    file.write("    Serial.print(F(\""+unit_name.upper()+"_MQTT: Subscribed to: \"));\n")
    file.write("    Serial.println("+char_variable_sub.lower()+");\n")
    file.write("  }\n")
    file.write("  else\n")
    file.write("  {\n")
    file.write("    Serial.print(F(\""+unit_name.upper()+"_MQTT: Failed to subscribe to: \"));\n")
    file.write("    Serial.println("+char_variable_sub.lower()+");\n")
    file.write("  }\n")
    file.write("#endif\n")
    file.write("}\n")
    file.write("\n")
    file.write("//----------------------------------------------------------\n")
    file.write("// Publish "+unit_name+" Data to MQTT\n")
    file.write("void "+unit_name+"_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)\n")
    file.write("{\n")
    file.write("\n")
    file.write("#ifdef USE_"+unit_name.upper()+"\n")
    file.write("\n")
    file.write("  Serial.println(F(\""+unit_name.upper()+"_MQTT: "+unit_name+"_mqtt_publish\"));\n")
    file.write("\n")
    file.write("  // JSON mapping\n")
    file.write("  doc_out.clear();\n")
    file.write("  doc_out[\"device_id\"] = \"gh_001\";\n")
    #auto increment unit_id

    global unit_id
    if 'unit_id' not in globals():
        unit_id = 100
    unit_id += 1
    # unit_id = config_get_component_id(component_json, unit_id)
    file.write("  doc_out[\"unit_id\"] = "+str(unit_id)+";\n")
    file.write("  doc_out[\"unit_name\"] = \""+unit_name+"\";\n")
    file.write("  doc_out[\"cur_hum\"] = "+unit_name+"_get_current_hum();\n")
    file.write("  doc_out[\"set_point\"] = "+unit_name+"_get_setpoint();\n")
    file.write("  doc_out[\"ctrl_mode\"] = "+unit_name+"_get_mode();\n")
    file.write("  doc_out[\"ctrl_out\"] = "+unit_name+"_get_output();\n")
    file.write("\n")
    file.write("  // Publishing data throgh MQTT\n")
    file.write("  char mqtt_message[256];\n")
    file.write("  serializeJson(doc_out, mqtt_message);\n")
    file.write("  mqttClient.publish("+char_variable_pub.lower()+", mqtt_message, true);\n")
    file.write("#endif\n")
    file.write("}\n")
    file.write("\n")
    file.write("//----------------------------------------------------------\n")
    file.write("// "+unit_name+" MQTT Callback\n")
    file.write("int "+unit_name+"_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)\n")
    file.write("{\n")
    file.write("  int result = 0; // default return value\n")
    file.write("\n")
    file.write("#ifdef USE_"+unit_name.upper()+"\n")
    file.write("\n")
    file.write("  Serial.println();\n")
    file.write("\n")
    file.write("  // check if the topic is the one we subscribed to\n")
    file.write("  if (strcmp(topic, "+char_variable_sub.lower()+") == 0)\n")
    file.write("  {\n")
    file.write("    result = 1; // set result to 1 if the topic matches\n")
    file.write("\n")
    file.write("    // Serial.println(F(\""+unit_name.upper()+"_MQTT: "+unit_name+"_mqtt_callback\"));\n")
    file.write("    // Serial.print(F(\""+unit_name.upper()+"_MQTT: Received message on topic: \"));\n")
    file.write("    // Serial.println(topic);\n")
    file.write("\n")
    file.write("    deserializeJson(doc_in, (const byte *)payload, length);\n")
    file.write("\n")
    file.write("    char cmd[32];\n")
    file.write("    strlcpy(cmd, doc_in[\"cmd\"] | \"default\", sizeof(cmd));\n")
    file.write("\n")
    file.write("    Serial.print(F(\"Command:\"));\n")
    file.write("    Serial.println(cmd);\n")
    file.write("\n")
    file.write("    char value[32];\n")
    file.write("    strlcpy(value, doc_in[\"value\"] | \"default\", sizeof(value));\n")
    file.write("\n")
    file.write("    Serial.print(F(\"Value:\"));\n")
    file.write("    Serial.println(value);\n")
    file.write("\n")
    file.write("    float value_f = atof(value);\n")
    file.write("    Serial.print(F(\"Value_f:\"));\n")
    file.write("    Serial.println(value_f);\n")
    file.write("\n")
    file.write("    // subscribe message example\n")
    file.write("    // {\n")
    file.write("    //   \"cmd\":\"set_point\",\n")
    file.write("    //   \"value\":\"17.3\"\n")
    file.write("    // }\n")
    file.write("\n")
    file.write("    if (strcmp(cmd, \"set_point\") == 0)\n")
    file.write("    {\n")
    file.write("      "+unit_name+"_set_setpoint(value_f);\n")
    file.write("    }\n")
    file.write("    else if (strcmp(cmd, \"ctrl_mode\") == 0)\n")
    file.write("    {\n")
    file.write("      int mode = value_f;\n")
    file.write("      if (mode == "+unit_name.upper()+"_DISABLE)\n")
    file.write("      {\n")
    file.write("        "+unit_name+"_set_mode_manual();\n")
    file.write("      }\n")
    file.write("      else if (mode == "+unit_name.upper()+"_ENABLE)\n")
    file.write("      {\n")
    file.write("        "+unit_name+"_set_mode_auto();\n")
    file.write("      }\n")
    file.write("    }\n")
    file.write("    else if (strcmp(cmd, \"ctrl_out\") == 0)\n")
    file.write("    {\n")
    file.write("      int out = value_f;\n")
    file.write("      if (out == "+unit_name.upper()+"_OUT_OFF)\n")
    file.write("      {\n")
    file.write("        dd_valve_off(DD_VALVE_"+unit_name.upper()+"_ID);\n")
    file.write("      }\n")
    file.write("      else if (out == "+unit_name.upper()+"_OUT_ON)\n")
    file.write("      {\n")
    file.write("        dd_valve_on(DD_VALVE_"+unit_name.upper()+"_ID, "+unit_name.upper()+"_OP_D_TIME);\n")
    file.write("      }\n")
    file.write("    }\n")
    file.write("  }\n")
    file.write("  else\n")
    file.write("  {\n")
    file.write("    result = 0; // set result to 0 if the topic does not match\n")
    file.write("    // Serial.print(F(\""+unit_name.upper()+"_MQTT: Received message on unknown topic: \"));\n")
    file.write("    // Serial.println(topic);\n")
    file.write("  }\n")
    file.write("#endif\n")
    file.write("  return result; // return 1 if the topic matches, otherwise return 0\n")
    file.write("}\n")
    file.write("\n")
    file.close()




    



def gen_units():
    directory_src = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory_src)
    base_dir = "tools/generated/src"

    except_list = ["srv_sys_os","srv_sig_cond"]

    #generate recurenceses counter intialization
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        #read json file
        config_json = file_to_json(directory_src + "/"+ subfolder + "/" + subfolder + "_cfg.json")
        #create unit Header file
        gen_unit_head(base_dir, subfolder, config_json)
        # create unit src file
        gen_unit_src(base_dir, subfolder, config_json)
        #crate unit report header file
        gen_unit_term_head(base_dir, subfolder, config_json)
        # create report file
        gen_unit_term_src(base_dir, subfolder, config_json)
        # create mqtt communication header file
        gen_unit_mqtt_head(base_dir, subfolder, config_json)
        # create mqtt communication src file
        gen_unit_mqtt_src(base_dir, subfolder, config_json)

unit_id = 100
gen_units()


