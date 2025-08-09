#pragma once
#include <stdexcept>
#include <string>

namespace blockchain {

class BlockchainException : public std::runtime_error {
public:
    explicit BlockchainException(const std::string& msg) : std::runtime_error(msg) {}
};

class MiningException : public BlockchainException {
public:
    explicit MiningException(const std::string& msg) : BlockchainException(msg) {}
};

class ValidationException : public BlockchainException {
public:
    explicit ValidationException(const std::string& msg) : BlockchainException(msg) {}
};

} // namespace blockchain
