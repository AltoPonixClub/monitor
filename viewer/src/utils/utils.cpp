
#include "utils.h"
#include <chrono>

long Utils::getTimeMs() {
    return std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1);
}

