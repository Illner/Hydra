#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Circuit {

    enum class CircuitTypeEnum {
        // Standard
        NNF,
        s_NNF,
        DNNF,
        s_DNNF,
        d_DNNF,
        sd_DNNF,

        // BDMC
        Krom_C_d_BDMC,
        Krom_C_sd_BDMC,
        renH_C_d_BDMC,
        renH_C_sd_BDMC,
        renH_C_AND_Krom_C_d_BDMC,
        renH_C_AND_Krom_C_sd_BDMC,

        // Weak and variants
        wDNNF,
        pwDNNF,
        nwDNNF,

        // Bella
        Bella,       // wDNNF + renH-C leaves
        posBella,    // pwDNNF + anti-Horn-C leaves
        negBella,    // nwDNNF + Horn-C leaves
        Krom_Bella   // wDNNF + Krom-C leaves
    };

    using CircuitTypeEnumSetType = Other::HashMap::SetType<CircuitTypeEnum>;

    const inline CircuitTypeEnumSetType smoothCircuitTypeSet { // Standard
                                                               CircuitTypeEnum::s_NNF,
                                                               CircuitTypeEnum::s_DNNF,
                                                               CircuitTypeEnum::sd_DNNF,
                                                               // BDMC
                                                               CircuitTypeEnum::Krom_C_sd_BDMC,
                                                               CircuitTypeEnum::renH_C_sd_BDMC,
                                                               CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC
    };

    const inline CircuitTypeEnumSetType standardCircuitTypeSet { CircuitTypeEnum::NNF,
                                                                 CircuitTypeEnum::s_NNF,
                                                                 CircuitTypeEnum::DNNF,
                                                                 CircuitTypeEnum::s_DNNF,
                                                                 CircuitTypeEnum::d_DNNF,
                                                                 CircuitTypeEnum::sd_DNNF };

    const inline CircuitTypeEnumSetType bdmcCircuitTypeSet { // Krom-C leaves
                                                             CircuitTypeEnum::Krom_C_d_BDMC,
                                                             CircuitTypeEnum::Krom_C_sd_BDMC,
                                                             // renH-C leaves
                                                             CircuitTypeEnum::renH_C_d_BDMC,
                                                             CircuitTypeEnum::renH_C_sd_BDMC,
                                                             // renH-C + Krom-C leaves
                                                             CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                             CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC
    };

    const inline CircuitTypeEnumSetType weakAndVariantsCircuitTypeSet { CircuitTypeEnum::wDNNF,
                                                                        CircuitTypeEnum::pwDNNF,
                                                                        CircuitTypeEnum::nwDNNF };

    const inline CircuitTypeEnumSetType bellaCircuitTypeSet { CircuitTypeEnum::Bella,
                                                              CircuitTypeEnum::posBella,
                                                              CircuitTypeEnum::negBella,
                                                              CircuitTypeEnum::Krom_Bella };

    const inline CircuitTypeEnumSetType sharingVariablesCircuitTypeSet { // Weak and variants
                                                                         CircuitTypeEnum::wDNNF,
                                                                         CircuitTypeEnum::pwDNNF,
                                                                         CircuitTypeEnum::nwDNNF,
                                                                         // Bella
                                                                         CircuitTypeEnum::Bella,
                                                                         CircuitTypeEnum::posBella,
                                                                         CircuitTypeEnum::negBella,
                                                                         CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType supportCompilationCircuitTypeSet { // Standard
                                                                           CircuitTypeEnum::d_DNNF,
                                                                           CircuitTypeEnum::sd_DNNF,
                                                                           // BDMC
                                                                           CircuitTypeEnum::Krom_C_d_BDMC,
                                                                           CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                           CircuitTypeEnum::renH_C_d_BDMC,
                                                                           CircuitTypeEnum::renH_C_sd_BDMC,
                                                                           CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                           CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                           // Weak and variants
                                                                           CircuitTypeEnum::wDNNF,
                                                                           CircuitTypeEnum::pwDNNF,
                                                                           CircuitTypeEnum::nwDNNF,
                                                                           // Bella
                                                                           CircuitTypeEnum::Bella,
                                                                           CircuitTypeEnum::posBella,
                                                                           CircuitTypeEnum::negBella,
                                                                           CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType supportConsistencyCheckCircuitTypeSet { // Standard
                                                                                CircuitTypeEnum::DNNF,
                                                                                CircuitTypeEnum::s_DNNF,
                                                                                CircuitTypeEnum::d_DNNF,
                                                                                CircuitTypeEnum::sd_DNNF,
                                                                                // BDMC
                                                                                CircuitTypeEnum::Krom_C_d_BDMC,
                                                                                CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                                CircuitTypeEnum::renH_C_d_BDMC,
                                                                                CircuitTypeEnum::renH_C_sd_BDMC,
                                                                                CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                                CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                                // Weak and variants
                                                                                CircuitTypeEnum::wDNNF,
                                                                                CircuitTypeEnum::pwDNNF,
                                                                                CircuitTypeEnum::nwDNNF,
                                                                                // Bella
                                                                                CircuitTypeEnum::Bella,
                                                                                CircuitTypeEnum::posBella,
                                                                                CircuitTypeEnum::negBella,
                                                                                CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType supportModelCountingCircuitTypeSet { // Standard
                                                                             CircuitTypeEnum::d_DNNF,
                                                                             CircuitTypeEnum::sd_DNNF,
                                                                             // BDMC (model counting with polynomial delay)
                                                                             CircuitTypeEnum::Krom_C_d_BDMC,
                                                                             CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                             CircuitTypeEnum::renH_C_d_BDMC,
                                                                             CircuitTypeEnum::renH_C_sd_BDMC,
                                                                             CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                             CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC
    };

    //region Formula leaves
    const inline CircuitTypeEnumSetType formulaLeavesCircuitTypeSet { // BDMC
                                                                      CircuitTypeEnum::Krom_C_d_BDMC,
                                                                      CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                      CircuitTypeEnum::renH_C_d_BDMC,
                                                                      CircuitTypeEnum::renH_C_sd_BDMC,
                                                                      CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                      CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                      // Bella
                                                                      CircuitTypeEnum::Bella,
                                                                      CircuitTypeEnum::posBella,
                                                                      CircuitTypeEnum::negBella,
                                                                      CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType kromCLeavesCircuitTypeSet { // BDMC
                                                                    CircuitTypeEnum::Krom_C_d_BDMC,
                                                                    CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                    CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                    CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                    // Bella
                                                                    CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType hornCLeavesCircuitTypeSet { // Bella
                                                                    CircuitTypeEnum::negBella
    };

    const inline CircuitTypeEnumSetType antiHornCLeavesCircuitTypeSet { // Bella
                                                                        CircuitTypeEnum::posBella
    };

    const inline CircuitTypeEnumSetType renHCLeavesCircuitTypeSet { // BDMC
                                                                    CircuitTypeEnum::renH_C_d_BDMC,
                                                                    CircuitTypeEnum::renH_C_sd_BDMC,
                                                                    CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                    CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                    // Bella
                                                                    CircuitTypeEnum::Bella
    };
    //endregion

    //region Cara caching scheme - a variable to variable/literal mapping
    const inline CircuitTypeEnumSetType caraCachingSchemeVariableToLiteralMappingCircuitTypeSet { // Standard
                                                                                                  CircuitTypeEnum::d_DNNF,
                                                                                                  CircuitTypeEnum::sd_DNNF,
                                                                                                  // BDMC
                                                                                                  CircuitTypeEnum::Krom_C_d_BDMC,
                                                                                                  CircuitTypeEnum::Krom_C_sd_BDMC,
                                                                                                  CircuitTypeEnum::renH_C_d_BDMC,
                                                                                                  CircuitTypeEnum::renH_C_sd_BDMC,
                                                                                                  CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC,
                                                                                                  CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC,
                                                                                                  // Weak and variants
                                                                                                  CircuitTypeEnum::wDNNF,
                                                                                                  // Bella
                                                                                                  CircuitTypeEnum::Bella,
                                                                                                  CircuitTypeEnum::Krom_Bella
    };

    const inline CircuitTypeEnumSetType caraCachingSchemeVariableToVariableMappingCircuitTypeSet { // Weak and variants
                                                                                                   CircuitTypeEnum::pwDNNF,
                                                                                                   CircuitTypeEnum::nwDNNF,
                                                                                                   // Bella
                                                                                                   CircuitTypeEnum::posBella,
                                                                                                   CircuitTypeEnum::negBella
    };
    //endregion

    inline std::string circuitTypeEnumToString(CircuitTypeEnum circuitType, bool addPostfixCircuit = false) noexcept {
        switch (circuitType) {
            // Standard
            case CircuitTypeEnum::NNF:
                if (addPostfixCircuit)
                    return "NNF circuit";

                return "NNF";
            case CircuitTypeEnum::s_NNF:
                if (addPostfixCircuit)
                    return "s-NNF circuit";

                return "s-NNF";
            case CircuitTypeEnum::DNNF:
                if (addPostfixCircuit)
                    return "DNNF circuit";

                return "DNNF";
            case CircuitTypeEnum::s_DNNF:
                if (addPostfixCircuit)
                    return "s-DNNF circuit";

                return "s-DNNF";
            case CircuitTypeEnum::d_DNNF:
                if (addPostfixCircuit)
                    return "d-DNNF circuit";

                return "d-DNNF";
            case CircuitTypeEnum::sd_DNNF:
                if (addPostfixCircuit)
                    return "sd-DNNF circuit";

                return "sd-DNNF";
            // BDMC
            case CircuitTypeEnum::Krom_C_d_BDMC:
                if (addPostfixCircuit)
                    return "{Krom-C}-d-BDMC circuit";

                return "{Krom-C}-d-BDMC";
            case CircuitTypeEnum::Krom_C_sd_BDMC:
                if (addPostfixCircuit)
                    return "{Krom-C}-sd-BDMC circuit";

                return "{Krom-C}-sd-BDMC";
            case CircuitTypeEnum::renH_C_d_BDMC:
                if (addPostfixCircuit)
                    return "{renH-C}-d-BDMC circuit";

                return "{renH-C}-d-BDMC";
            case CircuitTypeEnum::renH_C_sd_BDMC:
                if (addPostfixCircuit)
                    return "{renH-C}-sd-BDMC circuit";

                return "{renH-C}-sd-BDMC";
            case CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC:
                if (addPostfixCircuit)
                    return "{renH-C, Krom-C}-d-BDMC circuit";

                return "{renH-C, Krom-C}-d-BDMC";
            case CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC:
                if (addPostfixCircuit)
                    return "{renH-C, Krom-C}-sd-BDMC circuit";

                return "{renH-C, Krom-C}-sd-BDMC";
            // Weak and variants
            case CircuitTypeEnum::wDNNF:
                if (addPostfixCircuit)
                    return "wDNNF circuit";

                return "wDNNF";
            case CircuitTypeEnum::pwDNNF:
                if (addPostfixCircuit)
                    return "pwDNNF circuit";

                return "pwDNNF";
            case CircuitTypeEnum::nwDNNF:
                if (addPostfixCircuit)
                    return "nwDNNF circuit";

                return "nwDNNF";
            // Bella
            case CircuitTypeEnum::Bella:
                if (addPostfixCircuit)
                    return "Bella circuit";

                return "Bella";
            case CircuitTypeEnum::posBella:
                if (addPostfixCircuit)
                    return "posBella circuit";

                return "posBella";
            case CircuitTypeEnum::negBella:
                if (addPostfixCircuit)
                    return "negBella circuit";

                return "negBella";
            case CircuitTypeEnum::Krom_Bella:
                if (addPostfixCircuit)
                    return "Krom-Bella circuit";

                return "Krom-Bella";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Circuit
