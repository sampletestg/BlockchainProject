#pragma once
#include <string>
#include <cstdint>

namespace blockchain {

class Block {
public:
    Block() = default;
    Block(uint64_t index,
          const std::string& data,
          const std::string& previousHash,
          uint64_t timestamp = 0);

    // Accessors
    uint64_t index() const noexcept;
    uint64_t timestamp() const noexcept;
    const std::string& data() const noexcept;
    const std::string& previous_hash() const noexcept;
    const std::string& hash() const noexcept;
    uint64_t nonce() const noexcept;

    // Mining and hashing
    std::string calculate_hash() const;
    void mine(uint32_t difficulty);

private:
    uint64_t m_index{0};
    uint64_t m_timestamp{0};
    std::string m_data;
    std::string m_previousHash;
    std::string m_hash;
    uint64_t m_nonce{0};
};

} // namespace blockchain
