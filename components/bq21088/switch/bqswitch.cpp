#include "bqswitch.h"


namespace esphome {
namespace bq21088 {
    static const char* TAG = "BQ21088.Switch"; 
    void BqSwitch::write_state(bool state){
        switch (this->st) {
            case SwitchType::CHARGE_DISABLE: {
                auto charge = this->parent->read_ichg_ctrl();
                if (!charge)
                    return;
                charge->CHG_DIS = state;
                this->parent->write_ichg_ctrl(charge.value());
                break;
            }
            case SwitchType::REDUCE_PRECHARGE:{
                auto ic = this->parent->read_ic_ctrl();
                if (!ic) return;
                ic->VLOWV_SEL = state;
                this->parent->write_ic_ctrl(ic.value());
                break;
            }
            default:
                break;
        }
        
    }
    void BqSwitch::set_parent(BQ21088 *parent) {
        this->parent = parent;
    }

    void BqSwitch::set_type(SwitchType st) {
        this->st = st;
    }
}
}