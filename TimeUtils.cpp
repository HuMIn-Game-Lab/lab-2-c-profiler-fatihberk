#include "TimeUtils.h"
#include <chrono>

// Get the current time in seconds with high precision
double TimeUtils::getCurrentTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::duration<double>>(now.time_since_epoch());
    return timeSinceEpoch.count();
}
