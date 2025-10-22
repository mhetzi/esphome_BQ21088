#pragma once

#include <cstdint>
#include <string>
#include <array>

enum CHG_STATUS_t : uint8_t {
    NOT_CHARGING = 0b00,
    CONSTANT_CURRENT   = 0b01,
    CONSTANT_VOLTAGE = 0b10,
    CHARGE_DONE = 0b11
};

enum TS_STATUS_t : uint8_t {
    TS_NOT_CONNECTED = 0b00,
    TS_NORMAL       = 0b01,
    TS_WARM         = 0b10,
    TS_COOL         = 0b11
};

enum ITERM_t : uint8_t {
    ITERM_DISABLE  = 0b00,
    ITERM_5_PERC = 0b01,
    ITERM_10_PERC = 0b10,
    ITERM_20_PERC = 0b11
};

enum VINDPM_t : uint8_t {
    VINDPM_VBAT_PLUS_200mV = 0b00,
    VINDPM_4_5V = 0b01,
    VINDPM_4_7V = 0b10,
    VINDPM_DISABLED = 0b11
};

enum THERM_REG_t : uint8_t {
    THERMREG_100C = 0b00,
    THERMREG_80C = 0b01,
    THERMREG_60C = 0b10,
    THERMREG_DISABLED = 0b11
};

enum IBAT_OCP_t : uint8_t {
    IBAT_OCP_500mA  = 0b00,
    IBAT_OCP_1000mA = 0b01,
    IBAT_OCP_1500mA = 0b10,
    IBAT_OCP_3000mA = 0b11
};

enum BUVLO_t : uint8_t {
    BUVLO_3V0 = 0b000,
    BUVLO_3V0b = 0b001, // laut Datenblatt auch 3.0V
    BUVLO_3V0c = 0b010, // laut Datenblatt auch 3.0V
    BUVLO_2V8 = 0b011,
    BUVLO_2V6 = 0b100,
    BUVLO_2V4 = 0b101,
    BUVLO_2V2 = 0b110,
    BUVLO_2V0 = 0b111
};

enum ILIM_t : uint8_t {
    ILIM_50mA   = 0b000,
    ILIM_100mA  = 0b001,
    ILIM_200mA  = 0b010,
    ILIM_300mA  = 0b011,
    ILIM_400mA  = 0b100,
    ILIM_500mA  = 0b101,
    ILIM_665mA  = 0b110,
    ILIM_1050mA = 0b111
};
enum SYS_REG_CTRL_t : uint8_t {
    SYS_REG_BAT_TRACKING = 0b000,
    SYS_REG_4V4          = 0b001,
    SYS_REG_4V5          = 0b010,
    SYS_REG_4V6          = 0b011,
    SYS_REG_4V7          = 0b100,
    SYS_REG_4V8          = 0b101,
    SYS_REG_4V9          = 0b110,
    SYS_REG_PASS_THROUGH = 0b111
};

enum SYS_MODE_t : uint8_t {
    SYS_MODE_VIN_OR_VBAT      = 0b00,
    SYS_MODE_VBAT_ONLY        = 0b01,
    SYS_MODE_SYS_FLOAT        = 0b10,
    SYS_MODE_SYS_FLOAT_PD     = 0b11
};

// STAT0 Register (0x0)
struct STAT0 {
    bool VIN_PGOOD_STAT : 1;
    bool THERMREG_ACTIVE_STAT : 1;
    bool VINDPM_ACTIVE_STAT : 1;
    bool VDPPM_ACTIVE_STAT : 1;
    bool ILIM_ACTIVE_STAT : 1;
    CHG_STATUS_t CHG_STAT : 2;
    bool TS_OPEN_STAT : 1;

    STAT0(uint8_t reg) {
        VIN_PGOOD_STAT        = reg & 0x01;
        THERMREG_ACTIVE_STAT  = (reg >> 1) & 0x01;
        VINDPM_ACTIVE_STAT    = (reg >> 2) & 0x01;
        VDPPM_ACTIVE_STAT     = (reg >> 3) & 0x01;
        ILIM_ACTIVE_STAT      = (reg >> 4) & 0x01;
        CHG_STAT              = static_cast<CHG_STATUS_t>((reg >> 5) & 0x03);
        TS_OPEN_STAT          = (reg >> 7) & 0x01;
    }

