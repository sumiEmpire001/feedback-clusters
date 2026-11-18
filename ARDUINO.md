# Arduino feedback classifier demo

Open `examples/arduino-feedback/arduino-feedback.ino` in a checkout of this repository. Keep `cpp/core.hpp` at its relative location. Target: Arduino Uno/Mega or ESP32 using 115200 baud serial monitor, newline termination. No external components or actuators. Input is limited to 96 bytes per line; overflowed messages are rejected and discarded until newline. Only ASCII case folding is supported. This is deterministic substring classification, not ML, and counters are volatile (reset on reboot). Do not send secrets over serial.

Host regression: `cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure`. Existing Python behavior remains independent. GCC/Clang host tests do not prove Arduino/ESP32 compilation, electrical correctness, or on-device operation. The sketch uses a relative header path; IDE sketch-copying workflows may require placing the shared header inside the sketch folder.

## Board-build CI (added 2026-11-17)
The `.github/workflows/arduino-board-compile.yml` workflow invokes `arduino-cli compile` for **Arduino Uno (AVR)** and **ESP32 generic dev module**. This checks board-toolchain compatibility in GitHub Actions; host CMake/g++ and Python CI remain separate. A green compile does not establish actual sensor readings, wiring, pin compatibility on every variant, watchdog behavior, or electrical safety. Test on the actual board before connecting actuators.

Serial classifier rejects empty/control-byte messages before changing counters; no hardware ML inference. UART input is untrusted and limited to 96 bytes.
