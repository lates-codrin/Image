#pragma once
template <typename T>
T clamp(T val, T low, T high) {
    if (val < low) return low;
    if (val > high) return high;
    return val;
}