    const char* get_chg_status_string() {
        switch (this->CHG_STAT) {
            case NOT_CHARGING: return "Not Charging";
            case CONSTANT_CURRENT:    return "Constant Current";
            case CONSTANT_VOLTAGE:  return "Constant Voltage";
            case CHARGE_DONE:  return "Charge Done";
            default:           return "Unknown";
        }
    }
};

// STAT1 Register (0x1)
struct STAT1 {
    uint8_t WAKE2_FLAG : 1;
    uint8_t WAKE1_FLAG : 1;
    uint8_t SAFETY_TMR_FAULT_FLAG : 1;
    TS_STATUS_t TS_STAT : 2;
    uint8_t RESERVED : 1;
    uint8_t BUVLO_STAT : 1;
    uint8_t VIN_OVP_STAT : 1;

    STAT1(uint8_t reg) {
        WAKE2_FLAG              = reg & 0x01;
        WAKE1_FLAG              = (reg >> 1) & 0x01;
        SAFETY_TMR_FAULT_FLAG   = (reg >> 2) & 0x01;
        TS_STAT                 = static_cast<TS_STATUS_t>((reg >> 3) & 0x03);
        RESERVED                = (reg >> 5) & 0x01;
        BUVLO_STAT              = (reg >> 6) & 0x01;
        VIN_OVP_STAT            = (reg >> 7) & 0x01;
    }
};

// FLAG0 Register (0x2)
struct FLAG0 {
    bool BAT_OCP_FAULT : 1;
    bool BUVLO_FAULT_FLAG : 1;
    bool VIN_OVP_FAULT_FLAG : 1;
    bool THERMREG_ACTIVE_FLAG : 1;
    bool VINDPM_ACTIVE_FLAG : 1;
    bool VDPPM_ACTIVE_FLAG : 1;
    bool ILIM_ACTIVE_FLAG : 1;
    bool TS_FAULT : 1;

    FLAG0(uint8_t reg) {
        BAT_OCP_FAULT           = reg & 0x01;
        BUVLO_FAULT_FLAG        = (reg >> 1) & 0x01;
        VIN_OVP_FAULT_FLAG      = (reg >> 2) & 0x01;
        THERMREG_ACTIVE_FLAG    = (reg >> 3) & 0x01;
        VINDPM_ACTIVE_FLAG      = (reg >> 4) & 0x01;
        VDPPM_ACTIVE_FLAG       = (reg >> 5) & 0x01;
        ILIM_ACTIVE_FLAG        = (reg >> 6) & 0x01;
        TS_FAULT                = (reg >> 7) & 0x01;
    }
};

// VBAT_CTRL Register (0x3)
struct VBAT_CTRL {
    uint8_t VBATREG : 7;
    uint8_t PG_MODE : 1;

    VBAT_CTRL(uint8_t reg) {
        VBATREG = reg & 0x7F;
        PG_MODE = (reg >> 7) & 0x01;
    }

    float get_vbat_reg_voltage() const {
        return 3.5f + (VBATREG * 0.01f);
    }

    void set_vbat_reg_from_voltage(float voltage) {
        if (voltage < 3.5f) voltage = 3.5f;
        if (voltage > 4.92f) voltage = 4.65f;
        VBATREG = static_cast<uint8_t>((voltage - 3.5f) / 0.01f);
    }

    uint8_t to_uint8() const {
        return (PG_MODE << 7) | (VBATREG & 0x7F);
    }
};

// ICHG_CTRL Register (0x4)
struct ICHG_CTRL {
    uint8_t ICHG : 7;
    bool CHG_DIS : 1;

    ICHG_CTRL(uint8_t reg) {
        ICHG    = reg & 0x7F;
        CHG_DIS = (reg >> 7) & 0x01;
    }

