#pragma once

#include "esphome/components/switch/switch.h"
#include "../bq20188.h"

namespace esphome {
namespace bq21088 {

enum BQ_SwitchType {
    CHARGE_DISABLE = 0,
    REDUCE_PRECHARGE,
    ST_UNKNOWN
};

class BqSwitch: public esphome::switch_::Switch {
    protected:
        friend class BQ21088;
        void write_state(bool state) override;
    public:
        void set_parent(BQ21088* parent);
        void set_type(BQ_SwitchType st);

    private:
        BQ21088 *parent = nullptr;
        BQ_SwitchType st = BQ_SwitchType::ST_UNKNOWN;
};

}
}