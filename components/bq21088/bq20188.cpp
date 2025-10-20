#include "bq20188.h"

namespace esphome {
namespace bq21088 {
const char *TAG = "bq21088";

void BQ21088::dump_config() {
  ESP_LOGCONFIG(TAG, "BQ21088:");
  LOG_I2C_DEVICE(this);
  auto stat0 = this->read_stat0();
  ESP_LOGCONFIG(TAG, "  VIN_PGOOD_STAT: %s", BootToGoodString(stat0.VIN_PGOOD_STAT));
  ESP_LOGCONFIG(TAG, "  THERMREG_ACTIVE_STAT: %s", BoolToActiveString(stat0.THERMREG_ACTIVE_STAT));
  ESP_LOGCONFIG(TAG, "  VINDPM_ACTIVE_STAT: %s", BoolToActiveString(stat0.VINDPM_ACTIVE_STAT));
  ESP_LOGCONFIG(TAG, "  VDPPM_ACTIVE_STAT: %s", BoolToActiveString(stat0.VDPPM_ACTIVE_STAT));
  ESP_LOGCONFIG(TAG, "  ILIM_ACTIVE_STAT: %s", BoolToActiveString(stat0.ILIM_ACTIVE_STAT));
  ESP_LOGCONFIG(TAG, "  CHG_STAT: %s", BoolToActiveString(stat0.get_chg_status_string()));
  ESP_LOGCONFIG(TAG, "  TS_OPEN_STAT: %s", BoolToActiveString(stat0.TS_OPEN_STAT));

  auto vbat = this->read_vbat_ctrl();
  ESP_LOGCONFIG(TAG, "  VBAT_REG: %.3f", vbat.get_vbat_reg_voltage());

  auto icgh = this->read_ichg_ctrl();
  ESP_LOGCONFIG(TAG, "  ICHG: %u mA", icgh.get_charge_current_mA());
  ESP_LOGCONFIG(TAG, "  CHG_DIS: %s", BooleanToString(icgh.CHG_DIS));

  auto sys = this->read_sys_reg();
  ESP_LOGCONFIG(TAG, "  VDPPM_DIS: %s", BooleanToString(sys.VDPPM_DIS));
  ESP_LOGCONFIG(TAG, "  WATCHDOG_15S_ENABLE: %s", BooleanToString(sys.WATCHDOG_15S_ENABLE));
  ESP_LOGCONFIG(TAG, "  SYS_MODE: %s", sys.get_sys_mode_string());
  ESP_LOGCONFIG(TAG, "  PG_GPO: %s", BooleanToString(sys.PG_GPO));
  ESP_LOGCONFIG(TAG, "  SYS_REG_CTRL: %s", sys.get_sys_reg_string());

}

STAT0 BQ21088::read_stat0() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x0, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading STAT0 register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return STAT0(reg);
}

STAT1 BQ21088::read_stat1() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x1, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading STAT1 register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return STAT1(reg);
}

 FLAG0 BQ21088::read_flag0() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x2, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading FLAG0 register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return FLAG0(reg);
}


VBAT_CTRL BQ21088::read_vbat_ctrl() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x3, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading VBAT_CTRL register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return VBAT_CTRL(reg);
}

esphome::i2c::ErrorCode BQ21088::write_vbat_ctrl(const VBAT_CTRL &vbat_ctrl) {
  const uint8_t val = vbat_ctrl.to_uint8();
  return this->write_register(0x3, &val, 1);
}


ICHG_CTRL BQ21088::read_ichg_ctrl() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x4, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading ICHG_CTRL register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return ICHG_CTRL(reg);
}

esphome::i2c::ErrorCode BQ21088::write_ichg_ctrl(const ICHG_CTRL &ichg_ctrl) {
  const uint8_t val = ichg_ctrl.to_uint8();
  return this->write_register(0x4, &val, 1);
}

CHARGECTRL0 BQ21088::read_chargectl0() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x5, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading CHARGECTRL0 register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return CHARGECTRL0(reg);
}

esphome::i2c::ErrorCode BQ21088::write_chargectl0(const CHARGECTRL0 &chargectl0) {
  const uint8_t val = chargectl0.to_uint8();
  return this->write_register(0x5, &val, 1);
}

