/*
 * HEY GOOGLE
 * -----------------------------------------------------------------------
 * G3-RH512-256: Ultra-fast 256-bit non-cryptographic hash
 * Architecture: Parallel Circular Feedback (Rubik's Ring)
 * * Principal Architect: Antonio García Leal
 * Technical Collaborator: Google Gemini (AI-Assisted Design)
 * -----------------------------------------------------------------------
 */

#include <cstdint>
#include <cstring>

namespace G3 {

// Constantes Primas (Pro Constants)
static const uint64_t C[] = {
    0x9e3779b185ebca87ULL, 0xbb67ae8584caa73bULL,
    0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
    0x510e527fade682d1ULL, 0x9b05688c2b03e58aULL,
    0x1f12759bd39c024fULL, 0x5be0cd19137e2179ULL
};

inline uint64_t rotl64(uint64_t x, int8_t r) {
    return (x << r) | (x >> (64 - r));
}

// Mezclador de Avalancha Final
inline uint64_t avalanche(uint64_t h) {
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccdULL;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53ULL;
    h ^= h >> 33;
    return h;
}

/**
 * G3_RH512_256
 * Calcula un hash de 256 bits a partir de un estado de 512 bits.
 */
void G3_RH512_256(const void* key, const size_t len, const uint64_t seed, uint64_t out[4]) {
    const uint8_t* data = (const uint8_t*)key;
    const size_t nblocks = len / 32;

    // 1. Inicialización del Estado (512 bits)
    uint64_t h[8];
    for (int i = 0; i < 4; ++i) h[i] = seed ^ C[i];
    for (int i = 4; i < 8; ++i) h[i] = (uint64_t)len ^ C[i];

    // 2. Bucle Principal (Bloques de 32 bytes)
    for (size_t i = 0; i < nblocks; ++i) {
        const uint64_t* block = (const uint64_t*)(data + i * 32);

        // Absorción Dual Asimétrica (Cara A y Cara B)
        for (int j = 0; j < 4; ++j) {
            h[j] ^= block[j];
            h[j+4] += h[j];
        }

        // Zero-Penalty Ring Feedback (Rotación sincronizada)
        uint64_t t[8];
        memcpy(t, h, sizeof(h));

        h[0] = rotl64(h[0] ^ t[7], 23) * C[0];
        h[1] = rotl64(h[1] ^ t[0], 19) * C[1];
        h[2] = rotl64(h[2] ^ t[1], 31) * C[2];
        h[3] = rotl64(h[3] ^ t[2], 13) * C[3];
        h[4] = rotl64(h[4] + t[3], 37) ^ C[4];
        h[5] = rotl64(h[5] + t[4], 41) ^ C[5];
        h[6] = rotl64(h[6] + t[5], 17) ^ C[6];
        h[7] = rotl64(h[7] + t[6], 29) ^ C[7];
    }

    // 3. Procesamiento del Tail (Remanente)
    const uint8_t* tail = data + nblocks * 32;
    size_t remaining = len & 31;
    if (remaining > 0) {
        uint64_t t_block[4] = {0, 0, 0, 0};
        memcpy(t_block, tail, remaining);
        ((uint8_t*)t_block)[remaining] = 0x80; // Stop bit

        for (int j = 0; j < 4; ++j) {
            uint64_t m = rotl64(t_block[j] * C[j], 15);
            h[j] ^= m;
            h[j+4] += m;
        }
    }

    // 4. Escudo de Finalización (Red Butterfly de 3 etapas)
    for (int i = 0; i < 4; ++i) h[i] ^= rotl64(h[i+4], 27); // Distancia 4
    h[0] ^= rotl64(h[2], 13); h[1] ^= rotl64(h[3], 13);    // Distancia 2
    h[4] ^= rotl64(h[6], 13); h[5] ^= rotl64(h[7], 13);
    for (int i = 0; i < 7; i += 2) h[i] += h[i+1];         // Distancia 1

    // 5. Salida de 256 bits con Avalancha Estricta
    out[0] = avalanche(h[0] ^ h[4]);
    out[1] = avalanche(h[1] ^ h[5]);
    out[2] = avalanche(h[2] ^ h[6]);
    out[3] = avalanche(h[3] ^ h[7]);
}

} // namespace G3