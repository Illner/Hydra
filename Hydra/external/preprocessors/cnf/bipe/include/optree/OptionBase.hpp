#pragma once
#include <string>

namespace optree {

    class OptionRegistry;

    /**
 * @brief Virtual base class for all options and option groups.
 */
    class OptionBase {
    public:
        virtual ~OptionBase() = default;

        /** @brief Get the name of the option. */
        virtual std::string getName() const = 0;

        /** @brief Get the description of the option. */
        virtual std::string getDescription() const = 0;

        /** @brief Get the current value as a string. */
        virtual std::string getValueAsString() const = 0;

        /** @brief Set the value from a string. */
        virtual void setFromString(const std::string& value) = 0;

        /** @brief Get the type name of the option (e.g. "int", "bool"). */
        virtual std::string getTypeName() const = 0;

        /** @brief Get a list of possible values (for enums). */
        virtual std::string getPossibleValues() const = 0;

        /** @brief Get the minimum value as a string (if constrained). */
        virtual std::string getMinAsString() const { return ""; }

        /** @brief Get the maximum value as a string (if constrained). */
        virtual std::string getMaxAsString() const { return ""; }

        /** @brief Register the option to a registry with a prefix. */
        virtual void registerTo(OptionRegistry& registry, const std::string& prefix = "") = 0;

        /** @brief Try to set an option by name within this object or its children. Returns true if the option was matched and set. */
        virtual bool setPropagation(const std::string& name, const std::string& value) = 0;
    };

}   // namespace optree
