#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::Container {

    /**
     * Container exception (main)
     */
    class ContainerException : public CompilerException {
    public:
        explicit ContainerException(const std::string& message)
            : CompilerException(message) { }

        explicit ContainerException(std::string&& message)
            : CompilerException(std::move(message)) { }
    };
}   // namespace Hydra::Exception::Container
