# optree

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![Header Only](https://img.shields.io/badge/Header--Only-Yes-green.svg?style=flat)](#installation)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)](https://opensource.org/licenses/MIT)

`optree` is a lightweight, modern, header-only C++17 library designed for managing complex, hierarchical configurations and program options. It allows you to organize application options into a tree structure, enforce type safety and constraints, parse command-line arguments, generate autocomplete shell scripts, and integrate seamlessly with JSON (`nlohmann_json`).

---

## Key Features

- 📦 **Header-Only & Modern C++**: Easy to integrate, header-only, leveraging C++17 features.
- 🌳 **Hierarchical Option Groups**: Nest option groups (using `OptionGroup`) to match your system design.
- 🔗 **Dot-Notation Path Registry**: Access and modify nested configurations directly via dot-notation (e.g., `sys.sub.threads`).
- ⚡ **Smart Propagation**:
  - Target specific options directly (e.g., `--sys.sub.threads=12`).
  - Broadcast a generic parameter globally (e.g., `--threads=8` or `--verbosity=3`), which propagates to all matching option fields in the hierarchy.
- 🛡️ **Type Safety & Validation**:
  - Built-in type conversions (`int`, `double`, `bool`, `std::string`, etc.).
  - Range boundaries (minimum and maximum bounds validation).
  - Custom Enum support with pretty string mapping using `EnumMetadata<T>`.
- 💻 **Command-Line Parsing**: Parse arguments directly from `argv` including standard formats and flags.
- 🪄 **Dynamic Shell Autocomplete**: Auto-generates complete, context-aware Bash autocomplete scripts (`--completion-script`) containing all option keys, enums, and boolean helpers.
- ⚙️ **JSON Support**: Bidirectional serialization and deserialization using `nlohmann_json` (macros are entirely optional for enums, none are used for groups).

---

## Repository Structure

```text
optree/
├── CMakeLists.txt        # Build configurations and test targets
├── README.md             # Project documentation
├── include/              # Public header files
│   └── optree/
│       ├── EnumMetadata.hpp   # Custom Enum string binding
│       ├── Option.hpp         # The main Option class (with ranges and validation)
│       ├── OptionBase.hpp     # Abstract base class for options & groups
│       ├── OptionGroup.hpp    # Container for logical option subgroups
│       ├── OptionJson.hpp     # JSON serialization helpers (optional)
│       └── OptionRegistry.hpp # Flat registry tracking options & groups
└── tests/
    └── test_optree.cpp   # Comprehensive unit tests
```

---

## Quick Start

### 1. Define Options and Groups

You can define options by instantiating `optree::Option<T>` inside an `optree::OptionGroup`.

```cpp
#include "optree/Option.hpp"
#include "optree/OptionGroup.hpp"
#include "optree/OptionRegistry.hpp"

// Define a subgroup configuration
class DBConfig : public optree::OptionGroup {
public:
    DBConfig(const std::string& name) : OptionGroup(name, "Database settings") {}

    optree::Option<std::string> host{"host", "Database server host", "127.0.0.1"};
    optree::Option<int> port{"port", "Database port connection", 5432, 1024, 65535}; // constrained [1024, 65535]

    std::vector<optree::OptionBase*> getAllOptions() override {
        return { &host, &port };
    }
};

// Define main/parent configuration group
class AppConfig : public optree::OptionGroup {
public:
    AppConfig(const std::string& name) : OptionGroup(name, "Main Application settings") {}

    optree::Option<int> threads{"threads", "Execution threads", 4};
    optree::Option<bool> debug{"debug", "Enable debug prints", false};
    
    DBConfig db{"db"}; // Nested group

    std::vector<optree::OptionBase*> getAllOptions() override {
        return { &threads, &debug, &db };
    }
};
```

### 2. Custom Enum Mapping

Map enum classes to human-readable strings by specializing `optree::EnumMetadata<T>`:

```cpp
#include "optree/EnumMetadata.hpp"

enum class LogLevel { INFO, WARNING, ERROR };

namespace optree {
template<>
struct EnumMetadata<LogLevel> {
    static std::map<int, std::string> mapping() {
        return {
            {static_cast<int>(LogLevel::INFO), "info"},
            {static_cast<int>(LogLevel::WARNING), "warning"},
            {static_cast<int>(LogLevel::ERROR), "error"}
        };
    }
    static std::string name() { return "LogLevel"; }
};
}
```

### 3. Registry & Value Propagation

Create an `OptionRegistry` and register your top-level group.

```cpp
#include <iostream>

int main() {
    optree::OptionRegistry registry;
    AppConfig config("app");
    config.registerTo(registry);

    // 1. Direct path update
    registry.setOption("app.db.port", "8080");
    std::cout << config.db.port.get() << "\n"; // Output: 8080

    // 2. Broadcast propagation (sets "threads" globally in all registered groups/subgroups)
    registry.setOption("threads", "16");
    std::cout << config.threads.get() << "\n"; // Output: 16
    
    // 3. Display interactive help menu / tree view
    registry.displayHelp(std::cout);
}
```

### 4. Parsing Command Line Arguments & Auto-Completion

`OptionRegistry` makes it easy to parse standard `argv` options out of the box:

```cpp
int main(int argc, char* argv[]) {
    optree::OptionRegistry registry;
    AppConfig config("app");
    config.registerTo(registry);

    // Automatically processes options like:
    // --app.threads=8 --app.debug --app.db.host=192.168.1.1
    // Also intercepts --completion-script and --dump-options
    registry.parseArgv(argc, argv);
}
```

#### Bash Auto-Completion Setup

To enable auto-completion for your binary in the shell, register the completion hook:

```bash
# Source the auto-generated script directly in your terminal:
source <(/path/to/your_binary --completion-script)
```

Now, typing `/path/to/your_binary --[TAB]` will autocomplete nested flags and their corresponding options or values!

### 5. JSON Integration

Using the `OptionJson.hpp` helper header, you can export and update configuration states using `nlohmann_json`.

```cpp
#include "optree/OptionJson.hpp"

// Update configurations directly from a JSON string or object
std::string jsonConfig = R"({
    "app": {
        "threads": 32,
        "db": {
            "host": "production-db.internal"
        }
    }
})";
optree::updateRegistryFromJson(registry, jsonConfig);

// Serialize configuration registry to JSON object
nlohmann::json rootJson = optree::convertRegistryToJson(registry);
std::cout << rootJson.dump(4) << std::endl;
```

---

## Building and Running Tests

You can build the tests included in the repository by standard CMake directives.

```bash
# 1. Create build directory
mkdir build && cd build

# 2. Configure and build
cmake ..
make

# 3. Run unit tests
ctest
# Or execute test runner directly:
./test_optree
```

*Note: If `nlohmann_json` is not found installed on your system, CMake will automatically download it during configuration via `FetchContent`.*

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
