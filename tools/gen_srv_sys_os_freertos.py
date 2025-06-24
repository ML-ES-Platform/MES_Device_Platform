import os

from gen_utils import *


#generate recurenceses and offset for all modules
def gen_srv_sys_os_freertos():
    """
    Generate the FreeRTOS task modules for the srv_sys_os.

    This function generates the task modules declarations and initialization code for the srv_sys_os using FreeRTOS.
    It creates a file named 'srv_sys_os_freertos.cpp' in the 'tools/generated/src/srv_sys_os' directory and writes the generated code into it.

    Args:
        None

    Returns:
        None
    """
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/srv_sys_os/srv_sys_os_freertos.cpp"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)


    except_list = ["srv_sys_os","srv_sig_cond"]

    file = open(file_name, "w", encoding="utf-8")

    file.write("#include \"Arduino.h\"\n")
    file.write("#include \"srv_sys_os_freertos.h\"\n")
    file.write("#include \"ecu_modules.h\"\n")
    file.write("\n")
    file.write("//=============================================================================\n")
    file.write("// Task modules declarations\n")
    file.write("//-----------------------------------------------------------------------------\n")

    # to generate considering the layers DD ED SRV
    #generate Task modules declarations
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        # file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("void " +subfolder + "_task(void *pvParameters);\n")
        # file.write("#endif\n")
        # file.write("//-----------------------------------------------------------------------------\n")
    file.write("\n")

    file.write("//=============================================================================\n")
    file.write("// Task modules initialization\n")
    file.write("//-----------------------------------------------------------------------------\n")
    #generate setup function
    file.write("// the setup function runs once when you press reset or power the board\n")
    file.write("void srv_sys_os_freertos_setup()\n")
    file.write("{\n")
    file.write("    // Set up Tasks to run independently.\n")
    file.write("\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        file.write("//-----------------------------------------------------------------------------\n")
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("    xTaskCreate(" +subfolder + "_task, \"" +subfolder + "_task\", 1024, NULL, 1, NULL);\n")
        file.write("#endif\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("\n")
    file.write("    // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.")
    file.write("\n")
    file.write("}\n")
    file.write("\n")

    file.write("//=============================================================================\n")
    file.write("// Task modules declarations\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("\n")


    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        # insert loop recurent call

        file.write("//-----------------------------------------------------------------------------\n")
        file.write("// Task for managing "+subfolder.upper()+"\n")
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("void " +subfolder + "_task(void *pvParameters)\n")
        file.write("{\n")
        file.write("    " +subfolder + "_setup();\n")
        file.write("    vTaskDelay("+subfolder.upper()+"_OFFSET / portTICK_PERIOD_MS);\n")
        file.write("    TickType_t xLastWakeTime = xTaskGetTickCount();\n")
        file.write("\n")
        file.write("    for (;;)\n")
        file.write("    {\n")
        file.write("        " +subfolder + "_loop();\n")
        file.write("        vTaskDelayUntil(&xLastWakeTime, "+subfolder.upper()+"_REC / portTICK_PERIOD_MS);\n")
        file.write("    }\n")
        file.write("}\n")
        file.write("#endif\n")
        file.write("\n")




 




    file.write("\n")
    file.write("\n")

    file.close()


gen_srv_sys_os_freertos()

