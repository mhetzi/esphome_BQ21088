import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch

from .. import (
    bq21088_ns,
    BQ21088,
    CONF_BQ_ID
)

DEPENDENCIES = ["bq21088"]

BqSwitch = bq21088_ns.class_("BqSwitch", switch.Switch)
BqSwitchTypeEnum = bq21088_ns.enum("SwitchType", True)

CONF_CHG = "CHARGE_DISABLE"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BQ_ID): cv.use_id(BQ21088),
        cv.Optional(CONF_CHG.lower()): switch.switch_schema(
            BqSwitch,

        ),
    })

async def to_code(config):
    parent = await cg.get_variable(config[CONF_BQ_ID])

    for switch_type in [CONF_CHG]:
        if conf := config.get(switch_type.lower()):
            var = await switch.new_switch(conf)
            cg.add(var.set_parent(parent))
            sensor_type_value = getattr(BqSwitchTypeEnum, switch_type.upper())
            cg.add(var.set_type(sensor_type_value))

            if switch_type == CONF_CHG:
                cg.add(parent.setChargeDisabledSwitch(var))
