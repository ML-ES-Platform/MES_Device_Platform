import os

from gen_utils import *


#generate recurenceses and offset for all modules
def gen_srv_sys_os_seq():
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/srv_sys_os/srv_sys_os_seq.cpp"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)


    except_list = ["srv_sys_os","srv_sig_cond"]

    file = open(file_name, "w")

    file.write("#include \"Arduino.h\"\n")
    file.write("#include \"srv_sys_os_seq.h\"\n")
    file.write("#include \"ecu_modules.h\"\n")
    file.write("\n")
    file.write("//=============================================================================\n")
    file.write("// Task Scheduling definitions\n")
    file.write("//-----------------------------------------------------------------------------\n")

    #generate recurenceses counter intialization
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("    int " +subfolder + "_rec_cnt = "+subfolder.upper()+"_OFFSET; \n")
        file.write("#endif\n")
        file.write("//-----------------------------------------------------------------------------\n")


    #generate setup function
    file.write("void srv_sys_os_seq_setup()\n")
    file.write("{\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("" +subfolder + "_setup();\n")
        file.write("#endif\n")
    file.write("}\n")

    file.write("\n")

    #generte scheduler function
    file.write("void srv_sys_os_seq_scheduler()\n")
    file.write("{\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        # insert loop recurent call
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("  if (--" +subfolder + "_rec_cnt <= 0)\n")
        file.write("  {\n")
        file.write("    " +subfolder + "_loop();\n")
        file.write("    " +subfolder + "_rec_cnt = "+subfolder.upper()+"_REC;\n")
        file.write("  }\n")
        file.write("#endif\n")

    file.write("}\n")

    file.write("\n")



    file.write("#ifdef ESP32\n")
    file.write("\n")
    file.write("// #define LED 21\n")
    file.write("hw_timer_t *Timer0_Cfg = NULL;\n")
    file.write("\n")
    file.write("void IRAM_ATTR srv_sys_os_seq_scheduler_isr()\n")
    file.write("{\n")
    file.write("  // digitalWrite(LED, !digitalRead(LED));\n")
    file.write("  srv_sys_os_seq_scheduler();\n")
    file.write("  //   Serial.println(\"OS\");\n")
    file.write("}\n")
    file.write("\n")
    file.write("void srv_sys_os_seq_setup_isr()\n")
    file.write("{\n")
    file.write("  // pinMode(LED, OUTPUT);\n")
    file.write("  Timer0_Cfg = timerBegin(0, 80, true);\n")
    file.write("  timerAttachInterrupt(Timer0_Cfg, &srv_sys_os_seq_scheduler_isr, true);\n")
    file.write("  timerAlarmWrite(Timer0_Cfg, SYS_TICK, true);\n")
    file.write("  timerAlarmEnable(Timer0_Cfg);\n")
    file.write("}\n")
    file.write("\n")
    file.write("#else\n")
    file.write("\n")
    file.write("#include <TimerOne.h>\n")
    file.write("// Interrupt service routine that will be called every 1ms\n")
    file.write("void srv_sys_os_seq_scheduler_isr()\n")
    file.write("{\n")
    file.write("  srv_sys_os_seq_scheduler();\n")
    file.write("}\n")
    file.write("\n")
    file.write("void srv_sys_os_seq_setup_isr()\n")
    file.write("{\n")
    file.write("  // Initialize Timer1 to trigger an interrupt every 1ms\n")
    file.write("  Timer1.initialize(1000);\n")
    file.write("  Timer1.attachInterrupt(srv_sys_os_seq_scheduler_isr);\n")
    file.write("}\n")
    file.write("#endif\n")



 
    file.write("\n")
    file.write("\n")

    file.close()


gen_srv_sys_os_seq()

