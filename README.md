<a href="https://esphome.io/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./logo-text-on-dark.svg", alt="ESPHome Logo">
    <img src="./logo-text-on-light.svg" alt="ESPHome Logo">
  </picture>
</a>

## BQ21088 component
<p> This external compoment allowes the control of the BQ21088 battery charger IC. </p>
<p> 
Lets set the battery voltage and charging Current
</p>
<p>
The necessary section of the device YAML not everything is needed
</p>

```
external_components:
  - source:
      type: git
      url: https://github.com/mhetzi/esphome_BQ21088.git
    components: [ bq21088 ]

i2c:
  sda: 22
  scl: 23
  scan: True
  id: bus_a
  frequency: 50kHz


bq21088:
  i2c_id: bus_a
  id: bq_test

switch:
  - platform: bq21088
    bq21088_id: bq_test
    charge_disable:
      name: Laden deaktivieren
    reduce_precharge:
      name: Precharge Voltage 2.8V

number:
  - platform: bq21088
    bq21088_id: bq_test
    vbat:
      name: Battery Endladespannung
    icgh:
      name: Battery Ladestrom
    buvlo:
      name: Battery Undervoltage Lockout

sensor:
  - platform: bq21088
    bq21088_id: bq_test
    charge_status:
      name: Ladezustand

binary_sensor:
  - platform: bq21088
    bq21088_id: bq_test
    vin_pwr_good:
      name: VIN Power good
    batt_ocp_fault:
      name: "Battery Overcurrent Protection"
    batt_uvlo_fault:
      name: "Battery Undervoltage Protection"


select:
  - platform: bq21088
    bq21088_id: bq_test
    safety_timer:
      name: Safety Timer
      device_id: charging_channel0

```

## Going further

- [esphome Developer documentation](https://developers.esphome.io)
- [esphome Component architecture overview](https://developers.esphome.io/architecture/components/)
