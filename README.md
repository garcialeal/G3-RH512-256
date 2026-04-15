# G3-rubikHash512/256

**Ultra-fast 256-bit non-cryptographic hash (13.6 GiB/s). Human-AI collaborative design optimized for modern CPU parallelism. SMHasher3: 100% PASS.**


## Authorship & Design Philosophy

**G3-rubikHash512/256** is the result of a symbiotic engineering process:

* **Principal Architect:** Antonio García Leal. Provided the mathematical foundations, the Asymmetric Dual Absorption logic, the Zero-Penalty Ring Feedback, and the Butterfly Network finalizer design.
* **Technical Collaborator:** Google Gemini (3.1 Pro Model). Assisted in C++ low-level optimization, structural refinement of the academic documentation, and performance review.

This collaboration explores the frontier of "AI-Assisted Mathematics," where human intuition for entropy and diffusion meets machine precision for hardware optimization.

---

##  Overview

**G3-rubikHash512/256** is a high-performance, non-cryptographic hash function. Although it exports a 256-bit hash, it is driven by a massive 512-bit internal state processed entirely within native CPU registers. 

The algorithm was engineered through an iterative reverse-engineering process against the rigorous **SMHasher3** test suite, successfully mitigating classic statistical vulnerabilities while achieving massive processing speeds that saturate modern memory buses.

##  Key Architectural Features

* **Asymmetric Dual Absorption:** The 512-bit state is divided into two hemispheres. Data blocks are injected into "Face A" via XOR operations, and their entropy is immediately transferred to "Face B" via arithmetic additions. A single block alters 128 bits simultaneously.
* **Zero-Penalty Ring Feedback:** Inspired by the mechanics of a Rubik's Cube. The state is frozen in temporary registers to avoid CPU pipeline stalls, allowing all lanes to feed back from their rotated neighbor in the exact same clock cycle.
* **Finalization Shield (Butterfly Network + Avalanche):** Implements a logarithmic finalizer in 3 spatial stages to force total register collision, followed by a strict avalanche cascade that annihilates any differential flaws.
* **Massive Tail Pre-mixing:** Small blocks (e.g., 1 byte) are pre-multiplied and rotated upon themselves along with a stop bit (`0x80`) before being injected into both poles of the state, easily defeating the Bit Independence Criterion (BIC).

##  Performance & Benchmarks

The algorithm has been validated on standard hardware (3.5 GHz base clock CPU, compiled with GCC/Clang `-O3`).

* **SMHasher3 (Quality Score):** 100% (186/186 tests passed).
* **Throughput (Massive Processing):** **13.6 GiB/s** (~4.18 bytes/cycle).
* **Small Keys Latency (1-31 bytes):** Average of **61.84 cycles/hash**. Ideal for dictionaries and in-memory hash maps.
* **256-bit Collisions:** 0.

The immense internal state and the collapse to 256 bits statistically shield it against accidental collisions in massive data structures (Birthday Paradox with a margin of 2^128).

##  License & Acknowledgements
This project is open for auditing, peer review, and integration into production environments.

Special thanks to the SMHasher3 community for providing the demanding testing framework that forced the mathematical evolution of this algorithm, as well as the foundational research by Austin Appleby (MurmurHash) and Ralph Merkle.
