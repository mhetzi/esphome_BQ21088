import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']

CONF_BQ_ID = "bq21088_id"

bq21088_ns = cg.esphome_ns.namespace('bq21088')
BQ21088 = bq21088_ns.class_('BQ21088', cg.PollingComponent, i2c.I2CDevice)


CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BQ21088),
}).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(default_address=0x6A))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)
