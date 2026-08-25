#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "OptionBase.hpp"

namespace optree {

    /**
   * @brief Registry to manage dot-notation paths for options.
   */
    class OptionRegistry {
    public:
        /** @brief Register an option with a specific path. */
        void registerOption(const std::string& path, OptionBase* option) {
            m_options[path] = option;
        }

        /** @brief Check if an option exists. */
        bool hasOption(const std::string& path) const {
            return m_options.count(path) > 0;
        }

        /** @brief Set an option from a string value by propagating it from its parent group. Returns true if the option was matched and set. */
        bool setOption(const std::string& path, const std::string& value) {
            std::string groupPath;
            std::string optName;
            auto lastDot = path.find_last_of('.');

            if (lastDot == std::string::npos) {
                groupPath = "";   // Root
                optName = path;
            }
            else {
                groupPath = path.substr(0, lastDot);
                optName = path.substr(lastDot + 1);
            }

            bool consumed = false;
            if (groupPath == "") {
                // 1. Check if the option is directly registered at the root (flat option)
                auto itOpt = m_options.find(path);
                if (itOpt != m_options.end()) {
                    itOpt->second->setFromString(value);
                    consumed = true;
                }

                // 2. Broadcast to all top-level groups
                for (const auto& [gPath, group] : m_groups) {
                    if (gPath.find('.') == std::string::npos) {
                        if (group->setPropagation(optName, value)) {
                            consumed = true;
                        }
                    }
                }
            }
            else {
                auto itGroup = m_groups.find(groupPath);
                if (itGroup != m_groups.end()) {
                    consumed = itGroup->second->setPropagation(optName, value);
                }
            }

            if (!consumed) {
                std::cerr << "Warning: Option '" << path << "' was not consumed (unknown option)." << std::endl;
            }
            return consumed;
        }

        /** @brief Set multiple options from a vector of pairs, sorted by depth. */
        void setOptions(std::vector<std::pair<std::string, std::string>> options) {
            // Sort options by depth (number of dots) to ensure top-to-bottom order
            std::stable_sort(options.begin(), options.end(),
                             [](const auto& a, const auto& b) {
                                 auto countDots = [](const std::string& s) {
                                     return (size_t)std::count(s.begin(), s.end(), '.');
                                 };
                                 return countDots(a.first) < countDots(b.first);
                             });

            for (const auto& opt : options) {
                setOption(opt.first, opt.second);
            }
        }

        /** @brief Parse command line arguments and apply them. */
        void parseArgv(int argc, char* argv[]) {
            std::vector<std::pair<std::string, std::string>> collectedOptions;
            for (int i = 1; i < argc; ++i) {
                std::string arg = argv[i];
                if (arg == "--completion-script") {
                    std::string exePath = argv[0];
                    auto lastSlash = exePath.find_last_of("/\\");
                    std::string exeName = (lastSlash == std::string::npos) ? exePath : exePath.substr(lastSlash + 1);
                    std::cout << "# Bash completion script for " << exeName << "\n"
                              << "# Source this file in your shell:\n"
                              << "#   source <(" << argv[0] << " --completion-script)\n\n"
                              << "_" << exeName << "_completion() {\n"
                              << "    local cur prev opts\n"
                              << "    COMPREPLY=()\n"
                              << "    cur=\"${COMP_WORDS[COMP_CWORD]}\"\n"
                              << "    prev=\"${COMP_WORDS[COMP_CWORD-1]}\"\n\n"
                              << "    if [[ \"$prev\" == \"-i\" || \"$prev\" == \"--input\" || \"$prev\" == \"--inputName\" ]]; then\n"
                              << "        return 0\n"
                              << "    fi\n\n"
                              << "    # Handle completion of values after \"=\"\n"
                              << "    local opt_name=\"\"\n"
                              << "    local opt_val=\"\"\n"
                              << "    if [[ \"$cur\" == *=* ]]; then\n"
                              << "        opt_name=\"${cur%%=*}\"\n"
                              << "        opt_val=\"${cur#*=}\"\n"
                              << "    elif [[ \"$prev\" == \"=\" ]]; then\n"
                              << "        opt_name=\"${COMP_WORDS[COMP_CWORD-2]}\"\n"
                              << "        opt_val=\"$cur\"\n"
                              << "    fi\n\n"
                              << "    if [[ -n \"$opt_name\" ]]; then\n"
                              << "        case \"$opt_name\" in\n";
                    for (const auto& [path, opt] : m_options) {
                        std::string possible = opt->getPossibleValues();
                        std::vector<std::string> values;
                        if (!possible.empty()) {
                            size_t start = 0;
                            while (start < possible.size()) {
                                size_t end = possible.find(',', start);
                                std::string item = (end == std::string::npos) ? possible.substr(start) : possible.substr(start, end - start);
                                size_t eq = item.find('=');
                                if (eq != std::string::npos) {
                                    std::string val = item.substr(eq + 1);
                                    while (!val.empty() && std::isspace(val.front())) val.erase(val.begin());
                                    while (!val.empty() && std::isspace(val.back())) val.pop_back();
                                    values.push_back(val);
                                }
                                else {
                                    std::string val = item;
                                    while (!val.empty() && std::isspace(val.front())) val.erase(val.begin());
                                    while (!val.empty() && std::isspace(val.back())) val.pop_back();
                                    values.push_back(val);
                                }
                                if (end == std::string::npos)
                                    break;
                                start = end + 1;
                            }
                        }
                        if (opt->getTypeName() == "bool" || opt->getTypeName() == "boolean") {
                            values.push_back("true");
                            values.push_back("false");
                        }
                        if (!values.empty()) {
                            std::cout << "            --" << path << ")\n"
                                      << "                COMPREPLY=( $(compgen -W \"";
                            for (size_t i = 0; i < values.size(); ++i) {
                                std::cout << values[i] << (i + 1 < values.size() ? " " : "");
                            }
                            std::cout << "\" -- \"$opt_val\") )\n"
                                      << "                return 0\n"
                                      << "                ;;\n";
                        }
                    }
                    std::cout << "        esac\n"
                              << "        return 0\n"
                              << "    fi\n\n"
                              << "    if [[ \"$cur\" != -* ]]; then\n"
                              << "        return 0\n"
                              << "    fi\n\n"
                              << "    # Run the executable with --dump-options to get the list of options dynamically\n"
                              << "    local cmd=\"${COMP_WORDS[0]}\"\n"
                              << "    if [[ -x \"$cmd\" ]]; then\n"
                              << "        opts=$(\"$cmd\" --dump-options 2>/dev/null)\n"
                              << "    else\n"
                              << "        opts=$(command -v \"$cmd\" &>/dev/null && \"$cmd\" --dump-options 2>/dev/null)\n"
                              << "    fi\n\n"
                              << "    if [[ -n \"$opts\" ]]; then\n"
                              << "        local formatted_opts=\"\"\n"
                              << "        for opt in $opts; do\n"
                              << "            if [[ \"$opt\" == --* ]]; then\n"
                              << "                formatted_opts=\"$formatted_opts ${opt}=\"\n"
                              << "            else\n"
                              << "                formatted_opts=\"$formatted_opts $opt\"\n"
                              << "            fi\n"
                              << "        done\n\n"
                              << "        # Use nospace option if the selected option ends with \"=\"\n"
                              << "        if [[ \"$cur\" == --* ]]; then\n"
                              << "            compopt -o nospace 2>/dev/null\n"
                              << "        fi\n\n"
                              << "        COMPREPLY=( $(compgen -W \"$formatted_opts\" -- \"$cur\") )\n"
                              << "        return 0\n"
                              << "    fi\n"
                              << "}\n\n"
                              << "complete -o default -o filenames -F _" << exeName << "_completion " << exeName << " " << argv[0] << "\n";
                    exit(0);
                }
                if (arg == "--dump-options") {
                    std::set<std::string> opts;
                    for (const auto& [path, opt] : m_options) {
                        opts.insert("--" + path);
                    }
                    opts.insert("-i");
                    for (const auto& o : opts) {
                        std::cout << o << "\n";
                    }
                    exit(0);
                }

                if (arg.size() > 2 && arg.substr(0, 2) == "--") {
                    std::string key, value;
                    auto eqPos = arg.find('=');
                    if (eqPos != std::string::npos) {
                        key = arg.substr(2, eqPos - 2);
                        value = arg.substr(eqPos + 1);
                    }
                    else if (i + 1 < argc) {
                        key = arg.substr(2);
                        std::string next = argv[i + 1];
                        if (next.size() < 2 || next.substr(0, 2) != "--") {
                            value = next;
                            ++i;
                        }
                        else {
                            value = "true";
                        }
                    }
                    else {
                        key = arg.substr(2);
                        value = "true";
                    }
                    collectedOptions.push_back({ key, value });
                }
            }

            setOptions(collectedOptions);
        }

