import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.final_validate as fv
from esphome.components import binary_sensor
from esphome.const import CONF_ID

from .. import gea_adapter_ns, GEAA_CHILD_SCHMEA, CONF_GEA_ADAPTER_ID, register_GEAA_child

DEPENDENCIES = ["gea_adapter"]

GEAABinarySensor = gea_adapter_ns.class_(
    "GEAABinarySensor", binary_sensor.BinarySensor, cg.Component
)
SensorType = gea_adapter_ns.enum("SensorType")

CONF_TYPE = "type"
TYPES = {
    "door": SensorType.GEAA_SENSOR_DOOR,
    "door_lock": SensorType.GEAA_SENSOR_DOORLOCK,
    "complete": SensorType.GEAA_SENSOR_CYCLE_COMPLETE,
    "unbalanced": SensorType.GEAA_SENSOR_UNBALANCED,
}

CONF_ERD = "erd"

CONF_VALID_DRYER_TYPES = [
    "complete",
    "door",]

CONF_VALID_WASHER_TYPES = [
    "complete",
    "door",
    "door_lock",
    "unbalanced"
]

CONF_VALID_DISHWASHER_TYPES = [
    
]

CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(GEAABinarySensor)
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
            if config["type"] not in CONF_VALID_DRYER_TYPES:
                raise cv.Invalid(
                    f"Sensor {config['type']} is not a valid option for {appliance_type}."
                )                    
            if config["type"] == "complete":
                config["erd"] = 0x2002
            elif config["type"] == "door":
                config["erd"] = 0x2012
            else:
                raise cv.Invalid(
                    f"Missing ERD for '{appliance_type}' sensor type '{config['type']}'. \nNotify code owner: Default ERD needs added to final validate check logic."
                )
    elif appliance_type == "washer":
        if config["type"] not in CONF_VALID_WASHER_TYPES:
            raise cv.Invalid(f"{config['type']} is not a valid option for appliance type {appliance_type}.")
        
        if "erd" not in config:
            if config["type"] == "door_lock":
                config["erd"] = 0x2013
            elif config["type"] == "complete":
                config["erd"] = 0x2002
            elif config["type"] == "door":
                config["erd"] = 0x2012 
            elif config["type"] == "unbalanced":
                config["erd"] = 0x20A6                
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
    await binary_sensor.register_binary_sensor(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_binary_sensor_type(config[CONF_TYPE]))
    cg.add(var.set_erd(config[CONF_ERD]))    
    await register_GEAA_child(var, config)

