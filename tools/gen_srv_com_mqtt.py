import os

from gen_utils import *


#generate recurenceses and offset for all modules
def gen_srv_com_mqtt():
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/srv_com_mqtt/srv_com_mqtt.cpp"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)

    except_list = ["srv_sys_os","srv_sig_cond","srv_com_mqtt","srv_ui_serial" "app"]

    file = open(file_name, "w")

    file.write("#include \"Arduino.h\"\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("#include \"ecu_modules.h\"\n")
    file.write("#include \"srv_com_mqtt.h\"\n")
    file.write("\n")

    file.write("#ifndef ESP32\n")
    file.write("void srv_com_mqtt_setup() {}\n")
    file.write("void srv_com_mqtt_loop() {}\n")
    file.write("#else\n")
    file.write("#include <WiFi.h>\n")
    file.write("#include <PubSubClient.h>\n")
    file.write("#include <WiFiClientSecure.h>\n")
    file.write("#include <ArduinoJson.h>\n")
    file.write("#endif\n")

    file.write("//=============================================================================\n")
    file.write("// Include MQTT capabilityes of the units\n")
    file.write("//-----------------------------------------------------------------------------\n")

    #generate recurenceses counter intialization
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        #include each unit Mqtt capability
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("#include \"" + subfolder + "/" + subfolder + "_mqtt.h\"\n")
        file.write("#endif\n")
        file.write("//-----------------------------------------------------------------------------\n")
    file.write("\n")


    file.write("//=============================================================================\n")
    file.write("// Function declarations\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("void srv_com_mqtt_connectToWiFi();\n")
    file.write("void callback(char *topic, byte *payload, unsigned int length);\n")
    file.write("void publishMessage(int data);\n"); 
    file.write("void setupMQTT();\n")
    file.write("void reconnect();\n")
    file.write("\n")

    file.write("//=============================================================================\n")
    file.write("// WiFi and MQTT configuration\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("#include \"iot_crt.h\"\n")
    file.write("\n")
    file.write("// WiFi access point\n")
    file.write("#define WIFI_AP_NAME \"Galaxy Fold4DBB3\"\n")
    file.write("// WiFi password\n")
    file.write("#define WIFI_PASSWORD \"the8time\"\n")
    file.write("// #define WIFI_PASSWORD       \"A3KBuSpq\"\n")
    file.write("\n")
    file.write("// const char *SSID = WIFI_AP_NAME;\n")
    file.write("// const char *PWD = \"the8time\";\n")
    file.write("const char SSID[] = \"FabLab-FREE\";\n")
    file.write("const char PWD[] = \"\";\n")
    file.write("// MQTT Broker\n")
    file.write("DynamicJsonDocument doc_out(1024);\n")
    file.write("DynamicJsonDocument doc_in(1024);\n")
    file.write("WiFiClientSecure wifiClient;\n")
    file.write("PubSubClient mqttClient(wifiClient);\n")
    file.write("// char mqttServer[] = \"9b7b323ee67e46d18f9317162c8e8841.s1.eu.hivemq.cloud\";\n")
    file.write("char mqttServer[] = \"d5e3702cf49544dc93dafafff5bfa7e1.s1.eu.hivemq.cloud\";\n")
    file.write("// char mqtt_username[] = \"sergiu.doncila\";\n")   
    file.write("char mqtt_username[] = \"hivemq.webclient.1744459053013\";\n")
    file.write("// char mqtt_password[] = \"QWEasd!@#123\";\n")
    file.write("char mqtt_password[] = \"OT9.57Iu0USfg!x&C,im\";\n")
    file.write("int mqttPort = 8883;\n")    
    file.write("long last_time = 0;\n")
    file.write("char data[10];\n")
    file.write("\n")
# //=============================================================================
# // Function definitions
# //-----------------------------------------------------------------------------
    file.write("//=============================================================================\n")
    file.write("// Function definitions\n")
    file.write("//-----------------------------------------------------------------------------\n")
# // put your setup code here, to run once:

# // connect to WiFi
# void srv_com_mqtt_connectToWiFi()
    file.write("void srv_com_mqtt_connectToWiFi()\n")
    file.write("{\n")
    file.write("  Serial.print(F(\"Connecting to WiFi \"));\n")
    file.write("  WiFi.begin(SSID, PWD);\n")
    file.write("  Serial.print(F(\"SSID: \"));\n")
    file.write("  Serial.println(SSID);\n")

    file.write("  while (WiFi.status() != WL_CONNECTED) {\n")
    file.write("    delay(500);\n")
    file.write("    Serial.print(\".\");\n")
    file.write("  }\n")
    file.write("  Serial.println(F(\"Connected to WiFi\"));\n")
    file.write("  Serial.print(F(\"IP address: \"));\n")
    file.write("  Serial.println(WiFi.localIP());\n")
    file.write("}\n")
    file.write("\n")

#================================================================================
# // setup MQTT client
    file.write("void setupMQTT()\n")
    file.write("{\n")
    file.write("  mqttClient.setServer(mqttServer, mqttPort);\n")
    file.write("  mqttClient.setCallback(callback);\n")
    file.write("}\n")
    file.write("\n")

#================================================================================
# // MQTT callback function
    file.write("//=============================================================================\n")    
    file.write("// MQTT callback function \n")
    file.write("// This function is called when a message is received on a subscribed topic)\n")
    file.write("//-----------------------------------------------------------------------------\n")

    file.write("void callback(char *topic, byte *payload, unsigned int length)\n")
    file.write("{\n")
    file.write("  Serial.println(F(\"MQTT Callback \"));\n")
    file.write("  Serial.print(F(\"Topic:\"));\n")
    file.write("  Serial.println(topic);\n")
    file.write("\n")
    file.write("  Serial.println(F(\"Message:\"));\n")
    file.write("  for (int i = 0; i < length; i++)\n")
    file.write("  {\n")
    file.write("    Serial.print((char)payload[i]);\n")
    file.write("  }\n")
    file.write("  Serial.println();\n")
    file.write("\n")
    file.write("\n")
    
    #generate recurenceses counter intialization
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("  " + subfolder + "_mqtt_callback(doc_in, topic, payload, length);\n")
        file.write("#endif\n")
    file.write("\n")

    file.write("}\n")


# // reconnect to MQTT broker
    file.write("//============================================================================= \n")
    file.write("// MQTT reconnect function \n")
    file.write("/ This function attempts to reconnect to the MQTT broker if the connection is lost \n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("void reconnect()\n")
    file.write("{\n")
    file.write("  Serial.println(F(\"Connecting to MQTT Broker...\"));\n")
    file.write("  while (!mqttClient.connected())\n")
    file.write("  {\n")
    file.write("    Serial.print(F(\"Actual state: \"));\n")
    file.write("    Serial.println(mqttClient.state());\n")
    file.write("    Serial.println(F(\"Reconnecting to MQTT Broker..\"));\n")
    file.write("    String clientId = \"ESP32Client-\";\n")
    file.write("    clientId += String(random(0xffff), HEX);\n")
    file.write("\n")
    file.write("    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password))\n")
    file.write("    {\n")
    file.write("      Serial.println(F(\"Connected to MQTT broker.----------------------------------\"));\n")
# // subscribe to topic
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("      " + subfolder + "_mqtt_subscribe(mqttClient);\n")
        file.write("#endif\n")


#=====================================================================
# generate setup function
#-------------------------------------------------------------------------------
    file.write("//======================================================================\n")
    file.write("// MQTT setup function\n")
    file.write("//----------------------------------------------------------------------\n")

    file.write("void srv_com_mqtt_setup()\n")
    file.write("{\n")
    file.write("  // put your setup code here, to run once:\n")
    file.write("  delay(1000);\n")
    file.write("  srv_com_mqtt_connectToWiFi();\n")
    file.write("  wifiClient.setInsecure();\n")
    file.write("  setupMQTT();\n")
    file.write("\n")
    file.write("}\n")
    file.write("\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("" +subfolder + "_setup();\n")
        file.write("#endif\n")
    file.write("}\n")

    file.write("\n")


#===============================================================================
# MQTT loop function
#-------------------------------------------------------------------------------
    file.write("//=============================================================================\n")
    file.write("// MQTT loop function\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("void srv_com_mqtt_loop()\n")
    file.write("{\n")
    file.write("  // put your main code here, to run repeatedly:\n")
    file.write("  if (!mqttClient.connected())\n")
    file.write("    reconnect();\n")
    file.write("  mqttClient.loop();\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("  " + subfolder + "_mqtt_publish(doc_out, mqttClient);\n")
        file.write("#endif\n")

    file.write("\n")
    file.write("}\n")
    file.close()
#-------------------------------------------------------------------------------


gen_srv_com_mqtt()
print("srv_com_mqtt.cpp generated successfully.")
