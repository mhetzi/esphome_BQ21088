#include "bqswitch.h"


namespace esphome {
namespace bq21088 {
    static const char* BqSwitch::TAG = "BQ21088.Number"; 
    void BqSwitch::write_state(bool state){
        switch (this->nt) {
            case SwitchType::CHARGE_DISABLE: {
                auto charge = this->parent->read_ichg_ctrl();
                charge.CHG_DIS = state;
                this->parent->write_ichg_ctrl(charge);
                break;
            }
            default:
                break;
        }
        
    }
    void BqSwitch::set_parent(BQ21088 *parent) {
        this->parent = parent;
    }

    void BqSwitch::set_type(NumberType nt) {
        this->nt = nt;
    }
}
}