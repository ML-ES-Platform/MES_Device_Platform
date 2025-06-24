import os
import json

from gen_utils import *



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


gen_units()

