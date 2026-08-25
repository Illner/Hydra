#pragma once

#include "Option.hpp"
#include "OptionBase.hpp"
#include "OptionRegistry.hpp"
#include <string>
#include <vector>

namespace optree {

    /**
 * @brief A group of options that can be registered hierarchically.
 */
    class OptionGroup : public OptionBase {
    public:
        OptionGroup(const std::string& name, const std::string& description)
            : m_name(name), m_description(description) { }

        virtual ~OptionGroup() = default;

        /** @brief Verbosity level for this group. */
        Option<int> verbosity { "verbosity", "Verbosity level", 0 };

        std::string getName() const override { return m_name; }
        std::string getDescription() const override { return m_description; }
        std::string getValueAsString() const override { return ""; }
        void setFromString(const std::string&) override { }
        std::string getTypeName() const override { return "group"; }
        std::string getPossibleValues() const override { return ""; }

        /** @brief Get all options in this group. Must be implemented by subclasses. */
        virtual std::vector<OptionBase*> getAllOptions() = 0;

        /** @brief Register the group and its children to a registry. */
        void registerTo(OptionRegistry& registry, const std::string& prefix = "") override {
            std::string newPrefix = prefix;
            if (!m_name.empty()) {
                newPrefix += m_name;
                registry.registerGroup(newPrefix, this);
                newPrefix += ".";
            }
            else {
                std::string groupPath = prefix;
                if (!groupPath.empty() && groupPath.back() == '.') {
                    groupPath.pop_back();
                }
                registry.registerGroup(groupPath, this);
            }

            verbosity.registerTo(registry, newPrefix);

            for (auto* opt : getAllOptions()) {
                if (opt) {
                    opt->registerTo(registry, newPrefix);
                }
            }
        }

        bool setPropagation(const std::string& name, const std::string& value) override {
            bool consumed = verbosity.setPropagation(name, value);
            for (auto* opt : getAllOptions()) {
                if (opt) {
                    if (opt->setPropagation(name, value)) {
                        consumed = true;
                    }
                }
            }
            return consumed;
        }

    protected:
        std::string m_name;
        std::string m_description;
    };

}   // namespace optree
