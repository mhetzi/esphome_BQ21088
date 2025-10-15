#pragma once

#include "esphome/components/number/number.h"
#include "../bq20188.h"

namespace esphome {
namespace bq21088 {

enum NumberType {
    VBAT = 0,
    ICGH,
    NT_UNKNOWN
};

class BqNumber: public esphome::number::Number {
    protected:
        friend class BQ21088;
        void control(float value) override;
        void set_parent(BQ21088* parent);
        void set_type(NumberType nt);

    private:
        BQ21088 *parent = nullptr;
        NumberType nt = NumberType::NT_UNKNOWN;
};

}
}