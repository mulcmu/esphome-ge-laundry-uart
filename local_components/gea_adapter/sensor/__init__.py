import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.final_validate as fv
from esphome.components import sensor
from esphome.const import CONF_ID

from .. import gea_adapter_ns, GEAA_CHILD_SCHMEA, CONF_GEA_ADAPTER_ID, register_GEAA_child

DEPENDENCIES = ["gea_adapter"]

GEAASensor = gea_adapter_ns.class_("GEAASensor", sensor.Sensor, cg.Component)
GEAASensorType = gea_adapter_ns.enum("GEAASensorType")

CONF_TYPE = "type"
TYPES = {
    "remaining_cycle_time": GEAASensorType.GEAA_REMAINING_CYCLE_TIME,
    "total_cycles":    GEAASensorType.GEAA_TOTOAL_CYCLES,
}

CONF_ERD = "erd"

CONF_VALID_DRYER_TYPES = [
    "remaining_cycle_time",
    "total_cycles",
]

CONF_VALID_WASHER_TYPES = [
    "remaining_cycle_time",
    "total_cycles",
]

CONF_VALID_DISHWASHER_TYPES = [
    
]

CONFIG_SCHEMA = (
    sensor.sensor_schema(GEAASensor)
    .extend(
        {
            cv.Required(CONF_TYPE): cv.enum(TYPES, lower=True),
        }
    )
    .extend(GEAA_CHILD_SCHMEA)
)

def default_erds(config):
    fc = fv.full_config.get()
    appliance_type = fc.get("gea_adapter", [{}])[0].get("appliance", None)
    if appliance_type is None:
        raise cv.Invalid("ERROR: Appliance type not found in configuration.")
    
    if appliance_type == "dryer":
        if config["type"] not in CONF_VALID_DRYER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
        if "erd" not in config:
            if config["type"] == "remaining_cycle_time":
                config["erd"] = 0x2007
            elif config["type"] == "total_cycles":
                config["erd"] = 0x2003
            else:
                raise cv.Invalid(
                    f"Missing ERD for '{appliance_type}' sensor type '{config['type']}'. \nNotify code owner: Default ERD needs added to final validate check logic."
                )
    elif appliance_type == "washer":
        if config["type"] not in CONF_VALID_WASHER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
        if "erd" not in config:
            if config["type"] == "remaining_cycle_time":
                config["erd"] = 0x2007
            elif config["type"] == "total_cycles":
                config["erd"] = 0x2003
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
    await sensor.register_sensor(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_sensor_type(config[CONF_TYPE]))
    cg.add(var.set_erd(config[CONF_ERD]))    
    await register_GEAA_child(var, config)
