#pragma once
#include "Block.h"
#include <vector>
#include <cstdint>
#include <string>

namespace blockchain {

class Blockchain {
public:
    explicit Blockchain(uint32_t difficulty = 3);

    // genesis
    void create_genesis_block();

    // add and mine block
    void add_block(const std::string& data);

    // read
    const std::vector<Block>& chain() const noexcept;

    // validation
    bool is_chain_valid() const;

    // utility
    uint32_t difficulty() const noexcept;

private:
    std::vector<Block> m_chain;
    uint32_t m_difficulty{3};
};

} // namespace blockchain
