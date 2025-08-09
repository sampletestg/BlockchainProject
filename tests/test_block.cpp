#include <cassert>
#include <iostream>
#include "blockchain/Block.h"

int main() {
    blockchain::Block b(1, "hello", "0", 12345);
    std::string h1 = b.calculate_hash();
    b.mine(2); // small difficulty for test
    std::string h2 = b.hash();
    assert(h2.size() == 64); // hex length for sha256
    std::cout << "test_block passed\n";
    return 0;
}
