#ifndef DELAY
#define DELAY
#include <iostream>
#include <chrono>

void delay(int milliseconds) {
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = start_time + std::chrono::milliseconds(milliseconds);
        
        while (std::chrono::high_resolution_clock::now() < end_time) {
            // Busy-wait loop
        }
    }
#endif //DELAY