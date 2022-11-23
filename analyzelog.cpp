https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " logfile" << std::endl;
        return 1;
    }
    std::ifstream infile(argv[1]);

    std::string line;
    char op, colon;
    typedef unsigned int Instruction;
    typedef unsigned int Address;
    unsigned int data;
    Instruction previous = 0xdeadbeef;

    // This is a stupid cache. It has one entry of one word.
    Address cache[1];
    cache[0] = 0xcafebabe;
    unsigned int cache_hits = 0;
    unsigned int cache_misses = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> op >> colon >> std::hex >> data)) {
            std::cerr << "Parse error: " << line << std::endl;
            break;
        }
        std::cout << std::hex << std::setfill('0') << std::setw(8) << std::showbase;

        /*
         * Here's where your logic goes.
         */

        switch(op) {
        case 'i':
            std::cout << "I see an instruction: "
                      << data << std::endl;
            std::cout << "The previous instruction I ran was: "
                      << previous << std::endl;
            previous = data;    // for next time
            break;
        case 'I':
            std::cout << "I accessed an instruction at address: "
                      << data << std::endl;
            break;
        case 'L':
            std::cout << "I issued a load from memory address: "
                      << data << std::endl;
            // let's see if it's a hit!
            // our cache stores a whole word, so any access within the word
            //   should be a hit
            data &= 0xfffffffc; // this sets bottom two bits to zero
            if (data == cache[0]) {
                cache_hits++;
                std::cout << "That data access was a hit in cache!" << std::endl;
            } else {
                cache_misses++;
                std::cout << "That data access was a miss in cache!" << std::endl
                          << "What was actually in that cache slot was " << cache[0] << std::endl;

                // now update the cache
                cache[0] = data;
            }
            break;
        case 'S':
            std::cout << "I issued a store to memory address: "
                      << data << std::endl;
            break;
        default:
            std::cerr << "Something went wrong: I see op " << op << std::endl;
            return -1;
            break;
        }

    }
    std::cout << std::dec << std::setw(0) << std::noshowbase;
    std::cout << std::dec << "I saw " << cache_hits << " cache hits and " << cache_misses << " cache misses" << std::endl;
    return 0;
}
