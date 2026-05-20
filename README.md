# libhs-cpp

Modern C++20 RAII wrapper for libhs-compatible pattern matching engines.

Compatible with:

* [Intel Hyperscan](https://github.com/intel/hyperscan)
* [VectorCamp VectorScan](https://github.com/VectorCamp/vectorscan)

# About

`libhs-cpp` is a modern C++20 wrapper around the `libhs` API ecosystem. It provides RAII abstractions for databases, scratch regions, streams, patterns, literals, scanners, and match callbacks while remaining fully compatible with existing Hyperscan-style APIs and workflows.

The underlying backend may be either Intel Hyperscan or VectorScan. Since both engines expose the same `libhs` API and ABI surface, applications can generally switch between backends without source modifications.

`libhs` is the shared C API and ABI exposed by both engines.

These engines are designed for high-performance multiple regular expression matching and are commonly used in:

* DPI
* IDS/IPS
* Filtering
* Malware analysis
* High-speed inspection pipelines

Features include:

* RAII resource management
* C++20 support
* Block and streaming scanning
* Multi-pattern compilation
* Literal matching support
* Exception-safe abstractions
* Minimal overhead wrapper design
* Backend-agnostic architecture

The public C++ namespace currently remains `HyperScan` for API compatibility and stability across releases.

# Backend Compatibility

This project targets the `libhs` API contract rather than a specific implementation.

Supported backends:

| Backend                                                           | Status    |
| ----------------------------------------------------------------- | --------- |
| [Intel Hyperscan](https://github.com/intel/hyperscan)             | Supported |
| [VectorCamp VectorScan](https://github.com/VectorCamp/vectorscan) | Supported |

Because both libraries expose compatible APIs and binary interfaces, applications built with `libhs-cpp` can typically switch between backends without source modifications.

# Requirements

* C++20 compatible compiler
* libhs-compatible backend
* Linux

# Installation Notes

Both Intel Hyperscan and VectorScan expose a compatible `libhs` API.

They generally provide:

```text
hs/hs.h
libhs.so
```

The exact install paths are platform and distribution dependent.

On Debian or Ubuntu systems, the shared library may be installed under an architecture-specific directory such as:

```text
/usr/include/hs/hs.h
/usr/lib/x86_64-linux-gnu/libhs.so
```

or:

```text
/lib/x86_64-linux-gnu/libhs.so
```

Because both backends provide the same header and library names, installing both globally may cause package conflicts or ambiguity.

If you need to choose a specific backend, pass the paths explicitly to CMake:

```bash
cmake -S . -B build \
  -DLIBHS_INCLUDE_DIR=/usr/include \
  -DLIBHS_LIBRARY=/usr/lib/x86_64-linux-gnu/libhs.so
```

For custom installs, separate prefixes are recommended:

```text
/opt/hyperscan
/opt/vectorscan
```

Example:

```bash
cmake -S . -B build \
  -DLIBHS_INCLUDE_DIR=/opt/vectorscan/include \
  -DLIBHS_LIBRARY=/opt/vectorscan/lib/libhs.so
```

# Build libhs-cpp

```bash
# Download libhs-cpp via Git
git clone https://github.com/ludvikjerabek/libhs-cpp.git

# Change directory into libhs-cpp source directory
cd libhs-cpp

# Create the Release build profile
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release

# Compile the code
cmake --build build

```

# Installing libhs-cpp

```bash
sudo cmake --install build
```

# Uninstalling libhs-cpp

```bash
sudo cmake --build build --target uninstall
```

# General Usage

The example below demonstrates a single-pattern block scan.

Additional examples can be found in the `examples` directory.

```cpp
#include <iostream>
#include <fstream>
#include <libhs-cpp/HyperScan.h>

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
