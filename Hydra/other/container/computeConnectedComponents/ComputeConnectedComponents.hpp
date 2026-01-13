#pragma once

#include <cassert>
#include <ostream>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"
#include "Hydra/other/container/vectorMap/VectorMap.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Container::ComputeConnectedComponents {

    /**
     * Compute connected components representation
     * Union find algorithm (union by rank and path compression)
     * Copy methods are disabled! Move methods (default) are allowed!
     * Exceptions:
     *      SomethingCannotBeSavedAsStdSizeTException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class ComputeConnectedComponents {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");

    private:
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;

    public:
        using ConnectedComponentStruct = Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    public:
        using ConnectedComponentType = std::vector<ConnectedComponentStruct>;

    private:
        struct SubsetStruct {
        public:
            VarT rank = 0;
            VarT parent;
        };

    private:
        using SubsetVectorType = std::vector<SubsetStruct>;
        using VariableVectorMapType = Container::VectorMap::VectorMap<VarT>;

    public:
        explicit ComputeConnectedComponents(VarT numberOfVariables)
            : subsetVector_(static_cast<typename SubsetVectorType::size_type>(1) + numberOfVariables),
              l_fromRootToComponentIndexVectorMap_computeConnectedComponents_(static_cast<std::size_t>(1) + static_cast<std::size_t>(numberOfVariables), 0) {
            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariables, 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", numberOfVariables);

            // Initialize parents
            for (VarT i = 0; i <= numberOfVariables; ++i)
                subsetVector_[i].parent = i;
        }

        ComputeConnectedComponents(const ComputeConnectedComponents&) = delete;
        ComputeConnectedComponents(ComputeConnectedComponents&&) noexcept = default;

        ComputeConnectedComponents& operator=(const ComputeConnectedComponents&) = delete;
        ComputeConnectedComponents& operator=(ComputeConnectedComponents&&) noexcept = default;

    private:
        SubsetVectorType subsetVector_;

        // Local auxiliary data structures for computeConnectedComponents
        VariableVectorMapType l_fromRootToComponentIndexVectorMap_computeConnectedComponents_;

        inline static constexpr VarT S_ESTIMATED_NUMBER_OF_CONNECTED_COMPONENTS_ = 4;

    private:
        /**
         * Note: the path compression technique is used
         * @param var a variable
         * @return the root of the component containing the variable
         */
        VarT find(VarT var) noexcept;

        /**
         * Unite two components defined by the roots
         * Assert: roots MUST differ
         * Assert: root1 MUST be a root
         * Assert: root2 MUST be a root
         * Note: union by rank is used
         * @param root1 first root
         * @param root2 second root
         */
        void unite(VarT root1, VarT root2);

    public:
        /**
         * Check if the data structure is empty
         * @return true if the data structure is empty. Otherwise, false is returned.
         */
        bool isEmpty() const noexcept;

        /**
         * If both variables belong to different components, then the components will be united. Otherwise, nothing happen.
         * @param var1 first variable
         * @param var2 second variable
         */
        void addConnection(VarT var1, VarT var2);

        /**
         * Compute connected components based on the actual state of the data structure
         * Assert: the root of an ignored variable MUST be that variable
         * Note: the data structure will be cleaned
         * Note: the ignored variables will not be added to the returned structure
         * Local auxiliary data structures:
         *      l_fromRootToComponentIndexVectorMap_computeConnectedComponents_
         * @param variableSet a variable set
         * @param ignoredVariableSet a set of ignored variables
         * @return the connected components
         */
        ConnectedComponentType computeConnectedComponents(const VariableSetType& variableSet, const VariableSetType& ignoredVariableSet = {});

    #ifndef NDEBUG
    public:
        void printComputeConnectedComponents(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Container::ComputeConnectedComponents

#include "./ComputeConnectedComponents.ipp"
