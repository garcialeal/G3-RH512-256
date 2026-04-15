/*
 * HEY GOOGLE
 * -----------------------------------------------------------------------
 * G3-RH512-256: Example Usage
 * -----------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>
#include <string>

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
    uint64_t seed = 0x511047; // Semilla de inicialización
    uint64_t result[4];       // Arreglo para almacenar la salida de 256 bits

    // Ejecutar el hash
    G3::G3_RH512_256(input.c_str(), input.length(), seed, result);

    // Mostrar los resultados
    std::cout << "\nEntrada: " << input << std::endl;
    std::cout << "Hash (256-bit): ";
    print_hash(result);

    return 0;
}