    uint16_t get_charge_current_mA() const {
        if (ICHG <= 6) {
            // 0...6: 5mA + ICHG*5mA (also 5, 10, 15, ..., 35mA)
            return 5 + ICHG * 5;
        } else {
            // 7...63: 40mA + (ICHG-6)*10mA
            return 40 + (ICHG - 6) * 10;
        }
    }

    void set_charge_current_mA(uint16_t current_mA) {
        if (current_mA <= 35) {
            // 5...35mA: 5mA + ICHG*5mA
            if (current_mA < 5) current_mA = 5;
            ICHG = (current_mA - 5) / 5;
        } else {
            // 40...1000mA: 40mA + (ICHG-6)*10mA
            if (current_mA > 1000) current_mA = 1000;
            ICHG = 6 + (current_mA - 40) / 10;
        }
    }

    uint8_t to_uint8() const {
        return (CHG_DIS << 7) | (ICHG & 0x7F);
    }

};

// CHARGECTRL0 Register (0x5)
struct CHARGECTRL0 {
    THERM_REG_t THERM_REG : 2;
    VINDPM_t VINDPM : 2;
    ITERM_t ITERM : 2;
    uint8_t IPRECHG : 1;
    uint8_t EN_FC_MODE : 1;

    CHARGECTRL0(uint8_t reg) {
        THERM_REG   = static_cast<THERM_REG_t>(reg & 0x03);
        VINDPM      = static_cast<VINDPM_t>((reg >> 2) & 0x03);
        ITERM       = static_cast<ITERM_t>((reg >> 4) & 0x03);
        IPRECHG     = (reg >> 6) & 0x01;
        EN_FC_MODE  = (reg >> 7) & 0x01;
    }

    uint8_t to_uint8() const {
        return (EN_FC_MODE << 7)
             | (IPRECHG << 6)
             | (static_cast<uint8_t>(ITERM) << 4)
             | (static_cast<uint8_t>(VINDPM) << 2)
             | static_cast<uint8_t>(THERM_REG);
    }
};

// CHARGECTRL1 Register (0x6)
struct CHARGECTRL1 {
    uint8_t VINDPM_INT_MASK : 1;
    uint8_t ILIM_INT_MASK : 1;
    uint8_t CHG_STATUS_INT_MASK : 1;
    BUVLO_t BUVLO : 3;
    IBAT_OCP_t IBAT_OCP : 2;

    explicit CHARGECTRL1(uint8_t reg) {
        VINDPM_INT_MASK     = reg & 0x01;
        ILIM_INT_MASK       = (reg >> 1) & 0x01;
        CHG_STATUS_INT_MASK = (reg >> 2) & 0x01;
        BUVLO               = static_cast<BUVLO_t>((reg >> 3) & 0x07);
        IBAT_OCP            = static_cast<IBAT_OCP_t>((reg >> 6) & 0x03);
    }

    uint8_t to_uint8() const {
        return (static_cast<uint8_t>(IBAT_OCP) << 6)
             | (static_cast<uint8_t>(BUVLO) << 3)
             | (CHG_STATUS_INT_MASK << 2)
             | (ILIM_INT_MASK << 1)
             | VINDPM_INT_MASK;
    }

    float buvlo_as_number() const {
        switch (BUVLO) {
            case BUVLO_t::BUVLO_2V0:
                return 2.0f;
            case BUVLO_t::BUVLO_2V2:
                return 2.2f;
            case BUVLO_t::BUVLO_2V4:
                return 2.4f;
            case BUVLO_t::BUVLO_2V6:
                return 2.6f;
            case BUVLO_t::BUVLO_2V8:
                return 2.8f;
            case BUVLO_t::BUVLO_3V0:
            case BUVLO_t::BUVLO_3V0b:
            case BUVLO_t::BUVLO_3V0c:
                return 3.0f;
            default:
                return NAN;
        }
    };
};

