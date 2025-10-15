#pragma once

#include "esphome/components/switch/switch.h"
#include "../bq20188.h"

namespace esphome {
namespace bq21088 {

enum SwitchType {
    CHARGE_DISABLE = 0,
    ST_UNKNOWN
};

class BqSwitch: public esphome::switch_::Switch {
    protected:
        friend class BQ21088;
        void write_state(bool state) override;
        void set_parent(BQ21088* parent);
        void set_type(SwitchType st);

    private:
        BQ21088 *parent = nullptr;
        SwitchType st = SwitchType::ST_UNKNOWN;
};

}
}