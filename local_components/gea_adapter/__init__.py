import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import uart
import esphome.final_validate as fv


DEPENDENCIES = ["uart"]
MULTI_CONF = True

# gea_adapter:  
#   id: gea_adapter_ID
#   uart_id: uart_gea2
#   bus: gea2    is bus needed, the uart should be the same
#   appliance: dryer

CONF_GEA_ADAPTER_ID = "gea_adapter_id"
CONF_GEA_ADAPTER_TYPE = "appliance"

gea_adapter_ns = cg.esphome_ns.namespace("gea_adapter")

GEAAdapter = gea_adapter_ns.class_("GEAA_Component", cg.Component, uart.UARTDevice)


CONFIG_SCHEMA = cv.Schema(
    {
       cv.GenerateID(): cv.declare_id(GEAAdapter),
       
       cv.Required(CONF_GEA_ADAPTER_TYPE): cv.one_of("washer", "dryer", "dishwasher", upper=False),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)

GEAA_CHILD_SCHMEA = cv.Schema(
    {
        cv.GenerateID(CONF_GEA_ADAPTER_ID): cv.use_id(GEAAdapter),
    }
)


async def register_GEAA_child(var, config):
    parent = await cg.get_variable(config[CONF_GEA_ADAPTER_ID])
    cg.add(var.set_parent(parent))
    cg.add(parent.register_sensor(var))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    



# use hacked serial commands initially

    #    cv.Optional(CONF_GEA_ADAPTER_BUS, default="gea3"): cv.one_of("gea3", "gea2", upper=False),


    # #platformio library for GEA communication
    # cg.add_library(
    #     name="arduino-gea2",
    #     version="0.1.5",
    # )
    # cg.add_library(
    #     name="arduino-gea3",
    #     version="0.1.8",
    # )