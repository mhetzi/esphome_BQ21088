#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/log.h"
#include "bq20188_reg.h"
#include "esphome/core/defines.h"
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif
#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif

#include "esphome/core/gpio.h"
#include <optional>

namespace esphome {
namespace bq21088 {

#define BooleanToString(b) ((b) ? "true" : "false")
#define BootToGoodString(b) ((b) ? "Good" : "Not Good")
#define BoolToActiveString(b) ((b) ? "Active" : "Not Active")

class BQ21088 : public PollingComponent, public i2c::I2CDevice {
 public:
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::DATA; }
    void update() override;

    // BQ21088 specific functions
    std::optional<STAT0> read_stat0();
    std::optional<STAT1> read_stat1();
    std::optional<FLAG0> read_flag0();
    std::optional<VBAT_CTRL> read_vbat_ctrl();
    esphome::i2c::ErrorCode write_vbat_ctrl(const VBAT_CTRL &vbat_ctrl);
    std::optional<ICHG_CTRL> read_ichg_ctrl();
    esphome::i2c::ErrorCode write_ichg_ctrl(const ICHG_CTRL &ichg_ctrl);
    std::optional<CHARGECTRL0> read_chargectl0();
    esphome::i2c::ErrorCode write_chargectl0(const CHARGECTRL0 &chargectl0);
    std::optional<CHARGECTRL1> read_chargectl1();
    esphome::i2c::ErrorCode write_chargectl1(const CHARGECTRL1 &chargectl1);
    std::optional<IC_CTRL> read_ic_ctrl();
    esphome::i2c::ErrorCode write_ic_ctrl(const IC_CTRL &ic_ctrl);
    std::optional<TMR_ILIM> read_tmr_ilim();
    esphome::i2c::ErrorCode write_tmr_ilim(const TMR_ILIM &tmr_ilim);
    std::optional<SYS_REG> read_sys_reg();
    esphome::i2c::ErrorCode write_sys_reg(const SYS_REG &sys_reg);
    std::optional<MASK_ID> read_mask_id();
    esphome::i2c::ErrorCode write_mask_id(const MASK_ID &mask_id);

    #ifdef USE_BINARY_SENSOR
    void setVinPgood(binary_sensor::BinarySensor *vin_pgood_sensor_){
      this->vin_pgood_sensor_ = vin_pgood_sensor_;
    };
    void setBatOcPFault(binary_sensor::BinarySensor *bat_ocp_fault_sensor_){
      this->bat_ocp_fault_sensor_ = bat_ocp_fault_sensor_;
    };
    void setBuvloFault(binary_sensor::BinarySensor *buvlo_fault_sensor_){
      this->buvlo_fault_sensor_ = buvlo_fault_sensor_;
    };
    #endif

    #ifdef USE_NUMBER
    void setVbatReg   (number::Number *vbat_reg_number_   ) {this->vbat_reg_number_   = vbat_reg_number_;};
    void setIcgh      (number::Number *ichg_number_       ) {this->ichg_number_       = ichg_number_;};
    void setBuvlo     (number::Number *buvlo_number_      ) {this->buvlo_number_      = buvlo_number_;};
    #endif
    #ifdef USE_SENSOR
    void setChgStatus (sensor::Sensor *chg_status_sensor_ ) {this->chg_status_sensor_ = chg_status_sensor_;};
    #endif
    #ifdef USE_SWITCH
    void setChargeDisabledSwitch(switch_::Switch *sw) { this->chg_disable_switch_ = sw; };
    void setVlowvSwitch(switch_::Switch *sw)          { this->vlow_reduce_ = sw; };
    #endif
    #ifdef USE_SELECT
    void setSafetyTimerSelect(select::Select *select) { this->safety_timer_select_ = select; };
    #endif

    void setAlarmInput(esphome::InternalGPIOPin *alarm_pin);

 private:
   
    #ifdef USE_BINARY_SENSOR
    binary_sensor::BinarySensor *vin_pgood_sensor_{nullptr};
    binary_sensor::BinarySensor *bat_ocp_fault_sensor_{nullptr};
    binary_sensor::BinarySensor *buvlo_fault_sensor_{nullptr};
    #endif

    #ifdef USE_NUMBER
    number::Number *vbat_reg_number_{nullptr};
    number::Number *ichg_number_{nullptr};
    number::Number *buvlo_number_{nullptr};
    #endif
    #ifdef USE_SENSOR
    sensor::Sensor *chg_status_sensor_{nullptr};
    #endif

    #ifdef USE_SWITCH
    switch_::Switch *chg_disable_switch_{nullptr};
    switch_::Switch *vlow_reduce_{nullptr};
    #endif

    #ifdef USE_SELECT
    select::Select *safety_timer_select_{nullptr};
    #endif

    esphome::InternalGPIOPin *alarm_pin{nullptr};
};

} // namespace bq21088
} // namespace esphomeS