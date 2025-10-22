import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select

from .. import (
    bq21088_ns,
    BQ21088,
    CONF_BQ_ID
)

DEPENDENCIES = ["bq21088"]

BqSelect = bq21088_ns.class_("BqSelect", select.Select)
BqSelectTypeEnum = bq21088_ns.enum("BQ_SelectType", True)

CONF_SAFETY = ["SAFETY_TIMER", ("3h", "6h", "12h", "disabled")]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BQ_ID): cv.use_id(BQ21088),
        cv.Optional(CONF_SAFETY[0].lower()): select.select_schema(
            BqSelect,
        ),
    })

async def to_code(config):
    parent = await cg.get_variable(config[CONF_BQ_ID])

    for switch_type in [CONF_SAFETY]:
        if conf := config.get(switch_type[0].lower()):
            var = await select.new_select(conf, options=switch_type[1])
            cg.add(var.set_parent(parent))
            sensor_type_value = getattr(BqSelectTypeEnum, switch_type[0].upper())
            cg.add(var.set_type(sensor_type_value))

            if switch_type == CONF_SAFETY:
                cg.add(parent.setSafetyTimerSelect(var))
