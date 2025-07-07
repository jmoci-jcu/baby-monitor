#include "pico/stdlib.h"
#include <vector>

namespace mic_driver {
void init(
    uint16_t clkdiv //48MHz/f_target - 1 to the nearest integer
);
std::vector<uint16_t> read(uint16_t nSamples);
}