        /** @brief Display a pretty tree of all registered options. */
        void displayHelp(std::ostream& out) const {
            out << "\n\033[1;36mAvailable Options (use "
                   "--path.to.option=value):\033[0m\n";
            out << "\033[90mNote: Modifying an argument without its exact path (e.g. --verbosity=1)\n"
                   "      will automatically propagate the value to all matching child options.\033[0m\n";
            std::set<std::string> displayed_nodes;
            renderTree(out, "", "", displayed_nodes);
            out << std::endl;
        }

        void renderTree(std::ostream& out, const std::string& prefix,
                        const std::string& currentPath,
                        std::set<std::string>& displayed) const {
            std::map<std::string, bool> children;
            for (const auto& [path, opt] : m_options) {
                if (currentPath.empty() || (path.size() > currentPath.size() &&
                                            path.substr(0, currentPath.size() + 1) ==
                                                    currentPath + ".")) {
                    std::string remaining =
                            currentPath.empty() ? path : path.substr(currentPath.size() + 1);
                    auto dotPos = remaining.find('.');
                    std::string name = (dotPos == std::string::npos)
                                               ? remaining
                                               : remaining.substr(0, dotPos);
                    children[name] = (dotPos == std::string::npos);
                }
            }

            for (const auto& [name, isLeaf] : children) {
                std::string fullPath =
                        currentPath.empty() ? name : currentPath + "." + name;
                out << prefix << "└── " << name;
                if (isLeaf) {
                    OptionBase* opt = m_options.at(fullPath);
                    out << " \033[90m(" << opt->getTypeName() << ")\033[0m : "
                        << opt->getDescription() << " \033[33m[current value: "
                        << opt->getValueAsString() << "]\033[0m";
                    std::string possible = opt->getPossibleValues();
                    if (!possible.empty())
                        out << " \033[94m{" << possible << "}\033[0m";
                    out << "\n";
                }
                else {
                    out << "/\n";
                    renderTree(out, prefix + "    ", fullPath, displayed);
                }
            }
        }

        const std::map<std::string, OptionBase*>& getOptions() const {
            return m_options;
        }

        void registerGroup(const std::string& path, OptionBase* group) {
            if (m_groups.find(path) == m_groups.end()) {
                m_groups[path] = group;
            }
        }

    private:
        std::map<std::string, OptionBase*> m_options;
        std::map<std::string, OptionBase*> m_groups;
    };

}   // namespace optree
