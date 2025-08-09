#include "blockchain/Blockchain.h"
#include "blockchain/Block.h"
#include "blockchain/CryptoUtils.h"
#include "blockchain/Exceptions.h"
#include <iostream>

namespace blockchain {

Blockchain::Blockchain(uint32_t difficulty)
    : m_difficulty(difficulty)
{
    create_genesis_block();
}

void Blockchain::create_genesis_block() {
    if (!m_chain.empty()) return;
    Block genesis(0, "Genesis Block", "0");
    genesis.mine(m_difficulty);
    m_chain.push_back(genesis);
}

void Blockchain::add_block(const std::string& data) {
    if (m_chain.empty()) create_genesis_block();
    uint64_t index = m_chain.back().index() + 1;
    std::string prevHash = m_chain.back().hash();
    Block newBlock(index, data, prevHash);
    newBlock.mine(m_difficulty);
    m_chain.push_back(newBlock);
}

const std::vector<Block>& Blockchain::chain() const noexcept {
    return m_chain;
}

uint32_t Blockchain::difficulty() const noexcept { return m_difficulty; }

bool Blockchain::is_chain_valid() const {
    if (m_chain.empty()) return true;
    for (size_t i = 1; i < m_chain.size(); ++i) {
        const Block& current = m_chain[i];
        const Block& previous = m_chain[i-1];
        if (current.hash() != current.calculate_hash()) {
            std::cerr << "Block " << i << " has invalid hash\n";
            return false;
        }
        if (current.previous_hash() != previous.hash()) {
            std::cerr << "Block " << i << " has invalid previous hash\n";
            return false;
        }
        // check proof of work prefix
        std::string target(m_difficulty, '0');
        if (current.hash().substr(0, m_difficulty) != target) {
            std::cerr << "Block " << i << " hasn't been mined to difficulty\n";
            return false;
        }
    }
    return true;
}

} // namespace blockchain
