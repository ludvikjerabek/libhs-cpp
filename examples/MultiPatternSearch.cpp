#include <iostream>
#include <fstream>
#include <HyperScan.h>

using namespace std;

// Create a custom IMatcher object to deal with context and matching.
class MyMatcher : public HyperScan::IMatcher {
public:
    MyMatcher() : matches(0) {}

    ~MyMatcher() = default;

    // OnMatch is called when a match occurs
    int OnMatch(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags) override {
        // Printing output will slow down matching but it's for demonstration purposes.
        std::cout << "   ID: " << id << std::endl;
        std::cout << " From: " << from << std::endl;
        std::cout << "   To: " << to << std::endl;
        std::cout << "Flags: " << flags << std::endl;
        // Count matches
        matches++;
        return 0;
    }

    // Show number or matches for the data set
    void Dump() {
        std::cout << "Matches found: " << matches << std::endl;
    }

private:
    int matches;
};

int main() {
    // Global HyperScan or VectorScan functions

    // Hyperscan requires the Supplemental Streaming SIMD Extensions 3 instruction set. This function can be called
    // on any x86 platform to determine if the system provides the required instruction set.
    std::cout << "HyperScan Valid: " << HyperScan::ValidPlatform() << std::endl;

    // Get the version information. A string containing the version number of this release build and the date of the build.
    std::cout << "HyperScan Version: " << HyperScan::GetVersion() << std::endl;

    // Create a pattern object
    HyperScan::MultiPattern multi_pattern;
    multi_pattern.AddPattern("^192\\.152\\.201\\.85$", HyperScan::Pattern::CASELESS | HyperScan::Pattern::MULTILINE, 1);
    multi_pattern.AddPattern("^136\\.147\\.188\\.21$", HyperScan::Pattern::CASELESS | HyperScan::Pattern::MULTILINE, 2);

    // Create a block database from the current pattern object
    HyperScan::BlockDatabase pattern_db = multi_pattern.GetBlockDatabase();

    // Additional data you can query from the DB no required but just for visibility
    std::cout << "DB Size: " << pattern_db.GetSize() << std::endl;
    std::cout << "DB Info: " << pattern_db.GetInfo() << std::endl;

    // Create a Scratch object from the DB
    HyperScan::Scratch scratch = pattern_db.GetScratch();

    // Create your custom matcher object
    MyMatcher matcher;

    // Read a block of data
    std::ifstream file("ips.txt", std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cout << "Failed to open ips.txt" << std::endl;
        return 1;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> block(size);
    file.read(block.data(), size);
    // Scan the block of data

    HyperScan::Scanner::Scan(pattern_db, scratch, matcher, block);

    matcher.Dump();

    return 0;
}
