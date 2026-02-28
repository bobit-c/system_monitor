#include "system_monitor.h"
#include <fstream>
#include <sstream>
#include <string>

float SystemMonitor::getCPUUsage() {
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string cpu;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;

    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    unsigned long long idleTime = idle + iowait;
    unsigned long long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    unsigned long long totalDiff = totalTime - prevTotal;
    unsigned long long idleDiff = idleTime - prevIdle;

    prevTotal = totalTime;
    prevIdle = idleTime;

    if (totalDiff == 0) return 0.0;

    return 100.0f * (1.0f - ((float)idleDiff / totalDiff));
}

float SystemMonitor::getMemoryUsage() {
    std::ifstream file("/proc/meminfo");
    std::string key;
    unsigned long totalMem = 0, freeMem = 0;

    while (file >> key) {
        if (key == "MemTotal:") {
            file >> totalMem;
        } else if (key == "MemAvailable:") {
            file >> freeMem;
            break;
        }
        file.ignore(256, '\n');
    }

    if (totalMem == 0) return 0.0;

    return 100.0f * (1.0f - ((float)freeMem / totalMem));
}

float SystemMonitor::getTemperature() {
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    int tempMilli = 0;
    file >> tempMilli;

    if (!file) return -1.0f;

    return tempMilli / 1000.0f;
}
