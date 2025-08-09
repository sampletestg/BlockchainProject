#include "blockchain/Block.h"
#include "blockchain/CryptoUtils.h"
#include <chrono>
#include <sstream>

namespace blockchain {

Block::Block(uint64_t index,
             const std::string& data,
             const std::string& previousHash,
             uint64_t timestamp)
    : m_index(index),
      m_data(data),
      m_previousHash(previousHash)
{
    if (timestamp == 0) {
        m_timestamp = static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()).count());
    } else {
        m_timestamp = timestamp;
    }
    m_hash = calculate_hash();
}

uint64_t Block::index() const noexcept { return m_index; }
uint64_t Block::timestamp() const noexcept { return m_timestamp; }
const std::string& Block::data() const noexcept { return m_data; }
const std::string& Block::previous_hash() const noexcept { return m_previousHash; }
const std::string& Block::hash() const noexcept { return m_hash; }
uint64_t Block::nonce() const noexcept { return m_nonce; }

std::string Block::calculate_hash() const {
    std::ostringstream oss;
    oss << m_index << m_timestamp << m_data << m_previousHash << m_nonce;
    return sha256_hex(oss.str());
}

void Block::mine(uint32_t difficulty) {
    if (difficulty == 0) {
        m_nonce = 0;
        m_hash = calculate_hash();
        return;
    }
    const std::string target(difficulty, '0');
    m_nonce = 0;
    while (true) {
        m_hash = calculate_hash();
        // check prefix zeros (hex char '0')
        if (m_hash.substr(0, difficulty) == target) break;
        ++m_nonce;
        // Avoid infinite loops in degenerate cases (practically you want small difficulty for demos)
    }
}

} // namespace blockchain
