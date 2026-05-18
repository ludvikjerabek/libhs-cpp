# libhs-cpp

Modern C++20 RAII wrapper for Hyperscan-compatible pattern matching engines.

Compatible with:

* Intel Hyperscan
* VectorCamp VectorScan

# About

`libhs-cpp` is a modern C++20 wrapper around the `libhs` API ecosystem. It provides RAII abstractions for databases, scratch regions, streams, patterns, literals, scanners, and match callbacks while remaining fully compatible with existing Hyperscan-style APIs and workflows.

The underlying backend may be either Intel Hyperscan or VectorScan. Since both engines expose the same `libhs` API surface, no code changes are required when switching between implementations.

These engines are designed for high-performance multiple regular expression matching and are commonly used in DPI, IDS/IPS, filtering, malware analysis, and high-speed inspection pipelines.

Features include:

* RAII resource management
* C++20 support
* Block and streaming scanning
* Multi-pattern compilation
* Literal matching support
* Exception-safe abstractions
* Minimal overhead wrapper design
* Backend agnostic architecture

# Backend Compatibility

This project targets the `libhs` API contract rather than a specific implementation.

Supported backends:

| Backend               | Status    |
| --------------------- | --------- |
| Intel Hyperscan       | Supported |
| VectorCamp VectorScan | Supported |

Because both libraries expose compatible APIs and binary interfaces, applications built with `libhs-cpp` can typically switch between backends without source modifications.

# Installation Notes

Both Hyperscan and VectorScan generally install the same files:

```text
hs/hs.h
libhs.so
```

Because of this, installing both globally into the same system prefix may cause conflicts.

If multiple backends are installed, it is recommended to isolate them into separate installation prefixes such as:

```text
/opt/hyperscan
/opt/vectorscan
```

Then specify the backend explicitly during CMake configuration:

```bash
cmake -S . -B build \
  -DLIBHS_INCLUDE_DIR=/opt/vectorscan/include \
  -DLIBHS_LIBRARY=/opt/vectorscan/lib/libhs.so
```

# General Usage

The example below demonstrates a single-pattern block scan.

Additional examples can be found in the `examples` directory.

```cpp
#include <iostream>
#include <fstream>
#include "HyperScan.h"

using namespace std;

// Create a custom matcher object
class MyMatcher : public HyperScan::IMatcher {
public:
    MyMatcher() : matches(0) {}

    ~MyMatcher() = default;

    int OnMatch(unsigned int id,
                unsigned long long from,
                unsigned long long to,
                unsigned int flags) override
    {
        // Printing output slows scanning and is shown only for demonstration
        std::cout << "   ID: " << id << std::endl;
        std::cout << " From: " << from << std::endl;
        std::cout << "   To: " << to << std::endl;
        std::cout << "Flags: " << flags << std::endl;

        matches++;
        return 0;
    }

    void Dump() {
        std::cout << "Matches found: " << matches << std::endl;
    }

private:
    int matches;
};

int main() {

    // Validate platform support
    std::cout << "Platform Valid: "
              << HyperScan::ValidPlatform()
              << std::endl;

    // Get backend version information
    std::cout << "Engine Version: "
              << HyperScan::GetVersion()
              << std::endl;

    // Create a pattern
    HyperScan::Pattern pattern(
        "^192\\.152\\.201\\.85$",
        HyperScan::Pattern::CASELESS |
        HyperScan::Pattern::MULTILINE
    );

    // Create a block database
    HyperScan::BlockDatabase pattern_db =
        pattern.GetBlockDatabase();

    std::cout << "DB Size: "
              << pattern_db.GetSize()
              << std::endl;

    std::cout << "DB Info: "
              << pattern_db.GetInfo()
              << std::endl;

    // Create scratch space
    HyperScan::Scratch scratch =
        pattern_db.GetScratch();

    // Create matcher
    MyMatcher matcher;

    // Read input block
    std::ifstream file(
        "ips.txt",
        std::ios::binary | std::ios::ate
    );

    if (!file.is_open()) {
        std::cout << "Failed to open ips.txt"
                  << std::endl;
        return 1;
    }

    std::streamsize size = file.tellg();

    file.seekg(0, std::ios::beg);

    std::vector<char> block(size);

    file.read(block.data(), size);

    // Scan block
    HyperScan::Scanner::Scan(
        pattern_db,
        scratch,
        matcher,
        block
    );

    matcher.Dump();

    return 0;
}
```

# Virtual IMatcher vs C++20 Concepts

Performance testing showed no measurable performance penalty from virtual dispatch through `IMatcher`.

Since there was no significant difference in throughput, a concept-based matcher implementation was not added to the library in order to keep the API simpler and easier to maintain.

Benchmark sample:

```text
Matches found: 103,642,502

Non-Virtual Concept Matcher:

Time: 2070102 microseconds
Time: 2075437 microseconds
Time: 2040294 microseconds
Time: 2038348 microseconds
Time: 2051992 microseconds
Time: 2063293 microseconds
Time: 2058719 microseconds
Time: 2061387 microseconds
Time: 2056725 microseconds
Time: 2079855 microseconds

Virtual IMatcher:

Time: 2068737 microseconds
Time: 2048733 microseconds
Time: 2050551 microseconds
Time: 2058243 microseconds
Time: 2093890 microseconds
Time: 2069945 microseconds
Time: 2085806 microseconds
Time: 2079505 microseconds
Time: 2078688 microseconds
Time: 2057927 microseconds
```

# License

`libhs-cpp` is licensed under the MIT License.

See the LICENSE file for additional information.

# Versioning

The `master` branch always contains the most recent stable release.

All releases go through testing and validation before publication.
