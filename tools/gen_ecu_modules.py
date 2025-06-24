import os

from gen_utils import *

#generate recurenceses and offset for all modules
def generate_ecu_modules():
    directory = "src"  # Replace with the actual directory path
    subfolders = extract_subfolder_names(directory)
    file_name = "tools/generated/src/ecu_modules.h"

    # Create all subtrees from a path if they don't exist
    path = os.path.dirname(file_name)
    os.makedirs(path, exist_ok=True)


    except_list = ["srv_sig_cond"]

    file = open(file_name, "w")

    file.write("#ifndef ECU_MODULES_H\n")
    file.write("#define ECU_MODULES_H\n")
    file.write("\n")
    file.write("// Include any necessary libraries or headers here\n")
    file.write("\n")
    file.write("#include \"ecu_config.h\"\n")
    file.write("\n")
    file.write("//=============================================================================\n")
    file.write("// ECU Modules\n")
    file.write("//-----------------------------------------------------------------------------\n")



    for subfolder in subfolders:
        if subfolder in except_list:
            continue
        print(subfolder)
        file.write("#ifdef USE_"+subfolder.upper()+"\n")
        file.write("#include \""+ subfolder + "/"+ subfolder +".h\"\n")
        file.write("#endif\n")
        file.write("//-----------------------------------------------------------------------------\n")


    file.write("\n")
    file.write("\n")
    file.write("\n")
    file.write("// Declare any global variables or functions\n")
    file.write("\n")
    file.write("#endif // ECU_MODULES_H\n")
    file.close()


generate_ecu_modules()