static const std::array<std::string, 4> safety_timer_strings = {"3h", "6h", "12h", "disabled"};
// IC_CTRL Register (0x7)
struct IC_CTRL {
    uint8_t WATCHDOG_SEL : 2;
    uint8_t SAFETY_TIMER : 2;
    bool TMR_EN     : 1;
    bool VRCH       : 1;
    bool VLOWV_SEL  : 1;
    bool TS_EN      : 1;

    IC_CTRL(uint8_t reg) {
        WATCHDOG_SEL    = reg & 0x03;
        SAFETY_TIMER    = (reg >> 2) & 0x03;
        TMR_EN          = (reg >> 4) & 0x01;
        VRCH            = (reg >> 5) & 0x01;
        VLOWV_SEL       = (reg >> 6) & 0x01;
        TS_EN           = (reg >> 7) & 0x01;
    }

    uint8_t to_uint8() const {
        return (TS_EN << 7)
             | (VLOWV_SEL << 6)
             | (VRCH << 5)
             | (TMR_EN << 4)
             | (SAFETY_TIMER << 2)
             | WATCHDOG_SEL;
    }

    const std::string get_safety_timer_string(){
        return safety_timer_strings[SAFETY_TIMER];
    }

    void set_safety_timer_from_string(const std::string &str) {
        if (str.compare(safety_timer_strings[0]) == 0){
            SAFETY_TIMER = 0;
        } else if (str.compare(safety_timer_strings[1]) == 0){
            SAFETY_TIMER = 1;
        } else if (str.compare(safety_timer_strings[2]) == 0){
            SAFETY_TIMER = 2;
        } else if (str.compare(safety_timer_strings[3]) == 0){
            SAFETY_TIMER = 3;
        }
    }
};

// TMR_ILIM Register (0x8)
struct TMR_ILIM {
    ILIM_t ILIM : 3;
    uint8_t AUTOWAKE : 2;
    uint8_t MR_RESET_VIN : 1;
    uint8_t MR_LPRESS : 2;

    explicit TMR_ILIM(uint8_t reg) {
        ILIM           = static_cast<ILIM_t>(reg & 0x07);
        AUTOWAKE       = (reg >> 3) & 0x03;
        MR_RESET_VIN   = (reg >> 5) & 0x01;
        MR_LPRESS      = (reg >> 6) & 0x03;
    }

    uint8_t to_uint8() const {
        return (MR_LPRESS << 6)
             | (MR_RESET_VIN << 5)
             | (AUTOWAKE << 3)
             | static_cast<uint8_t>(ILIM);
    }
};

// SHIP_RST Register (0x9)
struct SHIP_RST {
    uint8_t EN_PUSH : 1;
    uint8_t WAKE2_TMR : 1;
    uint8_t WAKE1_TMR : 1;
    uint8_t PB_LPRESS_ACTION : 2;
    uint8_t EN_RST_SHIP : 2;
    uint8_t REG_RST : 1;

    SHIP_RST(uint8_t reg) {
        EN_PUSH             = reg & 0x01;
        WAKE2_TMR           = (reg >> 1) & 0x01;
        WAKE1_TMR           = (reg >> 2) & 0x01;
        PB_LPRESS_ACTION    = (reg >> 3) & 0x03;
        EN_RST_SHIP         = (reg >> 5) & 0x03;
        REG_RST             = (reg >> 7) & 0x01;
    }

    uint8_t to_uint8() const {
        return (REG_RST << 7)
             | (EN_RST_SHIP << 5)
             | (PB_LPRESS_ACTION << 3)
             | (WAKE1_TMR << 2)
             | (WAKE2_TMR << 1)
             | EN_PUSH;
    }
};

// SYS_REG Register (0xA)
struct SYS_REG {
    uint8_t VDPPM_DIS : 1;
    uint8_t WATCHDOG_15S_ENABLE : 1;
    SYS_MODE_t SYS_MODE : 2;
    uint8_t PG_GPO : 1;
    SYS_REG_CTRL_t SYS_REG_CTRL : 3;

