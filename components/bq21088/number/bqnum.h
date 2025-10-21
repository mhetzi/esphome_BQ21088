#pragma once

#include "esphome/components/number/number.h"
#include "../bq20188.h"

namespace esphome {
namespace bq21088 {

enum NumberType {
    VBAT = 0,
    ICGH,
    BUVLO,
    NT_UNKNOWN
};

class BqNumber: public esphome::number::Number {
    public:
        void set_parent(BQ21088* parent);
        void set_type(NumberType nt);
    protected:
        friend class BQ21088;
        void control(float value) override;

    private:
        BQ21088 *parent = nullptr;
        NumberType nt = NumberType::NT_UNKNOWN;

        void setBuvlo(float val);
};

}
}