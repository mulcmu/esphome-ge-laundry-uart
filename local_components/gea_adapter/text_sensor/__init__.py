import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.final_validate as fv
from esphome.components import text_sensor
from esphome.const import CONF_ID
from .. import gea_adapter_ns, GEAA_CHILD_SCHMEA, CONF_GEA_ADAPTER_ID,CONF_GEA_ADAPTER_TYPE , register_GEAA_child

DEPENDENCIES = ["gea_adapter"]

GEAATextSensor = gea_adapter_ns.class_(
    "GEAATextSensor", text_sensor.TextSensor, cg.Component
)

TextSensorType = gea_adapter_ns.enum("TextSensorType")

CONF_TYPE = "type"
TYPES = {
    "state": TextSensorType.GEAA_SENSOR_STATE,
    "sub_state": TextSensorType.GEAA_SENSOR_SUB_STATE,
    "cycle": TextSensorType.GEAA_SENSOR_CYCLE,
    "dryness_setting": TextSensorType.GEAA_SENSOR_DRYNESS_SETTING,
    "heat_setting": TextSensorType.GEAA_SENSOR_HEAT_SETTING,
    "rinse_setting": TextSensorType.GEAA_SENSOR_RINSE_SETTING,
    "soil_setting": TextSensorType.GEAA_SENSOR_SOIL_SETTING,
    "spin_setting": TextSensorType.GEAA_SENSOR_SPIN_SETTING,
    "temp_setting": TextSensorType.GEAA_SENSOR_TEMP_SETTING,
}

CONF_ERD = "erd"

CONF_VALID_DRYER_TYPES = [
    "state",
    "sub_state",
    "cycle",
    "dryness_setting",
    "heat_setting",
]

CONF_VALID_WASHER_TYPES = [
    "state",
    "sub_state",
    "cycle",
    "rinse_setting",
    "soil_setting",
    "spin_setting",
    "temp_setting",
]
CONF_VALID_DISHWASHER_TYPES = [

]

CONFIG_SCHEMA = text_sensor.text_sensor_schema(GEAATextSensor).extend(
    {
        cv.Required(CONF_TYPE): cv.enum(TYPES, lower=True),
        cv.Optional(CONF_ERD): cv.hex_int_range(min=0x2000, max=0x2222),
    }
).extend(GEAA_CHILD_SCHMEA)

def default_erds(config):
    fc = fv.full_config.get()
    appliance_type = fc.get("gea_adapter", [{}])[0].get("appliance", None)
    if appliance_type is None:
        raise cv.Invalid("ERROR: Appliance type not found in configuration.")
    
    if appliance_type == "dryer":
        if config["type"] not in CONF_VALID_DRYER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
        if "erd" not in config:
            if config["type"] == "state":
                config["erd"] = 0x2000
            elif config["type"] == "sub_state":
                config["erd"] = 0x2001
            elif config["type"] == "cycle":
                config["erd"] = 0x200A
            elif config["type"] == "dryness_setting":
                config["erd"] = 0x204d
            elif config["type"] == "heat_setting":
                senconfigsor["erd"] = 0x2050
            else:
                raise cv.Invalid(
                    f"Missing ERD for '{appliance_type}' sensor type '{config['type']}'. \nNotify code owner: Default ERD needs added to final validate check logic."
                )
    elif appliance_type == "washer":
        if config["type"] not in CONF_VALID_WASHER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
        if "erd" not in config:
            if config["type"] == "state":
                config["erd"] = 0x2000
            elif config["type"] == "sub_state":
                config["erd"] = 0x2001
            elif config["type"] == "cycle":
                config["erd"] = 0x200A
            elif config["type"] == "rinse_setting":
                config["erd"] = 0x2018
            elif config["type"] == "soil_setting":
                config["erd"] = 0x2015
            elif config["type"] == "spin_setting":
                config["erd"] = 0x2017
            elif config["type"] == "temp_setting":
                config["erd"] = 0x2016
            else:
                raise cv.Invalid(
                    f"Missing ERD for '{appliance_type}' sensor type '{config['type']}'. \nNotify code owner: Default ERD needs added to final validate check logic."
                )
                      
    elif appliance_type == "dishwasher":
        if config["type"] not in CONF_VALID_DISHWASHER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
    return config

FINAL_VALIDATE_SCHEMA = cv.All(default_erds)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await text_sensor.register_text_sensor(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_text_sensor_type(config[CONF_TYPE]))
    await register_GEAA_child(var, config)