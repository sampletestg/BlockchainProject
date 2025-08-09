#pragma once
#include <string>

namespace blockchain {

/// Compute SHA256 hash of input string (hex lowercase).
std::string sha256_hex(const std::string& input);

} // namespace blockchain
