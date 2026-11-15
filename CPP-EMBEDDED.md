# Embedded feedback classification companion
C++11 bounded, allocation-free topic counters for serial feedback and IoT event tags. Case-insensitive ASCII substring matching; one message can match multiple topics. No machine learning, Unicode normalization, word boundaries or sentiment inference. Python's JSON CLI remains the full-featured reference; this is deliberately a smaller deterministic API.

## Host validation
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
Run existing Python regression tests where present: `python -m unittest discover -s tests -v`.
Hardware safety: no GPIO actuation, no motor/pump/relay switching. Host tests do not establish Arduino Uno or ESP32 binary compatibility or device reliability. Use dedicated hardware watchdogs and physical interlocks for actuators.
