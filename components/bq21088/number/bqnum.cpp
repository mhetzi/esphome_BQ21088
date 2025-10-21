#include "bqnum.h"

static const char* TAG = "BQ21088.Number"; 

void esphome::bq21088::BqNumber::control(float value) {
    if (this->nt == NumberType::NT_UNKNOWN) {
        return;
    }

    switch (this->nt) {
        case NumberType::VBAT:{
            if (value < 3.6f || value > 4.65){
                ESP_LOGE(TAG, "control(%.3f): Is autside of range 3.6V - 4.65V", value);
            }
            auto vbat = this->parent->read_vbat_ctrl();
            vbat.set_vbat_reg_from_voltage(value);
            this->parent->write_vbat_ctrl(vbat);
            break;
        }
        case NumberType::ICGH: {
            if (value < 5 || value > 1000){
                ESP_LOGE(TAG, "control(%.3f): Is autside of range 5 - 1000mA", value);
            }
            auto icgh = this->parent->read_ichg_ctrl();
            icgh.set_charge_current_mA(value);
            this->parent->write_ichg_ctrl(icgh);
            break;
        }
        
        default:
            break;
    }

}

void esphome::bq21088::BqNumber::set_parent(BQ21088 *parent) {
    this->parent = parent;
}

void esphome::bq21088::BqNumber::set_type(NumberType nt) {
    this->nt = nt;
    ESP_LOGD(TAG, "I am now %d Type!", nt);
}
