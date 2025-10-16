import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import (
    bq21088_ns,
    BQ21088,
    CONF_BQ_ID
)

DEPENDENCIES = ["bq21088"]

CONF_CHG_STAT = "charge_status"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BQ_ID): cv.use_id(BQ21088),
        cv.Optional(CONF_CHG_STAT): sensor.sensor_schema(
            accuracy_decimals=0,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC
        ),
    })

async def to_code(config):
    parent = await cg.get_variable(config[CONF_BQ_ID])

    for sens in [CONF_CHG_STAT]:
        if conf := config.get(sens):
            var = await sensor.new_sensor(conf)
            if sens == CONF_CHG_STAT:
                cg.add(parent.setChgStatus(var))
            else:
                print("bq21088 no valid sensor in match case!")
                
