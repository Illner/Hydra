#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hpp"
#include "Hydra/renHCRecognition/aspvall/AspvallRenHCRecognition.hpp"
#include "Hydra/renHCRecognition/aspvall/AspvallRenHCRecognitionStructure.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/renHCRecognition/exceptions/RenHCRecognitionException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hxx"

namespace Hydra::RenHCRecognition::Aspvall::Creation {

    /**
     * If currentComponentVariableSet is empty, the (whole) initial formula is considered. Otherwise, the particular current component formula is considered.
     * Assert: NO unit clause
     * Assert: statistics ARE FORBIDDEN for the current component formula (that is, currentComponentVariableSet is NOT empty)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @param formulaRepresentationAbstractPtr a pointer to the formula representation
     * @param ignorePureLiteralType (debug) a type of ignored pure literals
     * @param currentComponentVariableSet (optional) a set of variables appearing in the current component
     * @return renH-C recognition
     * @throw AspvallFormulaHasTooManySomethingException if the Aspvall formula has too many variables, literals, or clauses
     * @throw SomethingCannotBeSavedAsStdSizeTException if the Aspvall variables/literals/clauses/formula size cannot be saved as std::size_t
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr = nullptr,
                                  const Other::HashMap::SetType<VarT>& currentComponentVariableSet = {});

    /**
     * Process one clause
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    inline void processClauseCreateAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                                           AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>& aspvallRenHCRecognitionStruct,
                                                           ClauseIdT clauseId, std::vector<ClauseIdAspT>& literalNumberOfOccurrences,
                                                           std::vector<Formula::Literal<VarAspT, LiteralAspT>>& formula,
                                                           ClauseIdAspT& currentAspvallClauseId, VarAspT& newAuxiliaryVariableIndex);

    /**
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam VarAspT type used for an Aspvall variable
     * @tparam LiteralAspT type used for an Aspvall literal
     * @tparam ClauseIdAspT type used for an Aspvall clause identifier
     * @param formulaRepresentationAbstractPtr a pointer to the formula representation
     * @param aspvallRenHCRecognitionStruct an Aspvall renH-C recognition structure
     * @param ignorePureLiteralType (debug) a type of ignored pure literals
     * @param currentComponentClauseReusableVector (optional) a reusable vector of current component clauses
     * @return renH-C recognition
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    inline std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>&& aspvallRenHCRecognitionStruct,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr);

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    inline std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>&& aspvallRenHCRecognitionStruct,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  const typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType& currentComponentClauseReusableVector);
}   // namespace Hydra::RenHCRecognition::Aspvall::Creation

#include "./AspvallRenHCRecognitionCreation.ipp"
