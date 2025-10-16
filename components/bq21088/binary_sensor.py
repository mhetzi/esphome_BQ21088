import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC, ENTITY_CATEGORY_NONE, DEVICE_CLASS_POWER, DEVICE_CLASS_PROBLEM

from . import (
    bq21088_ns,
    BQ21088,
    CONF_BQ_ID
)

DEPENDENCIES = ["bq21088"]

CONF_VIN_POWER_GOOD = "vin_pwr_good"
CONF_OCP_FAULT = "batt_ocp_fault"
CONF_BUVLO_FAULT = "batt_uvlo_fault"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BQ_ID): cv.use_id(BQ21088),
        cv.Optional(CONF_VIN_POWER_GOOD): binary_sensor.binary_sensor_schema(
            entity_category=ENTITY_CATEGORY_NONE,
            device_class=DEVICE_CLASS_POWER
        ),
        cv.Optional(CONF_OCP_FAULT): binary_sensor.binary_sensor_schema(
            entity_category=ENTITY_CATEGORY_NONE,
            device_class=DEVICE_CLASS_PROBLEM
        ),
        cv.Optional(CONF_BUVLO_FAULT): binary_sensor.binary_sensor_schema(
            entity_category=ENTITY_CATEGORY_NONE,
            device_class=DEVICE_CLASS_PROBLEM
        ),
    })

async def to_code(config):
    parent = await cg.get_variable(config[CONF_BQ_ID])

    for sens in [CONF_VIN_POWER_GOOD, CONF_OCP_FAULT]:
        if conf := config.get(sens):
            var = await binary_sensor.new_binary_sensor(conf)
            if sens == CONF_VIN_POWER_GOOD:
                cg.add(parent.setVinPgood(var))
            elif sens == CONF_OCP_FAULT:
                cg.add(parent.setBatOcPFault(var))
            elif sens == CONF_OCP_FAULT:
                cg.add(parent.setBuvloFault(var))
            else:
                print("bq21088 no valid sensor in match case!")
                
