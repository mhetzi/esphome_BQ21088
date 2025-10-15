import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number

from .. import (
    bq21088_ns,
    BQ21088,
    CONF_BQ_ID
)

DEPENDENCIES = ["BQ21088"]

BqNumber = bq21088_ns.class_("BqNumber", number.Number)
BqNumberTypeEnum = BqNumber.enum("NumberType", True)

CONF_ICHG = ("ICGH", 0.005, 1.0, 0.005)
CONF_VBAT = ("VBAT", 3.6, 4.65, 0.05)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BQ_ID): cv.use_id(BQ21088),
        cv.Optional(CONF_ICHG[0]): number.number_schema(
            BqNumber,

        ),
        cv.Optional(CONF_VBAT[0]): number.number_schema(
            BqNumber,

        ),
    })

async def to_code(config):
    parent = await cg.get_variable(config[CONF_BQ_ID])

    for sensor_type in [CONF_ICHG, CONF_VBAT]:
        if conf := config.get(sensor_type[0]):
            var = await number.new_number(conf, min_value=sensor_type[1], max_value=sensor_type[2], step=sensor_type[3])
            cg.add(var.set_parent(parent))
            sensor_type_value = getattr(BqNumberTypeEnum, sensor_type[0].upper())
            cg.add(var.set_type(sensor_type_value))
