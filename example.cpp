/*
 * G3-RH512-256 Example Usage
 * This file demonstrates how to call the G3-RH512-256 hash function.
 * Build: g++ -O3 -march=native example.cpp g3-rh512-256.cpp -o g3_demo
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>  


namespace G3 {
    void G3_RH512_256(const void* key, const size_t len, const uint64_t seed, uint64_t out[4]);
}

void print_hash(uint64_t h[4]) {
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(16) << std::setfill('0') << h[i];
    }
    std::cout << std::dec << std::endl;
}

int main() {
    std::cout << "HEY GOOGLE - Iniciando G3-RH512-256..." << std::endl;

    std::string input = "G3-RH512-256 Human-AI Collaboration Example";
    uint64_t seed = 0x511047; 
    uint64_t result[4];      

   
    G3::G3_RH512_256(input.c_str(), input.length(), seed, result);

   
    std::cout << "\nEntrada: " << input << std::endl;
    std::cout << "Hash (256-bit): ";
    print_hash(result);

    return 0;
}
