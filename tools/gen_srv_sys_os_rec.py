import os

from gen_utils import *


#generate recurenceses and offset for all modules
def generate_rec_offset():
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/srv_sys_os/srv_sys_os.h"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)

    default_REC = 10
    incremental_OFFSET = 0
    except_list = ["srv_sys_os","srv_sig_cond"]

    file = open(file_name, "w")

    file.write("#ifndef SRV_SYS_OS_H\n")
    file.write("#define SRV_SYS_OS_H\n")
    file.write("\n")
    file.write("// Include any necessary libraries or headers\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("\n")
    file.write("// Define any constants or macros\n")
    file.write("\n")
    file.write("\n")
    file.write("\n")
    file.write("//=============================================================================\n")
    file.write("// time base definitions\n")
    file.write("//-----------------------------------------------------------------------------\n")
    file.write("#ifdef SYS_TICK\n")
    file.write("#define SYS_TICK (10.0)\n")
    file.write("#endif\n")
    file.write("#ifndef TIME_SEC\n")
    file.write("#define TIME_SEC (1000 )\n")
    file.write("#endif\n")
    file.write("#ifndef TIME_MIN\n")
    file.write("#define TIME_MIN (60 * TIME_SEC)\n")
    file.write("#endif\n")
    file.write("#ifndef TIME_HOUR\n")
    file.write("#define TIME_HOUR (60 * TIME_MIN)\n")
    file.write("#endif\n")
    file.write("#ifndef TIME_DAY\n")
    file.write("#define TIME_DAY (24 * TIMTIME_HOUR)   \n")
    file.write("#endif\n")
    file.write("\n")
    file.write("//=============================================================================\n")
    file.write("// Task Scheduling definitions\n")
    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        incremental_OFFSET += 1
        print(subfolder)
        file.write("//-----------------------------------------------------------------------------\n")
        file.write("#ifdef USE_" +subfolder.upper()+"\n")
        file.write("#ifndef " +subfolder.upper()+"_REC\n")
        file.write("#define " +subfolder.upper()+"_REC (" +str(default_REC)+" / SYS_TICK)\n")
        file.write("#endif\n")
        file.write("#ifndef " +subfolder.upper()+"_OFFSET\n")
        file.write("#define " +subfolder.upper()+"_OFFSET (" +str(incremental_OFFSET)+" / SYS_TICK)\n")
        file.write("#endif\n")
        file.write("#endif\n")

    file.write("//-----------------------------------------------------------------------------\n")
    file.write("\n")
    file.write("\n")
    file.write("\n")
    file.write("// Declare any global variables or functions\n")
    file.write("\n")
    file.write("#endif // SRV_SYS_OS_H\n")
    file.close()


generate_rec_offset()

