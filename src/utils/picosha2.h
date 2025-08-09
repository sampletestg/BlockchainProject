#pragma once
// picosha2 minimal subset (public domain / MIT style small implementation)
// This is a compact SHA256 function that returns hex.

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace picosha2 {

inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ ((~x) & z); }
inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ (x & z) ^ (y & z); }
inline uint32_t rotr(uint32_t x, int n){ return (x >> n) | (x << (32 - n)); }
inline uint32_t bsig0(uint32_t x){ return rotr(x,2) ^ rotr(x,13) ^ rotr(x,22); }
inline uint32_t bsig1(uint32_t x){ return rotr(x,6) ^ rotr(x,11) ^ rotr(x,25); }
inline uint32_t ssig0(uint32_t x){ return rotr(x,7) ^ rotr(x,18) ^ (x >> 3); }
inline uint32_t ssig1(uint32_t x){ return rotr(x,17) ^ rotr(x,19) ^ (x >> 10); }

inline std::string to_hex_string(const std::vector<unsigned char>& digest){
    std::ostringstream oss;
    for(auto c : digest) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    return oss.str();
}

inline std::vector<unsigned char> sha256_raw(const std::string& input) {
    static const uint32_t k[64] = {
        0x428a2f98ul,0x71374491ul,0xb5c0fbcful,0xe9b5dba5ul,0x3956c25bul,0x59f111f1ul,0x923f82a4ul,0xab1c5ed5ul,
        0xd807aa98ul,0x12835b01ul,0x243185beul,0x550c7dc3ul,0x72be5d74ul,0x80deb1feul,0x9bdc06a7ul,0xc19bf174ul,
        0xe49b69c1ul,0xefbe4786ul,0x0fc19dc6ul,0x240ca1ccul,0x2de92c6ful,0x4a7484aaul,0x5cb0a9dcul,0x76f988daul,
        0x983e5152ul,0xa831c66dul,0xb00327c8ul,0xbf597fc7ul,0xc6e00bf3ul,0xd5a79147ul,0x06ca6351ul,0x14292967ul,
        0x27b70a85ul,0x2e1b2138ul,0x4d2c6dfcul,0x53380d13ul,0x650a7354ul,0x766a0abbul,0x81c2c92eul,0x92722c85ul,
        0xa2bfe8a1ul,0xa81a664bul,0xc24b8b70ul,0xc76c51a3ul,0xd192e819ul,0xd6990624ul,0xf40e3585ul,0x106aa070ul,
        0x19a4c116ul,0x1e376c08ul,0x2748774cul,0x34b0bcb5ul,0x391c0cb3ul,0x4ed8aa4aul,0x5b9cca4ful,0x682e6ff3ul,
        0x748f82eeul,0x78a5636ful,0x84c87814ul,0x8cc70208ul,0x90befffaul,0xa4506cebul,0xbef9a3f7ul,0xc67178f2ul
    };

    // Preprocessing
    std::vector<unsigned char> bytes(input.begin(), input.end());
    uint64_t bitlen = bytes.size() * 8ull;
    // append 0x80
    bytes.push_back(0x80);
    // append zeros until length ≡ 448 (mod 512) -> that is bytes ≡ 56 (mod 64)
    while ((bytes.size() % 64) != 56) bytes.push_back(0x00);
    // append 64-bit big-endian length
    for (int i = 7; i >= 0; --i) bytes.push_back(static_cast<unsigned char>((bitlen >> (8 * i)) & 0xff));

    // initial hash values
    uint32_t h0 = 0x6a09e667ul, h1 = 0xbb67ae85ul, h2 = 0x3c6ef372ul, h3 = 0xa54ff53aul;
    uint32_t h4 = 0x510e527ful, h5 = 0x9b05688cul, h6 = 0x1f83d9abul, h7 = 0x5be0cd19ul;

    // process chunks
    for (size_t chunk = 0; chunk < bytes.size(); chunk += 64) {
        uint32_t w[64];
        // prepare message schedule
        for (int i = 0; i < 16; ++i) {
            w[i] = (bytes[chunk + 4*i] << 24) | (bytes[chunk + 4*i + 1] << 16) |
                   (bytes[chunk + 4*i + 2] << 8) | (bytes[chunk + 4*i + 3]);
        }
        for (int i = 16; i < 64; ++i) {
            w[i] = ssig1(w[i-2]) + w[i-7] + ssig0(w[i-15]) + w[i-16];
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        for (int i = 0; i < 64; ++i) {
            uint32_t T1 = h + bsig1(e) + ch(e,f,g) + k[i] + w[i];
            uint32_t T2 = bsig0(a) + maj(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        h0 += a; h1 += b; h2 += c; h3 += d; h4 += e; h5 += f; h6 += g; h7 += h;
    }

    std::vector<unsigned char> digest(32);
    uint32_t hs[8] = {h0,h1,h2,h3,h4,h5,h6,h7};
    for (int i = 0; i < 8; ++i) {
        digest[4*i    ] = static_cast<unsigned char>((hs[i] >> 24) & 0xff);
        digest[4*i + 1] = static_cast<unsigned char>((hs[i] >> 16) & 0xff);
        digest[4*i + 2] = static_cast<unsigned char>((hs[i] >> 8) & 0xff);
        digest[4*i + 3] = static_cast<unsigned char>((hs[i]) & 0xff);
    }
    return digest;
}

inline std::string hash_hex_string(const std::string& input) {
    auto raw = sha256_raw(input);
    return to_hex_string(raw);
}

} // namespace picosha2