    explicit SYS_REG(uint8_t reg) {
        VDPPM_DIS           = reg & 0x01;
        WATCHDOG_15S_ENABLE = (reg >> 1) & 0x01;
        SYS_MODE            = static_cast<SYS_MODE_t>((reg >> 2) & 0x03);
        PG_GPO              = (reg >> 4) & 0x01;
        SYS_REG_CTRL        = static_cast<SYS_REG_CTRL_t>((reg >> 5) & 0x07);
    }

    uint8_t to_uint8() const {
        return (static_cast<uint8_t>(SYS_REG_CTRL) << 5)
             | (PG_GPO << 4)
             | (static_cast<uint8_t>(SYS_MODE) << 2)
             | (WATCHDOG_15S_ENABLE << 1)
             | VDPPM_DIS;
    }
    const char* get_sys_reg_string() {
        switch (this->SYS_REG_CTRL) {
            case SYS_REG_CTRL_t::SYS_REG_BAT_TRACKING: return "Battery Tracking";
            case SYS_REG_CTRL_t::SYS_REG_4V4:          return "4.4V";
            case SYS_REG_CTRL_t::SYS_REG_4V5:          return "4.5V";
            case SYS_REG_CTRL_t::SYS_REG_4V6:          return "4.6V";
            case SYS_REG_CTRL_t::SYS_REG_4V7:          return "4.7V";
            case SYS_REG_CTRL_t::SYS_REG_4V8:          return "4.8V";
            case SYS_REG_CTRL_t::SYS_REG_4V9:          return "4.9V";
            case SYS_REG_CTRL_t::SYS_REG_PASS_THROUGH: return "Pass Through";
            default:                                   return "Unknown";
        }
    }
    const char* get_sys_mode_string() {
        switch (this->SYS_MODE) {
            case SYS_MODE_t::SYS_MODE_VIN_OR_VBAT:  return "VIN or VBAT";
            case SYS_MODE_t::SYS_MODE_VBAT_ONLY:    return "VBAT Only";
            case SYS_MODE_t::SYS_MODE_SYS_FLOAT:    return "System Float";
            case SYS_MODE_t::SYS_MODE_SYS_FLOAT_PD: return "System Float with Power Down";
            default:                                return "Unknown";
        }
    }
};

// TS_CONTROL Register (0xB)
struct TS_CONTROL {
    uint8_t TS_VRCG : 1;
    uint8_t TS_ICHG : 1;
    uint8_t TS_COOL : 1;
    uint8_t TS_WARM : 1;
    uint8_t TS_COLD : 2;
    uint8_t TS_HOT : 2;

    TS_CONTROL(uint8_t reg) {
        TS_VRCG    = reg & 0x01;
        TS_ICHG    = (reg >> 1) & 0x01;
        TS_COOL    = (reg >> 2) & 0x01;
        TS_WARM    = (reg >> 3) & 0x01;
        TS_COLD    = (reg >> 4) & 0x03;
        TS_HOT     = (reg >> 6) & 0x03;
    }

    uint8_t to_uint8() const {
        return (TS_HOT << 6)
             | (TS_COLD << 4)
             | (TS_WARM << 3)
             | (TS_COOL << 2)
             | (TS_ICHG << 1)
             | TS_VRCG;
    }
};

// MASK_ID Register (0xC)
struct MASK_ID {
    uint8_t Device_ID : 4;
    uint8_t PG_INT_MASK : 1;
    uint8_t BAT_INT_MASK : 1;
    uint8_t TREG_INT_MASK : 1;
    uint8_t TS_INT_MASK : 1;

    MASK_ID(uint8_t reg) {
        Device_ID      = reg & 0x0F;
        PG_INT_MASK    = (reg >> 4) & 0x01;
        BAT_INT_MASK   = (reg >> 5) & 0x01;
        TREG_INT_MASK  = (reg >> 6) & 0x01;
        TS_INT_MASK    = (reg >> 7) & 0x01;
    }

    uint8_t to_uint8() const {
        return (TS_INT_MASK << 7)
             | (TREG_INT_MASK << 6)
             | (BAT_INT_MASK << 5)
             | (PG_INT_MASK << 4)
             | (Device_ID & 0x0F);
    }
};
