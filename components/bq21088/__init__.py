import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID
from esphome import pins

DEPENDENCIES = ['i2c']

CONF_BQ_ID = "bq21088_id"
CONF_PIN = "int_pin"

bq21088_ns = cg.esphome_ns.namespace('bq21088')
BQ21088 = bq21088_ns.class_('BQ21088', cg.PollingComponent, i2c.I2CDevice)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BQ21088),
    cv.Optional(CONF_PIN): pins.internal_gpio_input_pin_schema
}).extend(cv.polling_component_schema("1min")).extend(i2c.i2c_device_schema(default_address=0x6A))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    if CONF_PIN in config.keys():
        pin = await cg.gpio_pin_expression(config[CONF_PIN])
        cg.add(var.setAlarmInput(pin))
