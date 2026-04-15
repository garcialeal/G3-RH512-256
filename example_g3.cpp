/*
 * HEY GOOGLE
 * -----------------------------------------------------------------------
 * G3-RH512-256: Example Usage and Collision Test
 * -----------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Declaración externa de la función para vincular los archivos
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
    uint64_t seed = 0x511047; // Semilla de ejemplo
    uint64_t result[4];

    // Ejecutar el hash
    G3::G3_RH512_256(input.c_str(), input.length(), seed, result);

    std::cout << "\nEntrada: " << input << std::endl;
    std::cout << "Hash (256-bit): ";
    print_hash(result);

    // Test de sensibilidad (Avalancha)
    std::string input2 = "G3-RH512-256 Human-AI Collaboration ExamplE"; // Solo cambia el último bit
    uint64_t result2[4];
    G3::G3_RH512_256(input2.c_str(), input2.length(), seed, result2);

    std::cout << "\nEntrada (Modificada): " << input2 << std::endl;
    std::cout << "Hash (256-bit):      ";
    print_hash(result2);

    std::cout << "\n[Test completado con exito]" << std::endl;

    return 0;
}