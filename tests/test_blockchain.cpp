#include <cassert>
#include <iostream>
#include "blockchain/Blockchain.h"

int main() {
    blockchain::Blockchain bc(2);
    assert(bc.chain().size() >= 1);
    bc.add_block("t1");
    bc.add_block("t2");
    assert(bc.chain().size() == 3);
    assert(bc.is_chain_valid());
    std::cout << "test_blockchain passed\n";
    return 0;
}
