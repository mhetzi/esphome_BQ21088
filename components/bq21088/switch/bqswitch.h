#pragma once

#include "esphome/components/switch/switch.h"
#include "bq21088/bg20188.h"

namespace esphome {
namespace bq21088 {

enum SwitchType : uint8_t {
    CHARGE_DISABLE = 0,
    UNKNOWN
}

class BqSwitch: public esphome::switch_::Switch {
    protected:
        friend class BQ21088;
        void write_state(bool state) override;
        void set_parent(BQ21088* parent);
        void set_type(NumberType nt);

    private:
        static const char* TAG;
        BQ21088 *parent = nullptr;
        SwitchType nt = SwitchType::UNKNOWN;
}

}
}