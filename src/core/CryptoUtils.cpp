#include "blockchain/CryptoUtils.h"

#include "../utils/picosha2.h"


namespace blockchain {

std::string sha256_hex(const std::string& input) {
    return picosha2::hash_hex_string(input);
}

} // namespace blockchain
