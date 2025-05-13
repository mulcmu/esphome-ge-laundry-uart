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
CONF_GEA_ADAPTER_DESTINATION = "destination"
CONF_GEA_ADAPTER_SOURCE = "source"

gea_adapter_ns = cg.esphome_ns.namespace("gea_adapter")

GEAAdapter = gea_adapter_ns.class_("GEAA_Component", cg.PollingComponent, uart.UARTDevice)


CONFIG_SCHEMA = cv.Schema(
    {
       cv.GenerateID(): cv.declare_id(GEAAdapter),
       cv.Required(CONF_GEA_ADAPTER_TYPE): cv.one_of("washer", "dryer", "dishwasher", upper=False),
       cv.Optional(CONF_GEA_ADAPTER_DESTINATION, default=0x24): cv.hex_int_range(min=0x01, max=0xDF),
       cv.Optional(CONF_GEA_ADAPTER_SOURCE, default=0xBB): cv.hex_int_range(min=0x01, max=0xDF),
    }
).extend(uart.UART_DEVICE_SCHEMA).extend(cv.polling_component_schema("5s")).extend(cv.COMPONENT_SCHEMA)

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
    await uart.register_uart_device(var, config)
    cg.add(var.set_destination_address(config[CONF_GEA_ADAPTER_DESTINATION]))
    cg.add(var.set_source_address(config[CONF_GEA_ADAPTER_SOURCE]))
    



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