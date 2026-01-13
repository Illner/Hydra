#pragma once

#include <string>

namespace HydraTest::FormulaInstance {

    enum class FormulaInstanceEnum {
        _4step,
        _5step,
        ais6,
        ais12,
        anomaly,
        binsearch_16_pp,
        binsearch_32_pp,
        bmc_ibm_1,
        bmc_ibm_2,
        bomb_b10_t10_p_t5,
        C171_FR,
        C220_FV,
        c499_isc,
        cnt06_shuffled,
        D1119_M20,
        fs_01_net,
        mixdup,
        or_60_10_7_UC_10,
        s400_bench,
        sat_grid_pbl_0030,
        sum_32,
        uf250_04,
        wff_3_75_315,

        configuration_1,
        configuration_2,
        configuration_3,
        configuration_4,
        configuration_5
    };

    inline std::string formulaInstanceEnumToString(FormulaInstanceEnum formulaInstance) noexcept {
        switch (formulaInstance) {
            case FormulaInstanceEnum::_4step:
                return "4step";
            case FormulaInstanceEnum::_5step:
                return "5step";
            case FormulaInstanceEnum::ais6:
                return "ais6";
            case FormulaInstanceEnum::ais12:
                return "ais12";
            case FormulaInstanceEnum::anomaly:
                return "anomaly";
            case FormulaInstanceEnum::binsearch_16_pp:
                return "binsearch.16.pp";
            case FormulaInstanceEnum::binsearch_32_pp:
                return "binsearch.32.pp";
            case FormulaInstanceEnum::bmc_ibm_1:
                return "bmc-ibm-1";
            case FormulaInstanceEnum::bmc_ibm_2:
                return "bmc-ibm-2";
            case FormulaInstanceEnum::bomb_b10_t10_p_t5:
                return "bomb_b10_t10_p_t5";
            case FormulaInstanceEnum::C171_FR:
                return "C171_FR";
            case FormulaInstanceEnum::C220_FV:
                return "C220_FV";
            case FormulaInstanceEnum::c499_isc:
                return "c499.isc";
            case FormulaInstanceEnum::cnt06_shuffled:
                return "cnt06.shuffled";
            case FormulaInstanceEnum::D1119_M20:
                return "D1119_M20";
            case FormulaInstanceEnum::fs_01_net:
                return "fs-01.net";
            case FormulaInstanceEnum::mixdup:
                return "mixdup";
            case FormulaInstanceEnum::or_60_10_7_UC_10:
                return "or-60-10-7-UC-10";
            case FormulaInstanceEnum::s400_bench:
                return "s400.bench";
            case FormulaInstanceEnum::sat_grid_pbl_0030:
                return "sat-grid-pbl-0030";
            case FormulaInstanceEnum::sum_32:
                return "sum.32";
            case FormulaInstanceEnum::uf250_04:
                return "uf250-04";
            case FormulaInstanceEnum::wff_3_75_315:
                return "wff.3.75.315";
            case FormulaInstanceEnum::configuration_1:
                return "configuration 1";
            case FormulaInstanceEnum::configuration_2:
                return "configuration 2";
            case FormulaInstanceEnum::configuration_3:
                return "configuration 3";
            case FormulaInstanceEnum::configuration_4:
                return "configuration 4";
            case FormulaInstanceEnum::configuration_5:
                return "configuration 5";
            default:
                return "name not set";
        }
    }
}   // namespace HydraTest::FormulaInstance
