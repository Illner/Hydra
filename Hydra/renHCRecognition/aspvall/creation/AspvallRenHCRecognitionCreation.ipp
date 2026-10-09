#pragma once

#include "./AspvallRenHCRecognitionCreation.hpp"

namespace Hydra::RenHCRecognition::Aspvall::Creation {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr,
                                  const Other::HashMap::SetType<VarT>& currentComponentVariableSet) {
        using LargeNumberType = Other::LargeNumberType;
        using ClauseSizeType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using ClauseIdReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

        bool initialFormula = currentComponentVariableSet.empty();   // the initial formula vs the current component formula

        ClauseIdReusableVectorType currentComponentClauseReusableVector(initialFormula ? 0 : formulaRepresentationAbstractPtr->getNumberOfCurrentComponentClauses(currentComponentVariableSet));

        assert(initialFormula || renHCRecognitionStatisticsPtr == nullptr);   // statistics are forbidden for the current component formula

        FormulaSizeType formulaSize = 0;
        LargeNumberType numberOfClauses = 0;
        LargeNumberType numberOfLiterals = 0;
        LargeNumberType numberOfVariables = static_cast<LargeNumberType>(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula());

        // The initial formula
        if (initialFormula) {
            for (ClauseIdT clauseId = 0; clauseId < formulaRepresentationAbstractPtr->getNumberOfOriginalClauses(); ++clauseId) {
                // Satisfied clause
                if (formulaRepresentationAbstractPtr->isClauseSatisfied(clauseId))
                    continue;

                ClauseSizeType clauseSize = formulaRepresentationAbstractPtr->getCurrentClauseSize(clauseId);

                assert(clauseSize > 1);   // no unit clause

                LargeNumberType numberOfClausesTmp = (LargeNumberType)2 + (LargeNumberType)3 * static_cast<LargeNumberType>(clauseSize - 2);

                numberOfClauses += numberOfClausesTmp;
                formulaSize += (LargeNumberType)2 * numberOfClausesTmp;
                numberOfVariables += static_cast<LargeNumberType>(clauseSize - 1);
            }
        }
        // The current component formula
        else {
            formulaRepresentationAbstractPtr->getCurrentComponentClauses(currentComponentVariableSet, currentComponentClauseReusableVector, true);

            for (ClauseIdT clauseId : currentComponentClauseReusableVector) {
                assert(!formulaRepresentationAbstractPtr->isClauseSatisfied(clauseId));   // clause is not satisfied

                ClauseSizeType clauseSize = formulaRepresentationAbstractPtr->getCurrentClauseSize(clauseId);

                assert(clauseSize > 1);   // no unit clause

                LargeNumberType numberOfClausesTmp = (LargeNumberType)2 + (LargeNumberType)3 * static_cast<LargeNumberType>(clauseSize - 2);

                numberOfClauses += numberOfClausesTmp;
                formulaSize += (LargeNumberType)2 * numberOfClausesTmp;
                numberOfVariables += static_cast<LargeNumberType>(clauseSize - 1);
            }
        }

        numberOfLiterals = (LargeNumberType)2 * numberOfVariables;

        // The Aspvall variables cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfVariables))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("Aspvall variables", numberOfVariables);

        // The Aspvall literals cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfLiterals))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("Aspvall literals", numberOfLiterals);

        // The Aspvall clauses cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfClauses))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("Aspvall clauses", numberOfClauses);

        // The Aspvall formula size cannot be saved as std::size_t
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<FormulaSizeType>(formulaSize))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("Aspvall formula size", formulaSize);

        assert(formulaSize > 0);
        assert(numberOfClauses > 0);
        assert(numberOfLiterals > 0);
        assert(numberOfVariables > 0);

        // AspClauseIdT = char8_t
        if (Other::clauseIdCanBeSavedAsTypeT<char8_t>(numberOfClauses)) {
            using AspClauseIdT = char8_t;

            // AspVarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                using AspVarT = char8_t;

                // AspLiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                    using AspLiteralT = char8_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables));

                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspVarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                using AspVarT = char16_t;

                // AspLiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables));

                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspVarT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                using AspVarT = char32_t;

                // AspLiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // Too many literals
                else
                    throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("variables");
        }

        // AspClauseIdT = char16_t
        else if (Other::clauseIdCanBeSavedAsTypeT<char16_t>(numberOfClauses)) {
            using AspClauseIdT = char16_t;

            // AspVarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                using AspVarT = char8_t;

                // AspLiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                    using AspLiteralT = char8_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables));

                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspVarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                using AspVarT = char16_t;

                // AspLiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables));

                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspVarT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                using AspVarT = char32_t;

                // AspLiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // Too many literals
                else
                    throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("variables");
        }

        // AspClauseIdT = char32_t
        else if (Other::clauseIdCanBeSavedAsTypeT<char32_t>(numberOfClauses)) {
            using AspClauseIdT = char32_t;

            // AspVarT = char8_t
            if (Other::variablesCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                using AspVarT = char8_t;

                // AspLiteralT = char8_t
                if (Other::literalsCanBeSavedAsTypeT<char8_t>(numberOfVariables)) {
                    using AspLiteralT = char8_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char16_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables));

                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspVarT = char16_t
            else if (Other::variablesCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                using AspVarT = char16_t;

                // AspLiteralT = char16_t
                if (Other::literalsCanBeSavedAsTypeT<char16_t>(numberOfVariables)) {
                    using AspLiteralT = char16_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // AspLiteralT = char32_t
                else {
                    assert(Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables));

                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }
            }

            // AspLiteralT = char32_t
            else if (Other::variablesCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                using AspVarT = char32_t;

                // AspLiteralT = char32_t
                if (Other::literalsCanBeSavedAsTypeT<char32_t>(numberOfVariables)) {
                    using AspLiteralT = char32_t;

                    // The initial formula
                    if (initialFormula)
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            renHCRecognitionStatisticsPtr);
                    // The current component formula
                    else
                        return createAspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>(formulaRepresentationAbstractPtr,
                                                                                                                            { static_cast<AspVarT>(numberOfVariables),
                                                                                                                              static_cast<AspLiteralT>(numberOfLiterals),
                                                                                                                              static_cast<AspClauseIdT>(numberOfClauses),
                                                                                                                              formulaSize },
                                                                                                                            ignorePureLiteralType,
                                                                                                                            currentComponentClauseReusableVector);
                }

                // Too many literals
                else
                    throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("literals");
            }

            // Too many variables
            else
                throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("variables");
        }

        // Too many clauses
        else
            throw Exception::RenHCRecognition::AspvallFormulaHasTooManySomethingException("clauses");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename AspVarT, typename AspLiteralT, typename AspClauseIdT>
    void processClauseCreateAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                                    AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>& aspvallRenHCRecognitionStruct,
                                                    ClauseIdT clauseId, std::vector<AspClauseIdT>& literalNumberOfOccurrences,
                                                    std::vector<Formula::Literal<AspVarT, AspLiteralT>>& formula,
                                                    AspClauseIdT& currentAspvallClauseId, AspVarT& newAuxiliaryVariableIndex) {
        using ClauseSizeType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using LiteralAspType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::LiteralAspType;

        AspVarT previousY = 0;
        ClauseSizeType currentLiteralIndex = 0;
        ClauseSizeType maxLiteralIndex = (formulaRepresentationAbstractPtr->getCurrentClauseSize(clauseId) - 1);

        for (auto clauseIt = formulaRepresentationAbstractPtr->beginClause(clauseId);
             clauseIt != formulaRepresentationAbstractPtr->endClause(); ++clauseIt) {
            LiteralAspType lit(static_cast<AspVarT>(clauseIt->getVariable()), clauseIt->isPositive());

            // Last literal
            if (currentLiteralIndex++ == maxLiteralIndex) {
                assert(previousY > 0);

                LiteralAspType litY(previousY, false);

                ++literalNumberOfOccurrences[lit.getLiteralT()];
                ++literalNumberOfOccurrences[litY.getLiteralT()];

                // (lit or -y_p)
                formula.emplace_back(std::move(lit));
                formula.emplace_back(std::move(litY));

                // Aspvall clause -> original clause
                assert(aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] == 0);   // not initialized
                aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] = clauseId;

                ++currentAspvallClauseId;

                continue;
            }

            // Create y_new
            ++newAuxiliaryVariableIndex;
            AspVarT newY = newAuxiliaryVariableIndex;

            // First literal
            if (previousY == 0) {
                LiteralAspType litY(newY, true);

                ++literalNumberOfOccurrences[lit.getLiteralT()];
                ++literalNumberOfOccurrences[litY.getLiteralT()];

                // (lit or y_n)
                formula.emplace_back(std::move(lit));
                formula.emplace_back(std::move(litY));

                // Aspvall clause -> original clause
                assert(aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] == 0);   // not initialized
                aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] = clauseId;

                ++currentAspvallClauseId;

                previousY = newY;
                continue;
            }

            LiteralAspType posLitNewY(newY, true);
            LiteralAspType negLitPreviousY(previousY, false);

            literalNumberOfOccurrences[lit.getLiteralT()] += 2;
            literalNumberOfOccurrences[posLitNewY.getLiteralT()] += 2;
            literalNumberOfOccurrences[negLitPreviousY.getLiteralT()] += 2;

            // (lit v -y_p)
            formula.emplace_back(lit);
            formula.emplace_back(negLitPreviousY);

            // Aspvall clause -> original clause
            assert(aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] == 0);   // not initialized
            aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] = clauseId;

            ++currentAspvallClauseId;

            // (-y_p v y_n)
            formula.emplace_back(std::move(negLitPreviousY));
            formula.emplace_back(posLitNewY);

            // Aspvall clause -> original clause
            assert(aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] == 0);   // not initialized
            aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] = clauseId;

            ++currentAspvallClauseId;

            // (lit v y_n)
            formula.emplace_back(std::move(lit));
            formula.emplace_back(std::move(posLitNewY));

            // Aspvall clause -> original clause
            assert(aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] == 0);   // not initialized
            aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector[currentAspvallClauseId] = clauseId;

            ++currentAspvallClauseId;

            previousY = newY;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename AspVarT, typename AspLiteralT, typename AspClauseIdT>
    std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>&& aspvallRenHCRecognitionStruct,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr) {
        using AspvallRenHCRecognitionType = AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>;
        using FormulaAspType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::FormulaAspType;
        using ClauseIdVectorType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::ClauseIdVectorType;
        using ClauseIdVectorAspType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::ClauseIdVectorAspType;

        // Statistics
        if (renHCRecognitionStatisticsPtr)
            renHCRecognitionStatisticsPtr->creationTimer.startStopwatch();

        AspClauseIdT currentAspvallClauseId = 0;
        AspVarT newAuxiliaryVariableIndex = static_cast<AspVarT>(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula());

        FormulaAspType formula;
        formula.reserve(aspvallRenHCRecognitionStruct.formulaSize);
        ClauseIdVectorAspType literalNumberOfOccurrences(static_cast<typename ClauseIdVectorAspType::size_type>(AspLiteralT(2) + aspvallRenHCRecognitionStruct.numberOfLiterals), 0);
        aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector = ClauseIdVectorType(static_cast<typename ClauseIdVectorType::size_type>(aspvallRenHCRecognitionStruct.numberOfClauses), 0);
        aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector = ClauseIdVectorAspType(static_cast<typename ClauseIdVectorAspType::size_type>(ClauseIdT(1) + formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()), 0);

        for (ClauseIdT clauseId = 0; clauseId < formulaRepresentationAbstractPtr->getNumberOfOriginalClauses(); ++clauseId) {
            // Original clause -> first Aspvall clause
            assert(aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId] == 0);   // not initialized
            aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId] = currentAspvallClauseId;

            // Satisfied clause
            if (formulaRepresentationAbstractPtr->isClauseSatisfied(clauseId))
                continue;

            processClauseCreateAspvallRenHCRecognition(formulaRepresentationAbstractPtr, aspvallRenHCRecognitionStruct, clauseId, literalNumberOfOccurrences,
                                                       formula, currentAspvallClauseId, newAuxiliaryVariableIndex);
        }

        // Original clause -> first Aspvall clause
        assert(aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.back() == 0);
        aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.back() = currentAspvallClauseId;

        assert(currentAspvallClauseId == aspvallRenHCRecognitionStruct.numberOfClauses);
        assert(newAuxiliaryVariableIndex == aspvallRenHCRecognitionStruct.numberOfVariables);
        assert(aspvallRenHCRecognitionStruct.formulaSize == static_cast<FormulaSizeType>(formula.size()));
        assert((FormulaSizeType)2 * static_cast<FormulaSizeType>(currentAspvallClauseId) == aspvallRenHCRecognitionStruct.formulaSize);

        // Statistics
        if (renHCRecognitionStatisticsPtr)
            renHCRecognitionStatisticsPtr->creationTimer.stopStopwatch();

        return std::make_unique<AspvallRenHCRecognitionType>(std::move(formula), std::move(aspvallRenHCRecognitionStruct),
                                                             literalNumberOfOccurrences, formulaRepresentationAbstractPtr,
                                                             ignorePureLiteralType, true, renHCRecognitionStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename AspVarT, typename AspLiteralT, typename AspClauseIdT>
    std::unique_ptr<RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>>
    createAspvallRenHCRecognition(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>* formulaRepresentationAbstractPtr,
                                  AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>&& aspvallRenHCRecognitionStruct,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                  const typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType& currentComponentClauseReusableVector) {
        using AspvallRenHCRecognitionType = AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>;
        using FormulaAspType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::FormulaAspType;
        using ClauseIdVectorType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::ClauseIdVectorType;
        using ClauseIdVectorAspType = typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, AspVarT, AspLiteralT, AspClauseIdT>::ClauseIdVectorAspType;

        AspClauseIdT currentAspvallClauseId = 0;
        AspVarT newAuxiliaryVariableIndex = static_cast<AspVarT>(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula());

        FormulaAspType formula;
        formula.reserve(aspvallRenHCRecognitionStruct.formulaSize);
        ClauseIdVectorAspType literalNumberOfOccurrences(static_cast<typename ClauseIdVectorAspType::size_type>(AspLiteralT(2) + aspvallRenHCRecognitionStruct.numberOfLiterals), 0);
        aspvallRenHCRecognitionStruct.mappingFromAspvallClauseIdToOriginalClauseIdVector = ClauseIdVectorType(static_cast<typename ClauseIdVectorType::size_type>(aspvallRenHCRecognitionStruct.numberOfClauses), 0);
        aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector = ClauseIdVectorAspType(static_cast<typename ClauseIdVectorAspType::size_type>(ClauseIdT(1) + formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()), 0);

        assert(!currentComponentClauseReusableVector.empty());   // at least one clause

        auto currentComponentClauseIt = currentComponentClauseReusableVector.cbegin();

        for (ClauseIdT clauseId = 0; clauseId < formulaRepresentationAbstractPtr->getNumberOfOriginalClauses(); ++clauseId) {
            // Original clause -> first Aspvall clause
            assert(aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId] == 0);   // not initialized
            aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId] = currentAspvallClauseId;

            if (currentComponentClauseIt == currentComponentClauseReusableVector.cend())
                continue;

            // Not in the current component
            if (clauseId < *currentComponentClauseIt)
                continue;

            assert(clauseId == *currentComponentClauseIt);
            assert(!formulaRepresentationAbstractPtr->isClauseSatisfied(clauseId));   // clause is not satisfied

            ++currentComponentClauseIt;

            processClauseCreateAspvallRenHCRecognition(formulaRepresentationAbstractPtr, aspvallRenHCRecognitionStruct, clauseId, literalNumberOfOccurrences,
                                                       formula, currentAspvallClauseId, newAuxiliaryVariableIndex);
        }

        // Original clause -> first Aspvall clause
        assert(aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.back() == 0);
        aspvallRenHCRecognitionStruct.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.back() = currentAspvallClauseId;

        assert(currentAspvallClauseId == aspvallRenHCRecognitionStruct.numberOfClauses);
        assert(newAuxiliaryVariableIndex == aspvallRenHCRecognitionStruct.numberOfVariables);
        assert(aspvallRenHCRecognitionStruct.formulaSize == static_cast<FormulaSizeType>(formula.size()));
        assert((FormulaSizeType)2 * static_cast<FormulaSizeType>(currentAspvallClauseId) == aspvallRenHCRecognitionStruct.formulaSize);

        return std::make_unique<AspvallRenHCRecognitionType>(std::move(formula), std::move(aspvallRenHCRecognitionStruct),
                                                             literalNumberOfOccurrences, formulaRepresentationAbstractPtr,
                                                             ignorePureLiteralType, false, nullptr);
    }
}   // namespace Hydra::RenHCRecognition::Aspvall::Creation
