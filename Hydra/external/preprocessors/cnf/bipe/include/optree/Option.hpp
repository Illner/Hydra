#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "EnumMetadata.hpp"
#include "OptionBase.hpp"
#include "OptionRegistry.hpp"

namespace optree {

    template <typename U, typename = void>
    struct is_comparable : std::false_type { };

    template <typename U>
    struct is_comparable<U, std::void_t<decltype(std::declval<U>() < std::declval<U>())>> : std::true_type { };

    template <typename U, typename = void>
    struct is_stream_insertable : std::false_type { };

    template <typename U>
    struct is_stream_insertable<U, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const U&>())>> : std::true_type { };

    template <typename U, typename = void>
    struct is_stream_extractable : std::false_type { };

    template <typename U>
    struct is_stream_extractable<U, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<U&>())>> : std::true_type { };

    /**
 * @brief Concrete implementation of an option for a specific type T.
 */
    template <typename T>
    class Option : public OptionBase {
    public:
        Option() : m_name(""), m_description(""), m_value(T()) { }

        Option(const std::string& name, const std::string& description, T defaultValue,
               std::optional<T> minValue = std::nullopt, std::optional<T> maxValue = std::nullopt)
            : m_name(name), m_description(description), m_value(defaultValue),
              m_min(minValue), m_max(maxValue) {
            validate(defaultValue);
        }

        std::string getName() const override { return m_name; }
        std::string getDescription() const override { return m_description; }

        std::string valueToString(const T& val) const {
            if constexpr (std::is_same_v<T, std::string>) {
                return val;
            }
            else if constexpr (std::is_same_v<T, bool>) {
                return val ? "true" : "false";
            }
            else if constexpr (std::is_enum_v<T>) {
                return enum_to_string(val);
            }
            else {
                if constexpr (is_stream_insertable<T>::value) {
                    std::stringstream ss;
                    ss << val;
                    return ss.str();
                }
                else {
                    return "";
                }
            }
        }

        std::string getValueAsString() const override {
            return valueToString(m_value);
        }

        void setFromString(const std::string& value) override {
            T tempValue = m_value;
            if constexpr (std::is_same_v<T, std::string>) {
                tempValue = value;
            }
            else if constexpr (std::is_same_v<T, bool>) {
                tempValue = (value == "true" || value == "1" || value == "yes" || value == "on");
            }
            else if constexpr (std::is_enum_v<T>) {
                try {
                    tempValue = resolve_enum<T>(value);
                }
                catch (...) {
                }
            }
            else {
                if constexpr (is_stream_extractable<T>::value) {
                    std::stringstream ss(value);
                    ss >> tempValue;
                }
            }
            validate(tempValue);
            m_value = tempValue;
        }

        std::string getTypeName() const override {
            if constexpr (std::is_same_v<T, std::string>)
                return "string";
            if constexpr (std::is_same_v<T, bool>)
                return "bool";
            if constexpr (std::is_same_v<T, int>)
                return "int";
            if constexpr (std::is_same_v<T, unsigned>)
                return "uint";
            if constexpr (std::is_same_v<T, float>)
                return "float";
            if constexpr (std::is_same_v<T, double>)
                return "double";
            if constexpr (std::is_enum_v<T>)
                return "enum";
            return "unknown";
        }

        std::string getPossibleValues() const override {
            if constexpr (std::is_enum_v<T>) {
                return get_enum_doc<T>();
            }
            if (m_min || m_max) {
                std::string res = "[";
                if (m_min) {
                    res += valueToString(*m_min);
                }
                else {
                    res += "...";
                }
                res += ", ";
                if (m_max) {
                    res += valueToString(*m_max);
                }
                else {
                    res += "...";
                }
                res += "]";
                return res;
            }
            return "";
        }

        std::string getMinAsString() const override {
            return m_min ? valueToString(*m_min) : "";
        }

        std::string getMaxAsString() const override {
            return m_max ? valueToString(*m_max) : "";
        }

        const T& get() const { return m_value; }

        void set(const T& value) {
            validate(value);
            m_value = value;
        }

        std::optional<T> getMin() const { return m_min; }
        std::optional<T> getMax() const { return m_max; }

        void setMin(std::optional<T> minValue) {
            m_min = minValue;
            validate(m_value);
        }

        void setMax(std::optional<T> maxValue) {
            m_max = maxValue;
            validate(m_value);
        }

        /** @brief Implicit conversion to T. */
        operator T() const { return m_value; }

        /** @brief Assignment from T. */
        Option& operator=(const T& value) {
            set(value);
            return *this;
        }

        void registerTo(OptionRegistry& registry, const std::string& prefix = "") override {
            registry.registerOption(prefix + getName(), this);
        }

        bool setPropagation(const std::string& name, const std::string& value) override {
            if (m_name == name) {
                setFromString(value);
                return true;
            }
            return false;
        }

    private:
        void validate(const T& value) const {
            if constexpr (is_comparable<T>::value) {
                if (m_min && value < *m_min) {
                    throw std::out_of_range("Option '" + m_name + "' value " + valueToString(value) +
                                            " is below the minimum limit of " + valueToString(*m_min));
                }
                if (m_max && *m_max < value) {
                    throw std::out_of_range("Option '" + m_name + "' value " + valueToString(value) +
                                            " is above the maximum limit of " + valueToString(*m_max));
                }
            }
        }

        std::string m_name;
        std::string m_description;
        T m_value;
        std::optional<T> m_min;
        std::optional<T> m_max;
    };

}   // namespace optree
