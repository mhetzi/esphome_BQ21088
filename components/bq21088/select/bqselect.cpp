#include "bqselect.h"


namespace esphome {
namespace bq21088 {
    static const char* TAG = "BQ21088.Select";

    void BqSelect::control(const std::string &value) {
        switch (this->st) {
            case BQ_SelectType::SAFETY_TIMER:{
                auto ic = this->parent->read_ic_ctrl();
                if (!ic) return;
                ic->set_safety_timer_from_string(value);
                this->parent->write_ic_ctrl(ic.value());
                break;
            }
            
            default:
                break;
        }
    }
    
    void BqSelect::set_parent(BQ21088 *parent) {
        this->parent = parent;
    }

    void BqSelect::set_type(BQ_SelectType st) {
        this->st = st;
    }
}
}