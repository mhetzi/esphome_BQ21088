#pragma once

#include "esphome/components/select/select.h"
#include "../bq20188.h"

namespace esphome {
namespace bq21088 {

enum BQ_SelectType {
    SAFETY_TIMER = 0,
    SE_UNKNOWN
};

class BqSelect: public esphome::select::Select {
    protected:
        friend class BQ21088;
        void control(const std::string &value) override;
    public:
        void set_parent(BQ21088* parent);
        void set_type(BQ_SelectType st);

    private:
        BQ21088 *parent = nullptr;
        BQ_SelectType st = BQ_SelectType::SE_UNKNOWN;
};

}
}