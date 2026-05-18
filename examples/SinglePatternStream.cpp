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
    HyperScan::Pattern pattern("^192\\.152\\.201\\.85$", HyperScan::Pattern::CASELESS | HyperScan::Pattern::MULTILINE);

    // Create a stream database from the current pattern object
    HyperScan::StreamDatabase pattern_db = pattern.GetStreamDatabase();

    // Additional data you can query from the DB no required but just for visibility
    std::cout << "DB Size: " << pattern_db.GetSize() << std::endl;
    std::cout << "DB Info: " << pattern_db.GetInfo() << std::endl;

    // Create a Scratch object from the DB
    HyperScan::Scratch scratch = pattern_db.GetScratch();

    // Create your custom matcher object
    MyMatcher matcher;

    // Reading data in chunks (stream simulation)
    std::ifstream file("ips.txt", std::ifstream::binary);
    if (!file.is_open()) {
        std::cout << "Failed to open ips.txt" << std::endl;
        return 1;
    }
    std::vector<char> buffer(1024, 0); //reads only the first 1024 bytes

    // Create a stream scanner object.
    HyperScan::Stream stream;

    // Open the HS stream (hs_open_stream)
    stream.Open(pattern_db);

    // Process the data in chunks and pass it to the stream.
    while (!file.eof()) {
        file.read(buffer.data(), buffer.size());
        std::streamsize s = file.gcount();
        HyperScan::Scanner::Scan(stream,scratch,matcher, buffer.data(), s);
    }
    // Close the HS stream (hs_close_stream)
    stream.Close(scratch,matcher);

    matcher.Dump();

    return 0;
}
