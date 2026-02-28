#include "system_monitor.h"
#include "csv_logger.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

int main() {
    SystemMonitor monitor;
    CSVLogger logger("system_monitor.csv");
    thresholds t; // instance with default limits
    
    int log_counter = 0;
    const int LOG_INTERVAL = 10; // Log every 10 seconds

    while (true) {
        float cpu = monitor.getCPUUsage();
        float mem = monitor.getMemoryUsage();
        float temp = monitor.getTemperature();

        std::cout << "\033[2J\033[H"; // clear screen

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "===== System Monitor =====\n";

        std::cout << "CPU Usage: " << cpu << " %";
        if (cpu >= 0 && cpu > t.cpu_max) {
            std::cout << " [WARNING] (High!)";
        }
        std::cout << "\n";

        std::cout << "Memory Usage: " << mem << " %\n";

        if (temp >= 0) {
            if (temp > t.temp_max) {
                std::cout << "[WARNING] Temperature:  " << temp << " °C (High!)\n";
            }
            std::cout << "Temperature:  " << temp << " °C\n";
        } else {
            std::cout << "Temperature:  Not available\n";
        }
        
        // Log to CSV every LOG_INTERVAL seconds
        log_counter++;
        if (log_counter >= LOG_INTERVAL) {
            logger.log(cpu, mem, temp);
            log_counter = 0;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}