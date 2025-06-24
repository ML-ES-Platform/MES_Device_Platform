import os
import json



json_stuct = {
    "components": {
        "srv_sns_soil_moist": {
            "type": "Sensor",
            "description": "Soil Moisture Sensor",
            "config": {
                "pin": "A0"
            },
            "meta": {
                "author": "SmartGrow"
            },
            "signals": {
                "moisture": {
                    "signal_name": "moisture",
                    "units": "%",
                    "signal_dir": "output",
                    "default_value": "0.0",
                    "dependency": "ed_sns_soil_moist"
                }
            },
            "features": []
        }
    }
}

def extract_subfolder_names(directory):
    """
    Extracts the names of subfolders in the given directory.
    Args:
        directory (str): The directory to extract subfolder names from.
    Returns:
        list: A list of subfolder names.
    """
    subfolder_names = []
    for root, dirs, files in os.walk(directory):
        for dir in dirs:
            subfolder_names.append(dir)
    return subfolder_names


def file_to_json(file_name):
    if os.path.exists(file_name):
        with open(file_name, "r", encoding="utf-8") as file:
            # Parse the content and convert it to JSON
            json_data = json.load(file)
            # # Print the first level keys
            # for key in json_data.keys():
            #     print(key)    
            return json_data
    else:
        return {}

def config_get_components(config_json):
    components = {}
    if "components" in config_json:
        components = config_json["components"]
    return components

def config_get_component_name(component_json):
    component_name = ""
    if "component_name" in component_json:
        component_name = component_json["component_name"]
    else:
        component_name = component_json
    return component_name

def config_get_components_json(config_json):
    components_json = {}
    if "components" in config_json:
        components_json = config_json["components"]
    return components_json

def config_get_component_json(component_name, config_json):
    component_json = {}
    components_json = config_get_components_json(config_json)
    
    if component_name in components_json:
        component_json = components_json[component_name]
    return component_json

def config_get_signals( component_json):
    signals = {}
    if "signals" in component_json:
        signals = component_json["signals"]
    return signals

def config_get_signal_name(signal_json):
    signal_name = ""

    if "signal_name" in signal_json:
        signal_name = signal_json["signal_name"]
    else:
        signal_name = signal_json
    return signal_name

def config_get_signal_dir(signal_json):
    signal_dir = ""
    if "signal_dir" in signal_json:
        signal_dir = signal_json["signal_dir"]
    else:
        signal_dir = "generic"
    return signal_dir
    
def config_get_signal_units(signal_json):
    signal_units = ""

    if "units" in signal_json:
        signal_units = signal_json["units"]
    else:
        signal_units = "generic"
    return signal_units
    
def config_get_signal_default_value(signal_json):
    signal_default_value = ""

    if "default_value" in signal_json:
        signal_default_value = signal_json["default_value"]
    else:
        signal_default_value = "0.0"
    return signal_default_value

def config_get_signal_dependency(signal_json):
    signal_dependency = ""
    if "dependency" in signal_json:
        signal_dependency = signal_json["dependency"]
    else:
        signal_dependency = ""
    return signal_dependency

def config_get_signal_type(signal_json):
    signal_type = ""
    if "type" in signal_json:
        signal_type = signal_json["type"]
    else:
        signal_type = "float"
    return signal_type