CHARGECTRL1 BQ21088::read_chargectl1() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x6, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading CHARGECTRL1 register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return CHARGECTRL1(reg);
}

esphome::i2c::ErrorCode BQ21088::write_chargectl1(const CHARGECTRL1 &chargectl1) {
  const uint8_t val = chargectl1.to_uint8();
  return this->write_register(0x6, &val, 1);
}

IC_CTRL BQ21088::read_ic_ctrl() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x7, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading IC_CTRL register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return IC_CTRL(reg);
}

esphome::i2c::ErrorCode BQ21088::write_ic_ctrl(const IC_CTRL &ic_ctrl) {
  const uint8_t val = ic_ctrl.to_uint8();
  return this->write_register(0x7, &val, 1);
}

TMR_ILIM BQ21088::read_tmr_ilim() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0x8, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading TMR_ILIM register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return TMR_ILIM(reg);
}
esphome::i2c::ErrorCode BQ21088::write_tmr_ilim(const TMR_ILIM &tmr_ilim) {
  const uint8_t val = tmr_ilim.to_uint8();
  return this->write_register(0x8, &val, 1);
}

SYS_REG BQ21088::read_sys_reg() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0xA, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading SYS_REG register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return SYS_REG(reg);
}
esphome::i2c::ErrorCode BQ21088::write_sys_reg(const SYS_REG &sys_reg) {
  const uint8_t val = sys_reg.to_uint8();
  return this->write_register(0xA, &val, 1);
}

MASK_ID BQ21088::read_mask_id() {
  uint8_t reg = 0;
  esphome::i2c::ErrorCode err = this->read_register(0xC, &reg, 1);
  if (err != esphome::i2c::ErrorCode::NO_ERROR) {
    ESP_LOGE(TAG, "Error reading MASK_ID register: %d", err);
    this->status_set_warning("I2C read error");
  }
  return MASK_ID(reg);
}
esphome::i2c::ErrorCode BQ21088::write_mask_id(const MASK_ID &mask_id) {
  const uint8_t val = mask_id.to_uint8();
  return this->write_register(0xC, &val, 1);
}

void bootstrap_alarm(BQ21088* self){
  self->update();
}

void BQ21088::setAlarmInput(esphome::InternalGPIOPin *alarm_pin){
  this->alarm_pin = alarm_pin;
  if (alarm_pin == nullptr){
    return;
  }
  if (alarm_pin->is_internal()){
    alarm_pin->attach_interrupt(&bootstrap_alarm, this, gpio::InterruptType::INTERRUPT_LOW_LEVEL);
  }
}

void BQ21088::setup() {
  
}

void BQ21088::update() {
  #ifdef USE_BINARY_SENSOR
  auto flags = this->read_flag0();
  if (this->bat_ocp_fault_sensor_ != nullptr) {
    this->bat_ocp_fault_sensor_->publish_state(flags.BAT_OCP_FAULT);
  }
  if (this->buvlo_fault_sensor_ != nullptr) {
    this->buvlo_fault_sensor_->publish_state(flags.BUVLO_FAULT_FLAG);
  }
  if (this->vin_pgood_sensor_ != nullptr) {
    this->vin_pgood_sensor_->publish_state(flags.VIN_OVP_FAULT_FLAG);
  }
  #endif

  #if defined(USE_NUMBER) || defined(USE_SWITCH) 
  auto icgh = this->read_ichg_ctrl();
  #endif

  #ifdef USE_NUMBER
  if (this->ichg_number_ != nullptr){
    this->ichg_number_->publish_state(icgh.get_charge_current_mA());
  }
  if (this->vbat_reg_number_ != nullptr) {
    auto vbat = this->read_vbat_ctrl();
    this->vbat_reg_number_->publish_state(vbat.get_vbat_reg_voltage());
  }
  #endif

  #ifdef USE_SWITCH
  if (this->chg_disable_switch_ != nullptr) {
    this->chg_disable_switch_->publish_state(icgh.CHG_DIS);
  }
  #endif

  #ifdef USE_SENSOR
  if (this->chg_status_sensor_ != nullptr) {
    auto stat0 = this->read_stat0();
    this->chg_status_sensor_->publish_state(stat0.CHG_STAT);
  }
  #endif
}

} // namespace bq21088
} // namespace esphome
