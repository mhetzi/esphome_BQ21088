#include "bqnum.h"

static const char* TAG = "BQ21088.Number"; 

namespace esphome
{
namespace bq21088
{

    void BqNumber::control(float value) {
        if (this->nt == NumberType::NT_UNKNOWN) {
            return;
        }

        switch (this->nt) {
            case NumberType::VBAT:{
                if (value < 3.6f || value > 4.65){
                    ESP_LOGE(TAG, "control(%.3f): Is autside of range 3.6V - 4.65V", value);
                }
                auto vbat = this->parent->read_vbat_ctrl();
                if (!vbat)
                    return;
                vbat->set_vbat_reg_from_voltage(value);
                this->parent->write_vbat_ctrl(vbat.value());
                break;
            }
            case NumberType::ICGH: {
                if (value > 0.005 && value <= 1.0f){
                    value *= 1000;
                }
                
                if (value < 5 || value > 1000){
                    ESP_LOGE(TAG, "control(%.3f): Is autside of range 5 - 1000mA", value);
                }
                auto icgh = this->parent->read_ichg_ctrl();
                if (!icgh)
                    return;
                icgh->set_charge_current_mA(value);
                this->parent->write_ichg_ctrl(icgh.value());
                break;
            }
            case NumberType::BUVLO: {
                this->setBuvlo(value);
                break;
            }
            
            default:
                break;
        }

    }

    void BqNumber::set_parent(BQ21088 *parent) {
        this->parent = parent;
    }

    void BqNumber::set_type(NumberType nt) {
        this->nt = nt;
    }
    void BqNumber::setBuvlo(float val) {
        auto reg = this->parent->read_chargectl1();
        if (!reg)
            return;
        if (val == 3.0f){
            reg->BUVLO = BUVLO_t::BUVLO_3V0;
        } else if (val == 2.8f){
            reg->BUVLO = BUVLO_t::BUVLO_2V8;
        } else if (val == 2.6f){
            reg->BUVLO = BUVLO_t::BUVLO_2V6;
        } else if (val == 2.4f){
            reg->BUVLO = BUVLO_t::BUVLO_2V4;
        } else if (val == 2.2f){
            reg->BUVLO = BUVLO_t::BUVLO_2V2;
        } else if (val == 2.0f){
            reg->BUVLO = BUVLO_t::BUVLO_2V0;
        }
        this->parent->write_chargectl1(reg.value());
    }
}
}